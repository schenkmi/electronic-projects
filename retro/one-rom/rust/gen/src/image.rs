// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! Image generator for One ROM
//!
//! Used to create the images to be flashed to One ROM, pointed to by the
//! metadata.
//!
//! Create one or more [`Rom`] instances, and group them into one or more
//! [`RomSet`] instances.
//!
//! Then use [`RomSet::get_byte()`] to retrieve bytes from the ROM set, as the
//! MCU would address them, and needs to serve bytes - store these off in order
//! into a final ROM image to be flashed to One ROM, at an offset pointed to by
//! the metadata.

use alloc::format;
use alloc::string::String;
use alloc::vec::Vec;
use core::cmp::Ordering;

use onerom_config::fw::ServeAlg;
use onerom_config::hw::Board;
use onerom_config::mcu::Family as McuFamily;
use onerom_config::rom::RomType;

use crate::{Error, Result};

/// Value to use when told to pad a ROM image
pub const PAD_BLANK_BYTE: u8 = 0xAA;

/// Value to use when no ROM in portion of address space
pub const PAD_NO_ROM_BYTE: u8 = 0xAA;

const ROM_METADATA_LEN_NO_FILENAME: usize = 4;
const ROM_METADATA_LEN_WITH_FILENAME: usize = 8;

const ROM_SET_METADATA_LEN: usize = 16; // sdrr_rom_set_t

/// How to handle ROM images that are too small for the ROM type
#[derive(Debug, Default, Clone, serde::Serialize, serde::Deserialize)]
#[serde(rename_all = "snake_case")]
#[cfg_attr(feature = "schemars", derive(schemars::JsonSchema))]
pub enum SizeHandling {
    /// No special handling.  Errors if the image size does not exactly match
    /// the ROM size.
    #[default]
    None,

    /// Duplicates the image as many times as needed to fill the ROM.  Errors
    /// if the image size is not an exact divisor of the ROM size.
    Duplicate,

    /// Truncates the image to fit the ROM size.  Errors if the image is an
    /// exact match size-wise.
    Truncate,

    /// Pads the image out with [`PAD_BLANK_BYTE`].
    Pad,
}

/// Possible Chip Select line logic options
#[derive(Debug, Clone, Copy, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
#[cfg_attr(feature = "schemars", derive(schemars::JsonSchema))]
#[serde(rename_all = "snake_case")]
pub enum CsLogic {
    /// Chip Select line is active low
    ActiveLow,

    /// Chip Select line is active high
    ActiveHigh,

    /// Used for 2332/2316 ROMs, when a CS line isn't used because it's always
    /// tied active.
    Ignore,
}

/// Location within a larger ROM image that the specific image to use resides
#[derive(Debug, Clone, Copy, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
#[cfg_attr(feature = "schemars", derive(schemars::JsonSchema))]
#[serde(rename_all = "snake_case")]
pub struct Location {
    /// Start of the image within the larger ROM image
    pub start: usize,

    /// Length of the image within the larger ROM image.  Must match the
    /// selected ROM type, or SizeHandling will be applied.
    pub length: usize,
}

impl CsLogic {
    pub fn try_from_str(s: &str) -> Option<Self> {
        match s.to_lowercase().as_str() {
            "0" => Some(CsLogic::ActiveLow),
            "1" => Some(CsLogic::ActiveHigh),
            "ignore" => Some(CsLogic::Ignore),
            _ => None,
        }
    }

    pub fn c_value(&self) -> &str {
        match self {
            CsLogic::ActiveLow => "CS_ACTIVE_LOW",
            CsLogic::ActiveHigh => "CS_ACTIVE_HIGH",
            CsLogic::Ignore => "CS_NOT_USED",
        }
    }

    pub fn c_enum_val(&self) -> u8 {
        match self {
            CsLogic::ActiveLow => 0,
            CsLogic::ActiveHigh => 1,
            CsLogic::Ignore => 2,
        }
    }
}

#[derive(Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
#[cfg_attr(feature = "schemars", derive(schemars::JsonSchema))]
pub enum CsConfig {
    /// Configuration of the 3 possible Chip Select lines
    ChipSelect {
        /// Where type is ChipSelect, CS1 is always required
        cs1: CsLogic,

        /// Second chip select line, required for certain ROM Types
        cs2: Option<CsLogic>,

        /// Third chip select line, required for certain ROM Types
        cs3: Option<CsLogic>,
    },
    /// Configuration using CE/OE instead of chip select
    CeOe,
}

impl CsConfig {
    pub fn new(cs1: Option<CsLogic>, cs2: Option<CsLogic>, cs3: Option<CsLogic>) -> Self {
        if cs1.is_none() && cs2.is_none() && cs3.is_none() {
            return Self::CeOe;
        } else {
            let cs1 = cs1.expect("CS1 must be specified if any CS lines are used");
            Self::ChipSelect { cs1, cs2, cs3 }
        }
    }

    pub fn cs1_logic(&self) -> CsLogic {
        match self {
            CsConfig::ChipSelect { cs1, .. } => *cs1,
            CsConfig::CeOe => CsLogic::ActiveLow,
        }
    }

    pub fn cs2_logic(&self) -> Option<CsLogic> {
        match self {
            CsConfig::ChipSelect { cs2, .. } => *cs2,
            CsConfig::CeOe => Some(CsLogic::ActiveLow),
        }
    }

    pub fn cs3_logic(&self) -> Option<CsLogic> {
        match self {
            CsConfig::ChipSelect { cs3, .. } => *cs3,
            CsConfig::CeOe => None,
        }
    }
}

/// Single ROM image.  May be part of a ROM set
#[derive(Debug, serde::Serialize, serde::Deserialize)]
#[cfg_attr(feature = "schemars", derive(schemars::JsonSchema))]
pub struct Rom {
    index: usize,

    filename: String,

    // Optional alternative label for the ROM, replacing filename
    label: Option<String>,

    rom_type: RomType,

    cs_config: CsConfig,

    data: Vec<u8>,

    // Optional location within a larger ROM image
    location: Option<Location>,
}

impl Rom {
    fn new(
        index: usize,
        filename: String,
        label: Option<String>,
        rom_type: &RomType,
        cs_config: CsConfig,
        data: Vec<u8>,
        location: Option<Location>,
    ) -> Self {
        Self {
            index,
            filename,
            label,
            rom_type: rom_type.clone(),
            cs_config,
            data,
            location,
        }
    }

    /// Returns the index of the ROM in the configuration
    pub fn index(&self) -> usize {
        self.index
    }

    /// Returns the chip select configuration for the ROM.
    pub fn cs_config(&self) -> &CsConfig {
        &self.cs_config
    }

    /// Returns the ROM filename to use in metadata.  Uses label if specified,
    /// otherwise the actual filename string.
    pub fn filename(&self) -> &str {
        self.label.as_deref().unwrap_or(&self.filename)
    }

    /// Returns a [`Rom`] instance.
    ///
    /// Takes a raw ROM image (binary data, loaded from file) and processes it
    /// according to the specified size handling (none, duplicate, pad) to
    /// ensure it matches the expected size for the given ROM type.
    pub fn from_raw_rom_image(
        index: usize,
        filename: String,
        label: Option<String>,
        source: &[u8],
        mut dest: Vec<u8>,
        rom_type: &RomType,
        cs_config: CsConfig,
        size_handling: &SizeHandling,
        location: Option<Location>,
    ) -> Result<Self> {
        // Slice source if location specified
        let source = if let Some(loc) = location {
            // Bounds check
            let end = loc.start
                .checked_add(loc.length)
                .ok_or(Error::BadLocation {
                    id: index,
                    reason: format!("Location overflow: start={:#X} length={:#X}", loc.start, loc.length),
                })?;
            
            if end > source.len() {
                return Err(Error::RomTooSmall {
                    index,
                    expected: end,
                    actual: source.len(),
                });
            }
            
            &source[loc.start..end]
        } else {
            source
        };
        
        let expected_size = rom_type.size_bytes();
        if dest.len() < expected_size {
            return Err(Error::BufferTooSmall {
                location: "Rom::from_raw_rom_image",
                expected: expected_size,
                actual: dest.len(),
            });
        }

        // See what handling is required, if any
        match source.len().cmp(&expected_size) {
            Ordering::Equal => {
                // Exact match - error if dup/pad specified unnecessarily
                match size_handling {
                    SizeHandling::None => {
                        // Copy source to dest as-is
                        dest[..expected_size].copy_from_slice(&source[..expected_size]);
                    }
                    _ => {
                        return Err(Error::RightSize {
                            size: expected_size,
                        });
                    }
                }
            }
            Ordering::Less => {
                // File too small - handle with dup/pad
                match size_handling {
                    SizeHandling::None => {
                        return Err(Error::RomTooSmall {
                            index,
                            expected: expected_size,
                            actual: source.len(),
                        });
                    }
                    SizeHandling::Duplicate => {
                        if expected_size % source.len() != 0 {
                            return Err(Error::DuplicationNotExactDivisor {
                                rom_size: source.len(),
                                expected_size,
                            });
                        }
                        let multiples = expected_size / source.len();

                        // Copy multiplies of source into dest
                        for i in 0..multiples {
                            let start = i * source.len();
                            let end = start + source.len();
                            dest[start..end].copy_from_slice(source);
                        }
                    }
                    SizeHandling::Pad => {
                        // Copy source to dest and pad the rest with 0xAA
                        dest[..source.len()].copy_from_slice(source);
                        for byte in &mut dest[source.len()..expected_size] {
                            *byte = PAD_BLANK_BYTE;
                        }
                    }
                    SizeHandling::Truncate => {
                        return Err(Error::RomTooLarge {
                            rom_size: source.len(),
                            expected_size,
                        });
                    }
                }
            }
            Ordering::Greater => {
                match size_handling {
                    SizeHandling::Truncate => {
                        // Copy only up to expected size
                        dest[..expected_size].copy_from_slice(&source[..expected_size]);
                    }
                    _ => {
                        return Err(Error::RomTooLarge {
                            rom_size: source.len(),
                            expected_size,
                        });
                    }
                }
            }
        }

        Ok(Self::new(
            index,
            filename,
            label,
            rom_type,
            cs_config,
            dest,
            location,
        ))
    }

    // Transforms from a physical address (based on the hardware pins) to
    // a logical ROM address, so we store the physical ROM mapping, rather
    // than the logical one.
    fn address_to_logical(phys_pin_to_addr_map: &[Option<usize>], address: usize, _board: &Board, num_addr_lines: usize) -> usize {
        let mut result = 0;

        for (pin, item) in phys_pin_to_addr_map.iter().enumerate() {
            if let Some(addr_bit) = item {
                // Only use this mapping if it's within the ROM's address lines
                if *addr_bit < num_addr_lines {
                    if (address & (1 << pin)) != 0 {
                        result |= 1 << addr_bit;
                    }
                }
            }
        }

        result
    }

    // Transforms a data byte by rearranging its bit positions to match the hardware's
    // data pin connections.
    //
    // The hardware has a non-standard mapping for data pins, so we need to rearrange
    // the bits to ensure correct data is read/written.
    //
    // Bit mapping:
    // Original:  7 6 5 4 3 2 1 0
    // Mapped to: 3 4 5 6 7 2 1 0
    //
    // For example:
    // - Original bit 7 (MSB) moves to position 3
    // - Original bit 3 moves to position 7 (becomes new MSB)
    // - Bits 2, 1, and 0 remain in the same positions
    //
    // This transformation ensures that when the hardware reads a byte through its
    // data pins, it gets the correct bit values despite the non-standard connections.
    fn byte_mangled(byte: u8, board: &Board) -> u8 {
        // Start with 0 result
        let mut result = 0;

        // Retrieve data pin mapping - not physical pin to bit mapping, as that would be
        // the wrong way round.
        let data_pins = board.data_pins();

        // For each bit in the original byte
        #[allow(clippy::needless_range_loop)]
        for bit_pos in 0..8 {
            // Check if this bit is set in the original byte
            if (byte & (1 << bit_pos)) != 0 {
                // Get the new position for this bit
                let mut new_pos = data_pins[bit_pos];
                if new_pos > 15 {
                    // Fire rev A
                    assert!(new_pos < 24);
                    new_pos -= 16;
                } else {
                    // All other boards
                    assert!(new_pos < 8);
                }
                // Set the bit in the result at its new position
                result |= 1 << new_pos;
            }
        }

        result
    }

    // Get byte at the given address with both address and data
    // transformations applied.
    //
    // This function:
    // 1. Transforms the address to match the hardware's address pin mapping
    // 2. Retrieves the byte at that transformed address
    // 3. Transforms the byte's bit pattern to match the hardware's data pin
    //    mapping
    //
    // This ensures that when the hardware reads from a certain address
    // through its GPIO pins, it gets the correct byte value with bits
    // arranged according to its data pin connections.
    fn get_byte(&self, phys_pin_to_addr_map: &[Option<usize>], address: usize, board: &Board) -> u8 {
        // We have been passed a physical address based on the hardware pins,
        // so we need to transform it to a logical address based on the ROM
        // image.
        let num_addr_lines = self.rom_type.num_addr_lines();
        let transformed_address = Self::address_to_logical(phys_pin_to_addr_map, address, board, num_addr_lines);

        // Sanity check that we did get a logical address, which must by
        // definition fit within the actual ROM size.
        if transformed_address >= self.data.len() {
            panic!(
                "Transformed address {} out of bounds for ROM image of size {}",
                transformed_address,
                self.data.len()
            );
        }

        // Get the byte from the logical ROM address.
        let byte = self
            .data
            .get(transformed_address)
            .copied()
            .unwrap_or_else(|| {
                panic!(
                    "Address {} out of bounds for ROM image of size {}",
                    transformed_address,
                    self.data.len()
                )
            });

        // Now transform the byte, as the physical data lines are not in the
        // expected order (0-7).
        Self::byte_mangled(byte, board)
    }

    fn rom_type_c_enum_val(&self) -> u8 {
        match self.rom_type {
            RomType::Rom2316 => 0,
            RomType::Rom2332 => 1,
            RomType::Rom2364 => 2,
            RomType::Rom23128 => 3,
            RomType::Rom23256 => 4,
            RomType::Rom23512 => 5,
            RomType::Rom2704 => 6,
            RomType::Rom2708 => 7,
            RomType::Rom2716 => 8,
            RomType::Rom2732 => 9,
            RomType::Rom2764 => 10,
            RomType::Rom27128 => 11,
            RomType::Rom27256 => 12,
            RomType::Rom27512 => 13,
        }
    }
}

/// Type of ROM set
#[derive(Debug, Default, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
#[cfg_attr(feature = "schemars", derive(schemars::JsonSchema))]
#[serde(rename_all = "snake_case")]
pub enum RomSetType {
    /// Single ROM - the default
    #[default]
    Single,

    /// Set of dynamically banked ROMs. Used to switch between active ROM at
    /// runtime using jumpers
    Banked,

    /// Set of multiple ROMs selected by CS lines.  This allows a single One
    /// ROM to serve up to 3 ROM sockets simultaneously.
    Multi,
}

/// A set of ROMs, where the set type is RomSetType
#[derive(Debug, serde::Serialize, serde::Deserialize)]
#[cfg_attr(feature = "schemars", derive(schemars::JsonSchema))]
pub struct RomSet {
    /// ID of the ROM set
    pub id: usize,

    /// Type of ROM set
    pub set_type: RomSetType,

    /// Serving algorithm for the ROM set
    pub serve_alg: ServeAlg,

    /// ROMs in the set
    pub roms: Vec<Rom>,
}

impl RomSet {
    /// Creates a new ROM set of the specified ID, type, and containing the
    /// given ROMs.
    ///
    /// The ID is an arbitrary index, usually the set ID from the config,
    /// starting at 0.
    pub fn new(
        id: usize,
        set_type: RomSetType,
        serve_alg: ServeAlg,
        roms: Vec<Rom>,
    ) -> Result<Self> {
        // Check some ROMs were supplied
        if roms.is_empty() {
            return Err(Error::NoRoms);
        }

        // Check set type matches number of ROMs
        if roms.len() > 1 && set_type == RomSetType::Single {
            return Err(Error::TooManyRoms {
                expected: 1,
                actual: roms.len(),
            });
        }

        if roms.len() == 1 && set_type != RomSetType::Single {
            return Err(Error::TooFewRoms {
                expected: 2,
                actual: roms.len(),
            });
        }

        // Correct the serving algorithm if necessary - we accept any value
        // if a multi-rom set, and correct it.  But we don't accept an invalid
        // value for the other set types.
        let serve_alg = match set_type {
            RomSetType::Single | RomSetType::Banked => {
                if !matches!(
                    serve_alg,
                    ServeAlg::Default | ServeAlg::AddrOnCs | ServeAlg::TwoCsOneAddr
                ) {
                    return Err(Error::InvalidServeAlg { serve_alg });
                } else {
                    serve_alg
                }
            }
            RomSetType::Multi => ServeAlg::AddrOnAnyCs,
        };

        Ok(Self {
            id,
            set_type,
            serve_alg,
            roms,
        })
    }

    pub fn multi_cs_logic(&self) -> Result<CsLogic> {
        let first_cs1 = self.roms[0].cs_config.cs1_logic();
        if self.roms.len() == 1 {
            // Unused
            Ok(CsLogic::Ignore)
        } else {
            // For multi and banked rom sets we need to check all CS1 logic is
            // the same
            for rom in &self.roms {
                if rom.cs_config.cs1_logic() != first_cs1 {
                    return Err(Error::InconsistentCsLogic {
                        first: first_cs1,
                        other: rom.cs_config.cs1_logic(),
                    });
                }
            }

            // For multi-ROM sets we also need to check CS2 and CS3 are ignored
            // for all ROMS
            if self.set_type == RomSetType::Multi {
                for rom in &self.roms {
                    if let Some(cs2) = rom.cs_config.cs2_logic() {
                        if cs2 != CsLogic::Ignore {
                            return Err(Error::InconsistentCsLogic {
                                first: CsLogic::Ignore,
                                other: cs2,
                            });
                        }
                    }
                    if let Some(cs3) = rom.cs_config.cs3_logic() {
                        if cs3 != CsLogic::Ignore {
                            return Err(Error::InconsistentCsLogic {
                                first: CsLogic::Ignore,
                                other: cs3,
                            });
                        }
                    }
                }
            }

            Ok(self.roms[0].cs_config.cs1_logic())
        }
    }

    /// Returns the size of the data required for this ROM set, in bytes.
    pub fn image_size(&self, family: &McuFamily) -> usize {
        if family == &McuFamily::Rp2350 {
            // RP2350 can address full 64KB space for each ROM set
            65536
        } else {
            // STM32F4 uses 16KB space for single ROM sets, otherwise 64KB
            match self.set_type {
                RomSetType::Single => 16384,
                RomSetType::Banked | RomSetType::Multi => 65536,
            }
        }
    }

    fn truncate_phys_pin_to_addr_map(
        phys_pin_to_addr_map: &mut [Option<usize>],
        num_addr_lines: usize,
    ) {
        // Clear any address lines beyond the number of address lines the ROM supports
        for item in phys_pin_to_addr_map.iter_mut() {
            if let Some(addr_bit) = item {
                if *addr_bit >= num_addr_lines {
                    *item = None;
                }
            }
        }
    }

    /// Gets a byte from the ROM set at the given address (as far as the MCU is
    /// concerned) and returns the byte, ready for the MCU to serve.
    pub fn get_byte(&self, address: usize, board: &Board) -> u8 {
        // Hard-coded assumption that X1/X2 (STM32F4) are pins 14/15 for
        // single ROM sets and banked ROM sets.  However, for RP2350 they may
        // be other pins.
        if (self.roms.len() == 1) || (self.set_type == RomSetType::Banked) {
            let (rom_index, masked_address) = if self.set_type != RomSetType::Banked {
                match board.mcu_family() {
                    McuFamily::Rp2350 => {
                        // Single ROM set: uses entire 64KB space
                        assert!(
                            address < 65536,
                            "Address out of bounds for RP235X single ROM set"
                        );
                    }
                    McuFamily::Stm32f4 => {
                        // Single ROM set: uses entire 16KB space
                        assert!(
                            address < 16384,
                            "Address out of bounds for STM32F4 single ROM set"
                        );
                    }
                }
                (0, address)
            } else {
                // Banked mode: use X1/X2 to select ROM
                assert!(address < 65536, "Address out of bounds for banked ROM set");
                let x1_pin = board.bit_x1();
                let x2_pin = board.bit_x2();
                let bank = if board.x_jumper_pull() == 1 {
                    ((address >> x1_pin) & 1) | (((address >> x2_pin) & 1) << 1)
                } else {
                    // Invert the logic if the jumpers pull to GND
                    (!(address >> x1_pin) & 1) | ((!((address >> x2_pin) & 1)) << 1)
                };
                let mask = !(1 << x1_pin) & !(1 << x2_pin);
                let masked_address = address & mask;
                let rom_index = bank % self.roms.len(); // Wrap around
                (rom_index, masked_address)

                // Note that this code fills sections of the overall 64KB image with the bank ROM
                // images even if the CS value is set to inactive
            };

            let num_addr_lines = self.roms[rom_index].rom_type.num_addr_lines();
            let phys_pin_to_addr_map = board.phys_pin_to_addr_map();
            let mut phys_pin_to_addr_map = phys_pin_to_addr_map.clone();
            Self::truncate_phys_pin_to_addr_map(&mut phys_pin_to_addr_map, num_addr_lines);

            return self.roms[rom_index].get_byte(&phys_pin_to_addr_map, masked_address, board);
        }

        // Multiple ROMs: check CS line states to select responding ROM.  This
        // code can handle any X1/X2 positions - but the above can't.
        assert!(address < 65536, "Address out of bounds for multi-ROM set");
        for (index, rom_in_set) in self.roms.iter().enumerate() {
            // Get the physical addr and data pin mappings.  We have to
            // retrieve this for each ROM in the set, as each ROM may be
            // a different type (size).
            let num_addr_lines = rom_in_set.rom_type.num_addr_lines();
            let phys_pin_to_addr_map = board.phys_pin_to_addr_map();
            let mut phys_pin_to_addr_map = phys_pin_to_addr_map.clone();
            Self::truncate_phys_pin_to_addr_map(&mut phys_pin_to_addr_map, num_addr_lines);

            // All of CS1/X1/X2 have to have the same active low/high status
            // so we retrieve that from CS1 (as X1/X2 aren't specifically
            // configured in the rom sets).
            let pins_active_high = rom_in_set.cs_config.cs1_logic() == CsLogic::ActiveHigh;

            // Get the CS pin that controls this ROM's selection
            let cs_pin = board.cs_bit_for_rom_in_set(rom_in_set.rom_type, index);
            assert!(cs_pin <= 15, "Internal error: CS pin is > 15");

            fn is_pin_active(active_high: bool, address: usize, pin: u8) -> bool {
                if active_high {
                    (address & (1 << pin)) != 0
                } else {
                    (address & (1 << pin)) == 0
                }
            }

            let cs_active = is_pin_active(pins_active_high, address, cs_pin);

            if cs_active {
                // Verify exactly one CS pin is active
                let cs1_pin = board.bit_cs1(rom_in_set.rom_type);
                let x1_pin = board.bit_x1();
                let x2_pin = board.bit_x2();

                let cs1_is_active = is_pin_active(pins_active_high, address, cs1_pin);
                let x1_is_active = is_pin_active(pins_active_high, address, x1_pin);
                let x2_is_active = is_pin_active(pins_active_high, address, x2_pin);

                let active_count = [cs1_is_active, x1_is_active, x2_is_active]
                    .iter()
                    .filter(|&&x| x)
                    .count();

                // Only return the byte for a single CS active, otherwise
                // it'll get a "blank" byte
                if active_count == 1 && self.check_rom_cs_requirements(rom_in_set, address, board) {
                    return rom_in_set.get_byte(&phys_pin_to_addr_map, address, board);
                }
            }
        }

        // No ROM is selected, so this part of the address space is set to blank value
        Rom::byte_mangled(PAD_NO_ROM_BYTE, board)
    }

    fn check_rom_cs_requirements(&self, rom_in_set: &Rom, address: usize, board: &Board) -> bool {
        let cs_config = &rom_in_set.cs_config;
        let rom_type = rom_in_set.rom_type;

        // Check CS2 if specified
        if let Some(cs2_logic) = cs_config.cs2_logic() {
            match cs2_logic {
                CsLogic::Ignore => {
                    // CS2 state doesn't matter
                }
                CsLogic::ActiveLow => {
                    let cs2_pin = board.bit_cs2(rom_type);
                    let cs2_active = (address & (1 << cs2_pin)) == 0;
                    if !cs2_active {
                        return false;
                    }
                }
                CsLogic::ActiveHigh => {
                    let cs2_pin = board.bit_cs2(rom_type);
                    let cs2_active = (address & (1 << cs2_pin)) != 0;
                    if cs2_active {
                        return false;
                    }
                }
            }
        }

        // Check CS3 if specified
        if let Some(cs3_logic) = cs_config.cs3_logic() {
            match cs3_logic {
                CsLogic::Ignore => {
                    // CS3 state doesn't matter
                }
                CsLogic::ActiveLow => {
                    let cs3_pin = board.bit_cs3(rom_type);
                    let cs3_active = (address & (1 << cs3_pin)) == 0;
                    if !cs3_active {
                        return false;
                    }
                }
                CsLogic::ActiveHigh => {
                    let cs3_pin = board.bit_cs3(rom_type);
                    let cs3_active = (address & (1 << cs3_pin)) != 0;
                    if cs3_active {
                        return false;
                    }
                }
            }
        }

        true
    }

    #[allow(dead_code)]
    fn mask_cs_selection_bits(&self, address: usize, rom_type: RomType, board: &Board) -> usize {
        let mut masked_address = address;

        // Remove the CS selection bits - only mask bits that exist on this hardware
        masked_address &= !(1 << board.bit_cs1(rom_type));

        // Only mask X1/X2 on hardware that has them
        if board.supports_multi_rom_sets() {
            let x1 = board.bit_x1();
            let x2 = board.bit_x2();
            assert!(x1 < 15 && x2 < 15, "X1/X2 pins must be less than 15");
            masked_address &= !(1 << x1);
            masked_address &= !(1 << x2);
        }

        // Remove CS2/CS3 bits based on ROM type
        match rom_type {
            RomType::Rom2332 => {
                masked_address &= !(1 << board.bit_cs2(rom_type));
            }
            RomType::Rom2316 => {
                masked_address &= !(1 << board.bit_cs2(rom_type));
                masked_address &= !(1 << board.bit_cs3(rom_type));
            }
            RomType::Rom2364 => {
                // 2364 only uses CS1, no additional bits to remove
            }
            RomType::Rom23128 => {
                // No additional bits to remove
            }
            _ => {
                panic!(
                    "Internal error: unsupported ROM type {} in mask_cs_selection_bits",
                    rom_type.name()
                );
            }
        }

        // Ensure address fits within ROM size
        masked_address & ((1 << 13) - 1) // Mask to 13 bits max (8KB)
    }

    /// Returns a slice of the ROMs in this set.
    pub fn roms(&self) -> &[Rom] {
        &self.roms
    }

    /// Returns the length of metadata required for all of the ROMs.  This
    /// includes all ROM structs, plus the array of pointers to them.
    pub fn roms_metadata_len(&self, include_filenames: bool) -> usize {
        let num_roms = self.roms.len();

        // Size of all ROM metadata structs
        let rom_metadata_len = if include_filenames {
            ROM_METADATA_LEN_WITH_FILENAME
        } else {
            ROM_METADATA_LEN_NO_FILENAME
        } * num_roms;

        rom_metadata_len
    }

    /// Writes ROM metadata structs for all ROMs in this set and store off
    /// offsets to them.
    ///
    /// Returns the number of bytes written and also pointers to each, so
    /// that the array of ROM pointers can be written.
    pub fn write_rom_metadata(
        &self,
        buf: &mut [u8],
        rom_filename_ptrs: &[u32],
        rom_metadata_ptrs: &mut [u32],
        include_filenames: bool,
    ) -> Result<usize> {
        let num_roms = self.roms.len();

        // Check enough buffer space
        let expected_len = self.roms_metadata_len(include_filenames);
        if buf.len() < expected_len {
            return Err(Error::BufferTooSmall {
                location: "write_rom_metadata1",
                expected: expected_len,
                actual: buf.len(),
            });
        }

        // Check enough space for pointers
        if rom_metadata_ptrs.len() < num_roms {
            return Err(Error::BufferTooSmall {
                location: "write_rom_metadata2",
                expected: num_roms,
                actual: rom_metadata_ptrs.len(),
            });
        }

        let mut offset = 0;

        // Write ROM metadata.
        for (ii, rom) in self.roms.iter().enumerate() {
            // Set up the pointer to be returned first
            rom_metadata_ptrs[ii] = offset as u32;

            // Write the rom_type
            buf[offset] = rom.rom_type_c_enum_val();
            offset += 1;

            // Write the CS states
            buf[offset] = rom.cs_config.cs1_logic().c_enum_val();
            offset += 1;
            buf[offset] = rom.cs_config.cs2_logic().map_or(2, |cs| cs.c_enum_val());
            offset += 1;
            buf[offset] = rom.cs_config.cs3_logic().map_or(2, |cs| cs.c_enum_val());
            offset += 1;

            // Add filename if required
            if include_filenames {
                let rom_filename_ptr = rom_filename_ptrs
                    .get(rom.index())
                    .copied()
                    .ok_or_else(|| Error::MissingPointer { id: rom.index() })?;
                buf[offset..offset + 4].copy_from_slice(&rom_filename_ptr.to_le_bytes());
                offset += 4;
            }
        }

        Ok(offset)
    }

    /// Writes the array of pointers to each ROM metadata struct.  Must be
    /// called after [`Self::write_rom_metadata()`].
    pub fn write_rom_pointer_array(
        &self,
        buf: &mut [u8],
        rom_metadata_ptrs: &[u32],
    ) -> Result<usize> {
        let num_roms = self.roms.len();

        // Check enough buffer space
        let expected_len = 4 * num_roms;
        if buf.len() < expected_len {
            return Err(Error::BufferTooSmall {
                location: "write_rom_pointer_array",
                expected: expected_len,
                actual: buf.len(),
            });
        }

        // Check enough pointers
        if rom_metadata_ptrs.len() < num_roms {
            return Err(Error::MissingPointer {
                id: rom_metadata_ptrs.len(),
            });
        }

        let mut offset = 0;

        // Write the array of pointers
        for ii in rom_metadata_ptrs.iter() {
            buf[offset..offset + 4].copy_from_slice(&ii.to_le_bytes());
            offset += 4;
        }

        Ok(offset)
    }

    /// Writes the actual set metadata for this set.  This function must be
    /// called for each set one after the other, in order of set ID, as it
    /// must write an array of sets.
    pub fn write_set_metadata(
        &self,
        buf: &mut [u8],
        data_ptr: u32,
        rom_array_ptr: u32,
        family: &McuFamily,
    ) -> Result<usize> {
        // Check enough buffer space
        let expected_len = Self::rom_set_metadata_len();
        if buf.len() < expected_len {
            return Err(Error::BufferTooSmall {
                location: "write_set_metadata",
                expected: expected_len,
                actual: buf.len(),
            });
        }

        let mut offset = 0;

        // Write the ROM image(s) data pointer
        buf[offset..offset + 4].copy_from_slice(&data_ptr.to_le_bytes());
        offset += 4;

        // Write the ROM data size
        let data_size = self.image_size(family) as u32;
        buf[offset..offset + 4].copy_from_slice(&data_size.to_le_bytes());
        offset += 4;

        // Write the ROM data pointer
        buf[offset..offset + 4].copy_from_slice(&rom_array_ptr.to_le_bytes());
        offset += 4;

        // Write the nubmer of ROMs in this set
        let num_roms = self.roms.len() as u8;
        buf[offset] = num_roms;
        offset += 1;

        // Write the serving algorithm
        let algorithm = self.serve_alg().c_enum_value();
        buf[offset] = algorithm;
        offset += 1;

        // Write the multi-ROM CS state
        let multi_cs_state = self.multi_cs_logic()?.c_enum_val();
        buf[offset] = multi_cs_state;
        offset += 1;

        // Write a pad byte
        buf[offset] = 0;
        offset += 1;

        assert_eq!(
            offset, expected_len,
            "Internal error: offset does not match expected length"
        );

        Ok(offset)
    }

    pub const fn rom_set_metadata_len() -> usize {
        ROM_SET_METADATA_LEN
    }

    pub fn serve_alg(&self) -> ServeAlg {
        self.serve_alg
    }
}
