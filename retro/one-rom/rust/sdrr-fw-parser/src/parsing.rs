// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! sdrr-fw-parser
//!
//! Contains code and internal structures for parsing the SDRR firmware

use deku::prelude::*;
use static_assertions::const_assert_eq;

use crate::Reader;
use crate::{MAX_VERSION_MAJOR, MAX_VERSION_MINOR, MAX_VERSION_PATCH};
use crate::{McuLine, McuStorage, SdrrCsState, SdrrRomType, SdrrServe};
use crate::{SdrrExtraInfo, SdrrPins, SdrrRomInfo, SdrrRomSet, SdrrMcuPort};

#[cfg(not(feature = "std"))]
use alloc::{format, string::String, vec, vec::Vec};

// Maximum length of strings and bits of strings read from firmware
const MAX_STRING_LEN: usize = 1024;
const STRING_READ_CHUNK_SIZE: usize = 64;

#[derive(Debug, DekuRead, DekuWrite)]
#[deku(endian = "little", magic = b"sdrr")]
// Used internally to construct [`SdrrRuntimeInfo`]
pub(crate) struct SdrrRuntimeInfoHeader {
    pub runtime_info_size: u8,
    pub image_sel: u8,
    pub rom_set_index: u8,
    pub count_rom_access: u8,
    #[deku(endian = "little")]
    pub access_count: u32,
    #[deku(endian = "little")]
    pub rom_table_ptr: u32,
    #[deku(endian = "little")]
    pub rom_table_size: u32,
}

impl SdrrRuntimeInfoHeader {
    // Cannot assert this against SdrrInfoHeader size, as contains Vecs, which
    // increase its size.
    const SDRR_RUNTIME_INFO_HEADER_SIZE: usize = 20;

    // Offset of the access count field in the runtime info header
    const ACCESS_COUNT_OFFSET: usize = 8;

    pub(crate) const fn size() -> usize {
        // Rrust struct size ignored the magic bytes
        const_assert_eq!(
            core::mem::size_of::<SdrrRuntimeInfoHeader>(),
            SdrrRuntimeInfoHeader::SDRR_RUNTIME_INFO_HEADER_SIZE - 4
        );
        Self::SDRR_RUNTIME_INFO_HEADER_SIZE
    }

    pub(crate) const fn access_count_offset() -> usize {
        Self::ACCESS_COUNT_OFFSET
    }
}

#[derive(Debug, DekuRead, DekuWrite)]
#[deku(endian = "little", magic = b"SDRR")]
// Used internally to construct [`SdrrInfo`]
//
// Reflects `sdrr_info_t` from `sdrr/include/config_base.h`
pub(crate) struct SdrrInfoHeader {
    #[deku(endian = "little")]
    pub major_version: u16,
    #[deku(endian = "little")]
    pub minor_version: u16,
    #[deku(endian = "little")]
    pub patch_version: u16,
    #[deku(endian = "little")]
    pub build_number: u16,
    #[deku(endian = "little")]
    pub build_date_ptr: u32,
    #[deku(bytes = "8")]
    pub commit: [u8; 8],
    #[deku(endian = "little")]
    pub hw_rev_ptr: u32,
    pub stm_line: McuLine,
    pub stm_storage: McuStorage,
    #[deku(endian = "little")]
    pub freq: u16,
    pub overclock: u8,
    pub swd_enabled: u8,
    pub preload_image_to_ram: u8,
    pub bootloader_capable: u8,
    pub status_led_enabled: u8,
    pub boot_logging_enabled: u8,
    pub mco_enabled: u8,
    pub rom_set_count: u8, // Deprecated as of v0.5.0
    pub count_rom_access: u8,
    #[deku(pad_bytes_before = "1")]
    #[deku(endian = "little")]
    pub rom_sets_ptr: u32, // Changed as of v0.5.0 to be metadata pointer
    #[deku(endian = "little")]
    pub pins_ptr: u32,
    #[deku(bytes = "4")]
    pub boot_config: [u8; 4],
    pub extra_ptr: u32,
    pub _post: [u8; 4],
}

impl SdrrInfoHeader {
    // Cannot assert this against SdrrInfoHeader size, as contains Vecs, which
    // increase its size.
    const SDRR_INFO_HEADER_SIZE: usize = 64;

    pub(crate) const fn size() -> usize {
        Self::SDRR_INFO_HEADER_SIZE
    }

    // Indicates whether filenames present on ROM info structures
    // Always true for v0.5.1 and later
    // For earlier versions, depends on boot_logging_enabled flag.
    // Note however, even if included, they may be null pointers, or 0xFFFFFFFF
    // pointers
    pub(crate) fn filenames_enabled(&self) -> bool {
        if (self.major_version > 0) || ((self.minor_version == 5) && (self.patch_version >= 1)) {
            true
        } else {
            self.boot_logging_enabled != 0
        }
    }
}

// Used internally to construct SdrrExtraInfo
//
// Reflects `sdrr_extra_info_t` from `sdrr/include/config_base.h`
#[derive(Debug, DekuRead, DekuWrite)]
pub(crate) struct SdrrExtraInfoHeader {
    #[deku(endian = "little")]
    pub rtt_ptr: u32,

    pub usb_dfu: u8,
    pub usb_port: u8,
    pub vbus_pin: u8,
    pub reserved1: [u8; 1],

    pub _post: [u8; 248],
}

impl SdrrExtraInfoHeader {
    // Cannot assert this against SdrrExtraInfoHeader size, as contains Vecs, which
    // increase its size.
    const EXTRA_INFO_HEADER_SIZE: usize = 256;

    pub(crate) const fn size() -> usize {
        const_assert_eq!(
            core::mem::size_of::<SdrrExtraInfoHeader>(),
            SdrrExtraInfoHeader::EXTRA_INFO_HEADER_SIZE
        );
        Self::EXTRA_INFO_HEADER_SIZE
    }
}

#[derive(Debug, DekuRead, DekuWrite)]
#[deku(endian = "little", magic = b"ONEROM_METADATA\0")]
// Used internally to construct OneRomMetadataHeader
//
// Reflects onerom_metadata_header_t from `sdrr/include/config_base.h`
pub(crate) struct OneRomMetadataHeaderInternal {
    #[deku(endian = "little")]
    pub version: u32,
    #[deku(pad_bytes_after = "3")]
    pub rom_set_count: u8,
    #[deku(endian = "little")]
    pub rom_sets_ptr: u32,
    pub _reserved: [u8; 228],
}

impl OneRomMetadataHeaderInternal {
    // Cannot assert this against SdrrInfoHeader size, as contains Vecs, which
    // increase its size.
    const ONE_ROM_METADATA_HEADER_SIZE: usize = 256;

    pub(crate) const fn size() -> usize {
        Self::ONE_ROM_METADATA_HEADER_SIZE
    }
}

// Information about a specific ROM set
//
// Reflects `sdrr_rom_set_info_t` from `sdrr/include/config_base.h`
//
// Used internally to construct [`SdrrRomSet`]
#[derive(Debug, DekuRead, DekuWrite)]
pub(crate) struct SdrrRomSetHeader {
    #[deku(endian = "little")]
    pub data_ptr: u32,
    #[deku(endian = "little")]
    pub size: u32,
    #[deku(endian = "little")]
    pub roms_ptr: u32,
    pub rom_count: u8,
    pub serve: SdrrServe,
    #[deku(pad_bytes_after = "1")]
    pub multi_rom_cs1_state: SdrrCsState,
}

impl SdrrRomSetHeader {
    // Cannot assert this against SdrrRomSetHeader size, as contains Vecs, which
    // increase its size.
    const ROM_SET_HEADER_SIZE: usize = 16;

    pub(crate) const fn size() -> usize {
        const_assert_eq!(
            core::mem::size_of::<SdrrRomSetHeader>(),
            SdrrRomSetHeader::ROM_SET_HEADER_SIZE
        );
        Self::ROM_SET_HEADER_SIZE
    }
}

// Contains information about a specific ROM image
//
// This version is used when the BOOT_LOGGING is not defined in the C code
//
// Reflects `sdrr_rom_info_t` from `sdrr/include/config_base.h`
//
// Only used internally
#[derive(Debug, DekuRead, DekuWrite)]
struct SdrrRomInfoBasic {
    pub rom_type: SdrrRomType,
    pub cs1_state: SdrrCsState,
    pub cs2_state: SdrrCsState,
    pub cs3_state: SdrrCsState,
}

impl SdrrRomInfoBasic {
    const ROM_INFO_BASIC_SIZE: usize = 4;
    pub(crate) fn size() -> usize {
        const_assert_eq!(
            core::mem::size_of::<SdrrRomInfoBasic>(),
            SdrrRomInfoBasic::ROM_INFO_BASIC_SIZE
        );
        Self::ROM_INFO_BASIC_SIZE
    }
}

// Contains information about a specific ROM image
//
// This version is used when the BOOT_LOGGING is defined in the C code
//
// Reflects `sdrr_rom_info_t` from `sdrr/include/config_base.h`
//
// Only used internally
#[derive(Debug, DekuRead, DekuWrite)]
struct SdrrRomInfoWithLogging {
    pub rom_type: SdrrRomType,
    pub cs1_state: SdrrCsState,
    pub cs2_state: SdrrCsState,
    pub cs3_state: SdrrCsState,
    #[deku(endian = "little")]
    pub filename_ptr: u32,
}

impl SdrrRomInfoWithLogging {
    const ROM_INFO_WITH_LOGGING_SIZE: usize = 8;
    pub(crate) fn size() -> usize {
        const_assert_eq!(
            core::mem::size_of::<SdrrRomInfoWithLogging>(),
            SdrrRomInfoWithLogging::ROM_INFO_WITH_LOGGING_SIZE
        );
        Self::ROM_INFO_WITH_LOGGING_SIZE
    }
}

/// Parse and validate runtime information from buffer
pub(crate) fn parse_and_validate_runtime_info(
    data: &[u8],
) -> Result<SdrrRuntimeInfoHeader, String> {
    if data.len() < SdrrRuntimeInfoHeader::size() {
        return Err("Runtime info data too small".into());
    }

    let (_, header) = SdrrRuntimeInfoHeader::from_bytes((data, 0))
        .map_err(|e| format!("Failed to parse runtime info header: {}", e))?;

    if header.runtime_info_size < SdrrRuntimeInfoHeader::size() as u8 {
        return Err(format!(
            "Invalid runtime info size: {} < {}",
            header.runtime_info_size,
            SdrrRuntimeInfoHeader::size()
        ));
    }

    Ok(header)
}

/// Parse and validate SDRR header from buffer
pub(crate) fn parse_and_validate_header(data: &[u8]) -> Result<SdrrInfoHeader, String> {
    if data.len() < SdrrInfoHeader::size() {
        return Err("Header data too small".into());
    }

    let (_, mut header) = SdrrInfoHeader::from_bytes((data, 0))
        .map_err(|e| format!("Failed to parse header: {}", e))?;

    // Validate version
    if header.major_version > MAX_VERSION_MAJOR
        || (header.major_version == MAX_VERSION_MAJOR && header.minor_version > MAX_VERSION_MINOR)
        || (header.major_version == MAX_VERSION_MAJOR
            && header.minor_version == MAX_VERSION_MINOR
            && header.patch_version > MAX_VERSION_PATCH)
    {
        return Err(format!(
            "One ROM firmware version v{}.{}.{} unsupported - max version v{}.{}.{}",
            header.major_version,
            header.minor_version,
            header.patch_version,
            MAX_VERSION_MAJOR,
            MAX_VERSION_MINOR,
            MAX_VERSION_PATCH
        ));
    }

    if header.major_version == 0 && header.minor_version < 4 {
        // Extra info and _post fields are invalid - re-initialize them.
        header.extra_ptr = 0xFFFFFFFF;
        header._post = [0xFF; 4];
    }

    Ok(header)
}

/// Read a null-terminated string from the given pointer
pub(crate) async fn read_string_at_ptr<R: Reader>(
    reader: &mut R,
    ptr: u32,
    base_addr: u32,
) -> Result<String, String> {
    if ptr < base_addr {
        return Err(format!("Invalid pointer: 0x{:08X}", ptr));
    }

    let mut result = Vec::new();
    let mut addr = ptr;
    let mut buf = [0u8; STRING_READ_CHUNK_SIZE];

    loop {
        let chunk_size = buf.len().min(MAX_STRING_LEN - result.len());
        reader
            .read(addr, &mut buf[..chunk_size])
            .await
            .map_err(|_| format!("Failed to read string at 0x{:08X}", ptr))?;

        if let Some(null_pos) = buf[..chunk_size].iter().position(|&b| b == 0) {
            result.extend_from_slice(&buf[..null_pos]);
            break;
        }

        result.extend_from_slice(&buf[..chunk_size]);
        addr += chunk_size as u32;

        if result.len() >= 1024 {
            return Err("String too long (>1KB)".into());
        }
    }

    String::from_utf8(result).map_err(|_| "Invalid UTF-8 string".into())
}

pub(crate) async fn read_extra_info<R: Reader>(
    reader: &mut R,
    ptr: u32,
    base_addr: u32,
) -> Result<SdrrExtraInfo, String> {
    if ptr < base_addr {
        return Err(format!("ROM Extra Info invalid pointer: {ptr:#010X}"));
    }

    let mut buf = [0u8; SdrrExtraInfoHeader::size()];
    reader
        .read(ptr, &mut buf)
        .await
        .map_err(|_| format!("Failed to read extra info at 0x{:08X}", ptr))?;

    let (_, header) = SdrrExtraInfoHeader::from_bytes((&buf, 0))
        .map_err(|e| format!("Failed to parse extra info: {}", e))?;

    let usb_port = SdrrMcuPort::from(header.usb_port);
    let vbus_pin = header.vbus_pin;

    Ok(SdrrExtraInfo {
        rtt_ptr: header.rtt_ptr,
        usb_dfu: header.usb_dfu != 0,
        usb_port,
        vbus_pin,
    })
}

/// Read OneRomMetadataHeaderInfo
pub(crate) async fn read_one_rom_metadata_header_info<R: Reader>(
    reader: &mut R,
    ptr: u32,
    base_addr: u32,
) -> Result<OneRomMetadataHeaderInternal, String> {
    if ptr < base_addr {
        return Err(format!(
            "Failed to read One ROM metadata header as pointer invalid {ptr:#010X}"
        ));
    }

    let mut buf = [0u8; OneRomMetadataHeaderInternal::size()];
    reader
        .read(ptr, &mut buf)
        .await
        .map_err(|_| format!("Failed to read One ROM metadata header at {ptr:#010X}"))?;

    let (_, metadata) = OneRomMetadataHeaderInternal::from_bytes((&buf, 0))
        .map_err(|e| format!("Failed to parse One ROM metadata header: {e}"))?;

    Ok(metadata)
}

/// Read ROM sets from firmware
pub(crate) async fn read_rom_sets<R: Reader>(
    reader: &mut R,
    info_header: &SdrrInfoHeader,
    base_addr: u32,
) -> Result<Vec<SdrrRomSet>, String> {
    let ptr = info_header.rom_sets_ptr;
    let count = info_header.rom_set_count;

    if count == 0 {
        return Ok(Vec::new());
    }

    if ptr < base_addr {
        return Err(format!(
            "ROM set pointer {ptr:#010X} is below base address {base_addr:#010X}"
        ));
    }

    let mut rom_sets = Vec::with_capacity(count as usize);

    for i in 0..count {
        let header_addr = ptr + (i as u32 * SdrrRomSetHeader::size() as u32);

        // Read ROM set header
        let mut header_buf = [0u8; SdrrRomSetHeader::size()];
        reader
            .read(header_addr, &mut header_buf)
            .await
            .map_err(|_| format!("Failed to read ROM set header {}", i))?;

        let (_, header) = SdrrRomSetHeader::from_bytes((&header_buf, 0))
            .map_err(|e| format!("Failed to parse ROM set header {}: {}", i, e))?;

        // Read ROM infos
        let roms = read_rom_infos(reader, info_header, &header, base_addr).await?;

        // Note: We don't read the ROM data itself - just store where it is
        rom_sets.push(SdrrRomSet {
            data_ptr: header.data_ptr, // Store pointer, not data
            size: header.size,
            roms,
            rom_count: header.rom_count,
            serve: header.serve,
            multi_rom_cs1_state: header.multi_rom_cs1_state,
        });
    }

    Ok(rom_sets)
}

// Read ROM info structures
async fn read_rom_infos<R: Reader>(
    reader: &mut R,
    info_header: &SdrrInfoHeader,
    rom_set_header: &SdrrRomSetHeader,
    base_addr: u32,
) -> Result<Vec<SdrrRomInfo>, String> {
    let ptr = rom_set_header.roms_ptr;
    let count = rom_set_header.rom_count;

    if count == 0 {
        return Ok(Vec::new());
    }

    if ptr < base_addr {
        return Err(format!(
            "ROM infos pointer {ptr:#010X} is below base address {base_addr:#010X}"
        ));
    }

    let mut rom_infos = Vec::with_capacity(count as usize);

    for i in 0..count {
        // Read pointer to ROM info
        let ptr_addr = ptr + (i as u32 * core::mem::size_of::<u32>() as u32);
        let mut ptr_buf = [0u8; core::mem::size_of::<u32>()];
        reader
            .read(ptr_addr, &mut ptr_buf)
            .await
            .map_err(|_| format!("Failed to read ROM info pointer {}", i))?;

        let rom_info_ptr = u32::from_le_bytes(ptr_buf);

        // Read the ROM info itself
        let info_size = if info_header.filenames_enabled() {
            SdrrRomInfoWithLogging::size()
        } else {
            SdrrRomInfoBasic::size()
        };
        let mut info_buf = vec![0u8; info_size];
        reader
            .read(rom_info_ptr, &mut info_buf)
            .await
            .map_err(|_| format!("Failed to read ROM info {}", i))?;

        let rom_info = if info_header.filenames_enabled() {
            let (_, info) = SdrrRomInfoWithLogging::from_bytes((&info_buf, 0))
                .map_err(|e| format!("Failed to parse ROM info with logging {}: {}", i, e))?;

            // This test sets filename to None if pointer invalid (for example 0)
            let filename = if info.filename_ptr >= base_addr && info.filename_ptr != 0xFFFFFFFF {
                read_string_at_ptr(reader, info.filename_ptr, base_addr)
                    .await
                    .ok()
            } else {
                None
            };

            SdrrRomInfo {
                rom_type: info.rom_type,
                cs1_state: info.cs1_state,
                cs2_state: info.cs2_state,
                cs3_state: info.cs3_state,
                filename,
            }
        } else {
            let (_, info) = SdrrRomInfoBasic::from_bytes((&info_buf, 0))
                .map_err(|e| format!("Failed to parse ROM info basic {}: {}", i, e))?;

            SdrrRomInfo {
                rom_type: info.rom_type,
                cs1_state: info.cs1_state,
                cs2_state: info.cs2_state,
                cs3_state: info.cs3_state,
                filename: None,
            }
        };

        rom_infos.push(rom_info);
    }

    Ok(rom_infos)
}

/// Read pin configuration
pub(crate) async fn read_pins<R: Reader>(
    reader: &mut R,
    ptr: u32,
    base_addr: u32,
) -> Result<SdrrPins, String> {
    if ptr < base_addr {
        return Err(format!("Invalid pins pointer: 0x{:08X}", ptr));
    }

    let mut pins_buf = [0u8; SdrrPins::size()];
    reader
        .read(ptr, &mut pins_buf)
        .await
        .map_err(|_| "Failed to read pins data")?;

    SdrrPins::from_bytes((&pins_buf, 0))
        .map_err(|e| format!("Failed to parse pins: {}", e))
        .map(|(_, pins)| pins)
}
