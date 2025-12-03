// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! Metadata generator for One ROM.
//!
//!

use alloc::vec;
use alloc::vec::Vec;

use onerom_config::hw::Board;

use crate::{Error, FIRMWARE_SIZE, METADATA_VERSION, Result, image::RomSet};

pub const PAD_METADATA_BYTE: u8 = 0xFF;

const HEADER_MAGIC: &[u8; 16] = b"ONEROM_METADATA\0";

// Metadata starts at 48KB from the start of flash.
const METADATA_START: u32 = FIRMWARE_SIZE as u32;

// ROM images start at 64KB from the start of flash.
const ROM_IMAGE_DATA_START: u32 = 65536;

/// Metadata max length
pub const MAX_METADATA_LEN: usize = 16384;

const METADATA_HEADER_LEN: usize = 256; // onerom_metadata_header_t

const METADATA_ROM_SET_OFFSET: usize = 24; // Offset of rom_set pointer in header

/// Metadata for One ROM firmware
#[derive(Debug, serde::Serialize, serde::Deserialize)]
pub struct Metadata {
    board: Board,
    rom_sets: Vec<RomSet>,
    filenames: bool,
}

impl Metadata {
    pub fn new(board: Board, rom_sets: Vec<RomSet>, filenames: bool) -> Self {
        Self {
            board,
            rom_sets,
            filenames,
        }
    }

    const fn header_len(&self) -> usize {
        METADATA_HEADER_LEN
    }

    const fn abs_metadata_start(&self) -> u32 {
        self.board.mcu_family().get_flash_base() + METADATA_START
    }

    const fn abs_rom_image_start(&self) -> u32 {
        self.board.mcu_family().get_flash_base() + ROM_IMAGE_DATA_START
    }

    /// Length of buffer required for metadata.
    pub fn metadata_len(&self) -> usize {
        // Size needs to include:
        // - Header (256 bytes) - onerom_metadata_header_t
        // - All ROM filenames - char[]
        // - All ROM set entries (16 bytes) - sdrr_rom_set_t
        // - Array of pointers to ROMs in each set (4 bytes per ROM)
        // - Each ROM entry (4-8 bytes) - sdrr_rom_info_t
        let len = self.header_len() + self.filenames_metadata_len() + self.sets_len();

        if len > MAX_METADATA_LEN {
            panic!(
                "Metadata too large: {} bytes (max {})",
                len, MAX_METADATA_LEN
            );
        }

        len
    }

    pub fn total_set_count(&self) -> usize {
        self.rom_sets.len()
    }

    // Total number of ROMs across all sets
    fn total_rom_count(&self) -> usize {
        self.rom_sets.iter().map(|rs| rs.roms().len()).sum()
    }

    // Total length, including null terminators, of all filenames
    fn filenames_metadata_len(&self) -> usize {
        let len = if !self.filenames {
            0
        } else {
            self.rom_sets
                .iter()
                .flat_map(|rs| rs.roms())
                .map(|rom| rom.filename().len() + 1)
                .sum()
        };
        if len % 4 != 0 {
            // Align to 4 bytes
            len + (4 - (len % 4))
        } else {
            len
        }
    }

    // Get total length of sets:
    // - Pointer to array of ROM pointers
    // - All ROM structs
    //
    // Does not include filename lengths
    fn sets_len(&self) -> usize {
        let mut total = 0;
        for set in &self.rom_sets {
            total += set.roms_metadata_len(self.filenames);
            total += set.roms().len() * 4;
        }

        total += self.rom_sets.len() * RomSet::rom_set_metadata_len();

        total
    }

    /// Writes all metadata to provided buffer.
    ///
    /// It is advisable to call [`Self::metadata_len`] first to ensure the
    /// buffer provided is large enough.  Also [`Self::total_set_count`] should
    /// be called to get the number of ROM sets, so the caller can allocate
    /// space for the returned ROM data pointers.
    ///
    /// The `rtn_rom_data_ptrs` slice provides offsets from the start of the ROM
    /// data location (flash_base + 64KB) for each ROM set.
    ///
    /// The caller should ensure that each ROM set data is written to the flash.
    pub fn write_all(&self, buf: &mut [u8], rtn_rom_data_ptrs: &mut [u32]) -> Result<usize> {
        // Check we have enough of a buffer.
        if self.metadata_len() > buf.len() {
            return Err(Error::BufferTooSmall {
                location: "write_all",
                expected: self.metadata_len(),
                actual: buf.len(),
            });
        }

        let mut offset = 0;

        // Write the header
        offset += self.write_header(&mut buf[offset..])?;

        // Write the filenames.
        let mut filename_ptrs = vec![0xFF_u32; self.total_rom_count()];
        if self.filenames {
            // Store off the offset where filenames start
            let filename_offset = offset;

            // write_filenames() fills in filename_ptrs, but starts at 0
            let filename_len = self.write_filenames(&mut buf[offset..], &mut filename_ptrs)?;
            offset += filename_len;

            // Need to correct filename pointers to be absolute addresses.
            // We need to add filename_offset plus the flash base
            for ptr in filename_ptrs.iter_mut() {
                *ptr += (filename_offset as u32) + self.abs_metadata_start();
            }

            if filename_len % 4 != 0 {
                // Align to 4 bytes
                let padding = 4 - (filename_len % 4);
                for _ in 0..padding {
                    buf[offset] = PAD_METADATA_BYTE;
                    offset += 1;
                }
            }

            assert_eq!(
                offset % 4,
                0,
                "Metadata offset not 4 byte aligned after writing filenames"
            );
        }

        // Pre-compute where the ROM set image data will live for each rom set
        // now, so we can fill in the pointers in each set.  This is from
        // the start of flash + 64KB.  We also set up a vec to hold offsets
        // from the start of the ROM image location to return from this
        // function.
        let mut rom_data_ptrs = vec![0u32; self.rom_sets.len()];
        let mut rom_data_ptr = self.abs_rom_image_start();
        let mut rtn_rom_data_ptr = 0;
        for (ii, set) in self.rom_sets.iter().enumerate() {
            rom_data_ptrs[ii] = rom_data_ptr;
            rtn_rom_data_ptrs[ii] = rtn_rom_data_ptr;
            let rom_data_size = set.image_size(&self.board.mcu_family());
            rom_data_ptr += rom_data_size as u32;
            rtn_rom_data_ptr += rom_data_size as u32;
        }

        // Write each set's ROM data, which need to return pointers to rom arrays.
        // This doesn't write the set itself - that comes last.
        let mut rom_array_ptrs = vec![Vec::new(); self.rom_sets.len()];
        for (ii, rom_set) in self.rom_sets.iter().enumerate() {
            // Each write_metadata() fills in rom_ptrs for that set
            let mut rom_metadata_ptrs = vec![0u32; rom_set.roms().len()];
            let len = rom_set.write_rom_metadata(
                &mut buf[offset..],
                &filename_ptrs,
                &mut rom_metadata_ptrs,
                self.filenames,
            )?;

            // Now update this set's array of ROM pointers
            for ptr in rom_metadata_ptrs.iter_mut() {
                *ptr += offset as u32 + self.abs_metadata_start();
            }
            rom_array_ptrs[ii] = rom_metadata_ptrs;

            // Advance the offset
            offset += len;
        }

        // Next, write each of the ROM pointer arrays creating a vec of
        // actual pointers to each array, to include in each set.
        let mut actual_rom_array_ptrs = vec![0u32; self.rom_sets.len()];
        for (ii, rom_set) in self.rom_sets.iter().enumerate() {
            let len = rom_set.write_rom_pointer_array(&mut buf[offset..], &rom_array_ptrs[ii])?;
            actual_rom_array_ptrs[ii] = offset as u32 + self.abs_metadata_start();
            offset += len;
        }

        // Write each set struct - this will become an array of set structs.
        let first_rom_set_ptr = offset as u32 + self.abs_metadata_start();
        for (ii, rom_set) in self.rom_sets.iter().enumerate() {
            offset += rom_set.write_set_metadata(
                &mut buf[offset..],
                rom_data_ptrs[ii],
                actual_rom_array_ptrs[ii],
                &self.board.mcu_family(),
            )?;
        }

        // Finally, update the pointer to the first ROM set in the header.
        self.update_rom_set_ptr(&mut buf[..], first_rom_set_ptr)?;

        Ok(offset)
    }

    // Writes all ROM filenames to provided buffer.
    fn write_filenames(&self, buf: &mut [u8], ptrs: &mut [u32]) -> Result<usize> {
        if !self.filenames {
            return Ok(0);
        }

        if buf.len() < self.filenames_metadata_len() {
            return Err(crate::Error::BufferTooSmall {
                location: "write_filenames1",
                expected: self.filenames_metadata_len(),
                actual: buf.len(),
            });
        }

        let mut offset = 0;

        // Set up array of filename pointers.
        let num_roms = self.total_rom_count();
        if ptrs.len() < num_roms {
            return Err(crate::Error::BufferTooSmall {
                location: "write_filenames2",
                expected: num_roms,
                actual: ptrs.len(),
            });
        }

        for (ii, rom) in self.rom_sets.iter().flat_map(|rs| rs.roms()).enumerate() {
            assert_eq!(ii, rom.index());

            // Get the filename and its length
            let name_bytes = rom.filename().as_bytes();
            let len = name_bytes.len();

            // Store off the pointer
            ptrs[ii] = offset as u32;

            // Store the null terminated filename
            buf[offset..offset + len].copy_from_slice(name_bytes);
            offset += len;
            buf[offset] = 0;
            offset += 1;
        }
        Ok(offset)
    }

    fn write_header(&self, buf: &mut [u8]) -> Result<usize> {
        if buf.len() < METADATA_HEADER_LEN {
            return Err(crate::Error::BufferTooSmall {
                location: "write_header",
                expected: METADATA_HEADER_LEN,
                actual: buf.len(),
            });
        }

        let mut offset = 0;
        let len = 16;
        buf[0..offset + len].copy_from_slice(HEADER_MAGIC);
        offset += len;

        let len = 4;
        buf[offset..offset + len].copy_from_slice(&METADATA_VERSION.to_le_bytes());
        offset += len;

        let len = 1;
        buf[offset..offset + len].copy_from_slice(&[self.rom_sets.len() as u8]);
        offset += len;

        let len = 3;
        buf[offset..offset + len].copy_from_slice(&[0u8; 3]);
        offset += len;

        // We'll need to update this later
        let len = 4;
        assert_eq!(offset, METADATA_ROM_SET_OFFSET);
        buf[offset..offset + len].copy_from_slice(&0xFFFFFFFF_u32.to_le_bytes());
        offset += len;

        let len = 228;
        buf[offset..offset + len].copy_from_slice(&[0u8; 228]);
        offset += len;

        // Final sanity check
        assert_eq!(offset, self.header_len());

        Ok(offset)
    }

    fn update_rom_set_ptr(&self, buf: &mut [u8], ptr: u32) -> Result<()> {
        if buf.len() < (METADATA_ROM_SET_OFFSET + 4) {
            return Err(crate::Error::BufferTooSmall {
                location: "update_rom_set_ptr",
                expected: (METADATA_ROM_SET_OFFSET + 4),
                actual: buf.len(),
            });
        }

        // Pointer is at offset 20
        buf[METADATA_ROM_SET_OFFSET..METADATA_ROM_SET_OFFSET + 4]
            .copy_from_slice(&ptr.to_le_bytes());
        Ok(())
    }

    /// Returns the total size needed for all ROM images
    pub fn rom_images_size(&self) -> usize {
        self.rom_sets
            .iter()
            .map(|set| set.image_size(&self.board.mcu_family()))
            .sum()
    }

    /// Write all ROM images to buffer
    pub fn write_roms(&self, buf: &mut [u8]) -> Result<()> {
        // Validate buffer size
        if buf.len() < self.rom_images_size() {
            return Err(Error::BufferTooSmall {
                location: "write_roms",
                expected: self.rom_images_size(),
                actual: buf.len(),
            });
        }

        let mut offset = 0;
        for rom_set in &self.rom_sets {
            let size = rom_set.image_size(&self.board.mcu_family());

            // Fill buffer by calling get_byte for each address
            for addr in 0..size {
                buf[offset + addr] = rom_set.get_byte(addr, &self.board);
            }

            offset += size;
        }

        Ok(())
    }
}
