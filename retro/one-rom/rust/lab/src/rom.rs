//! One ROM Lab - ROM handling

// Copyright (c) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT licence

#[allow(unused_imports)]
use log::{debug, error, info, trace, warn};

use alloc::vec::Vec;
use embassy_stm32::gpio::{Flex, Pull, Speed};
use embassy_time::{Duration, Instant, Timer};

use onerom_database::{CsActive, RomEntry, RomType, checksum, identify_rom, sha1_digest};

use crate::logs::{log_bad_rom_match, log_good_rom_match, log_rom_id};

/// Identification information for a particular ROM type.  Includes:
/// - The type of the ROM used to construct the ROM image (in particular, using
///   the ROM type's size and chip select behaviour).
/// - The wrapping 32-bit checksum of the ROM image.
/// - The SHA1 digest of the ROM image.
/// - A flag indicating whether the ROM image is all zeros.
/// - A flag indicating whether the ROM image is all ones (0xFF).
#[derive(Debug)]
pub struct Id {
    rom_type: RomType,
    sum: u32,
    sha1: [u8; 20],
    all_zeros: bool,
    all_ones: bool,
}

impl Default for Id {
    fn default() -> Self {
        Self {
            rom_type: RomType::Type2364 { cs: CsActive::Low },
            sum: 0,
            sha1: [0u8; 20],
            all_zeros: false,
            all_ones: false,
        }
    }
}

impl Id {
    pub fn rom_type(&self) -> RomType {
        self.rom_type
    }

    pub fn sum(&self) -> u32 {
        self.sum
    }

    pub fn sha1(&self) -> &[u8; 20] {
        &self.sha1
    }

    pub fn all_ones(&self) -> bool {
        self.all_ones
    }

    pub fn all_zeros(&self) -> bool {
        self.all_zeros
    }
}

/// Results for ROM detection.
#[derive(Debug, Default)]
pub struct Matches {
    good: Vec<&'static RomEntry>,
    bad: Vec<(&'static RomEntry, RomType)>,
    ids: [Id; RomType::all().len()],
}

/// Object representing the ROM.  Used to read and detect connected ROMs.
pub struct Rom {
    address: AddressLines,
    data: DataLines,
    pub buf: [u8; 1 << AddressLines::NUM_ADDR_LINES],
    matches: Option<Matches>,
    last_read_duration: Option<Duration>,
}

impl Rom {
    /// Creates a new ROM object.
    ///
    /// Arguments:
    /// - `addr_pins`: An array of the physical pins connected to A0-A13.  A13
    ///   is actually the 2364 chip select pin.
    /// - `data_pins`: An array of the physical pins connected to D0-D7.
    pub fn new(
        addr_pins: [Flex<'static>; AddressLines::NUM_ADDR_LINES],
        data_pins: [Flex<'static>; DataLines::NUM_DATA_LINES],
    ) -> Self {
        Self {
            address: AddressLines { address: addr_pins },
            data: DataLines::new(data_pins),
            buf: [0u8; 1 << AddressLines::NUM_ADDR_LINES],
            matches: None,
            last_read_duration: None,
        }
    }

    /// Initializes the ROM object.  Must be called after creation, before
    /// calling other methods.
    pub fn init(&mut self) {
        self.address.init();
        self.data.init();
    }

    // Reads the ROM data without any delays between settings address lines
    // and reading the data.
    #[allow(dead_code)]
    async fn read_fast(&mut self) {
        let max_addr = 1 << AddressLines::NUM_ADDR_LINES;
        assert!(self.buf.len() == max_addr);

        let start = Instant::now();

        // Now read the ROM
        for ii in 0..max_addr {
            self.address.set(ii);
            self.buf[ii] = self.data.read();
        }
        self.address.init();

        let end = Instant::now();
        self.last_read_duration = Some(end - start);
    }

    // Reads the ROM data with, resetting address lines to inputs (i.e. tri-
    // stating them) in between reads.
    #[allow(dead_code)]
    async fn read_slow(&mut self) {
        let max_addr = 1 << AddressLines::NUM_ADDR_LINES;
        assert!(self.buf.len() == max_addr);

        self.address.set(0x3FFF); // Set all address lines high
        Timer::after_micros(1).await;

        let start = Instant::now();

        // Now read the ROM
        for ii in 0..max_addr {
            self.address.set(ii);
            Timer::after_micros(1).await;
            self.buf[ii] = self.data.read();
            Timer::after_micros(1).await;
        }
        self.address.init();

        let end = Instant::now();
        self.last_read_duration = Some(end - start);
    }

    // Identifies the read ROM image.  Must only be called after either
    // `Self::read_fast()` or `Self::read_slow()`.
    //
    // The existing ROM image buffer contains a 16KB image, based on the
    // entire address space, including all CS lines, being enumerated.  This
    // function takes that image, and turns it into an equivalent ROM image
    // for every supported ROM type (including each possible chip select
    // configuration) in turn.
    //
    // It then attempted to match each image against the database.  Hence, it
    // should detect any of the different ROM types, if any of them match.
    // There may be multiple matches, for example if:
    // - the ROM image is a larger image, containing multiple copies of a
    //   smaller one (i.e. a 2364 image containing two 2332 images, one for
    //   each 2332 CS2 chip select value)
    // - the actual bytes data (and hence SHA1/checksum) was a match, but the
    //   actually CS cofiguration required to serve it differed from that in
    //   the database (this is a "bad" match).
    fn id(&mut self) {
        // Scratch buffer
        let mut buf = [0u8; RomType::max_size()];

        let mut matches = Matches::default();

        for (ii, rom_type) in RomType::all().iter().enumerate() {
            // Build a temporary copy of the ROM data, based on this particular
            // ROM type and CS behaviour
            let size = rom_type.size();
            #[allow(clippy::needless_range_loop)]
            for jj in 0..size {
                let addr = jj | rom_type.cs_active_mask();
                buf[jj] = self.buf[addr];
            }

            // Now use this copy to get the checksum/SHA1 digest
            let sum: u32 = checksum(&buf[0..size]);
            let sha1 = sha1_digest(&buf[0..size]);
            let (mut good, mut bad) = identify_rom(rom_type, sum, sha1);

            matches.good.append(&mut good);
            matches.bad.append(&mut bad);
            matches.ids[ii] = Id {
                rom_type: *rom_type,
                sum,
                sha1,
                all_zeros: buf[0..size].iter().all(|&b| b == 0),
                all_ones: buf[0..size].iter().all(|&b| b == 0xFF),
            };
        }

        self.matches = Some(matches);
    }

    /// Reads any connected ROM and detects any matches.
    ///
    /// Use `Self::good_matches()`, `Self::bad_matches()` and `Self::ids()` for
    /// the results.  `Self::last_read_duration()` provides the time taken to
    /// do the read of the ROM.
    pub async fn detect(&mut self) {
        self.read_fast().await;
        self.id();
    }

    /// Returns last read duration
    pub fn last_read_duration(&self) -> Option<Duration> {
        self.last_read_duration
    }

    /// Returns good matches
    pub fn good_matches(&self) -> Option<&Vec<&'static RomEntry>> {
        self.matches.as_ref().map(|m| &m.good)
    }

    /// Returns bad matches - those where SHA1 or checksum matches a database
    /// entry, but the ROM type (probably chip select line configuration)
    /// didn't.
    pub fn bad_matches(&self) -> Option<&Vec<(&'static RomEntry, RomType)>> {
        self.matches.as_ref().map(|m| &m.bad)
    }

    /// Returns the identification information of the various ROM types for
    /// this ROM image
    pub fn ids(&self) -> Option<&[Id; RomType::all().len()]> {
        self.matches.as_ref().map(|m| &m.ids)
    }

    /// Reads all the data from the ROM and tries to match it.
    ///
    /// Returns the first RomEntry found, if multiple exist.  Does not return
    /// any "bad" matches.
    pub async fn read_rom(&mut self) -> Option<RomEntry> {
        // Read any connected ROM
        info!("-----");
        info!("Reading ROM...");
        self.detect().await;
        let dur = self.last_read_duration().unwrap();
        debug!("Read took {}us", dur.as_micros());

        // Output any good matches
        let good_matches = self.good_matches().unwrap();
        if !good_matches.is_empty() {
            for entry in good_matches {
                log_good_rom_match(entry);
            }
        }

        // Also output any bad matches
        let bad_matches = self.bad_matches().unwrap();
        if !bad_matches.is_empty() {
            for (entry, rom_type) in bad_matches {
                log_bad_rom_match(entry, rom_type);
            }
        }

        // If we got none of either, log why
        if good_matches.is_empty() && bad_matches.is_empty() {
            let ids = self.ids().unwrap();
            let mut all_zeros_count = 0;
            let mut all_ones_count = 0;
            for id in ids {
                if id.all_zeros() {
                    all_zeros_count += 1;
                }
                if id.all_ones() {
                    all_ones_count += 1;
                }
            }
            if all_zeros_count == ids.len() {
                warn!("ROM data is all zeros - check ROM is connected");
            } else if all_ones_count == ids.len() {
                warn!("ROM data is all 0xFF - ROM may be blank or unprogrammed");
            } else {
                info!("No matches found in database - ROM information follows:");
                for id in ids {
                    if !id.all_zeros() && !id.all_ones() {
                        log_rom_id(id);
                    }
                }
            }
        }

        if !good_matches.is_empty() {
            Some(good_matches[0].clone())
        } else {
            None
        }
    }
}

// Address - and CS lines - for the ROM object to use.
struct AddressLines {
    // Array of GPIOs corresponding to A0, A2, ... A13.
    // A13 is the address line used for 2364's CS line.
    address: [Flex<'static>; Self::NUM_ADDR_LINES],
}

impl AddressLines {
    const NUM_ADDR_LINES: usize = 14;

    fn init(&mut self) {
        for pin in self.address.iter_mut() {
            pin.set_as_input(Pull::None);
        }
    }

    #[inline]
    fn set(&mut self, address: usize) {
        assert!(address < (1 << Self::NUM_ADDR_LINES));

        // Set address pins as outputs and drive them
        for (i, pin) in self.address.iter_mut().enumerate() {
            pin.set_as_output(Speed::High);
            if address & (1 << i) != 0 {
                pin.set_high();
            } else {
                pin.set_low();
            }
        }
    }

    #[allow(dead_code)]
    fn clear(&mut self) {
        self.init()
    }
}

// Data lines for the ROM object to use.
struct DataLines {
    data: [Flex<'static>; Self::NUM_DATA_LINES],
}

impl DataLines {
    const NUM_DATA_LINES: usize = 8;

    fn new(data_pins: [Flex<'static>; Self::NUM_DATA_LINES]) -> Self {
        Self { data: data_pins }
    }

    fn pins(&self) -> &[Flex<'static>] {
        &self.data
    }

    fn pins_mut(&mut self) -> &mut [Flex<'static>] {
        &mut self.data
    }

    fn init(&mut self) {
        for pin in self.pins_mut() {
            pin.set_as_input(Pull::Down);
        }
    }

    fn read(&self) -> u8 {
        let mut value = 0u8;
        for (i, pin) in self.pins().iter().enumerate() {
            if pin.is_high() {
                value |= 1 << i;
            }
        }
        value
    }
}
