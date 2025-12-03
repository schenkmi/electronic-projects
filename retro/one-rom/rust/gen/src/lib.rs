// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! Generates firmware artifacts for One ROM.

#![no_std]

extern crate alloc;

pub mod builder;
pub mod image;
pub mod meta;

pub use builder::{Builder, Config, FileData, FileSpec, License, RomConfig, RomSetConfig};
pub use image::{CsConfig, CsLogic, Rom, RomSet, RomSetType, SizeHandling};
pub use image::{PAD_BLANK_BYTE, PAD_NO_ROM_BYTE};
pub use meta::{MAX_METADATA_LEN, Metadata, PAD_METADATA_BYTE};

use alloc::string::String;
use onerom_config::fw::ServeAlg;
use onerom_config::rom::RomType;

/// Version of metadata produced by this version of the crate
pub const METADATA_VERSION: u32 = 1;
const METADATA_VERSION_STR: &str = "1";

/// Firmware size reserved at the start of flash, before metadata
pub const FIRMWARE_SIZE: usize = 48 * 1024; // 48KB

/// Error type
#[derive(Debug, serde::Serialize, serde::Deserialize)]
pub enum Error {
    RightSize {
        size: usize,
    },
    RomTooSmall {
        index: usize,
        expected: usize,
        actual: usize,
    },
    DuplicationNotExactDivisor {
        rom_size: usize,
        expected_size: usize,
    },
    RomTooLarge {
        rom_size: usize,
        expected_size: usize,
    },
    BufferTooSmall {
        location: &'static str,
        expected: usize,
        actual: usize,
    },
    NoRoms,
    TooManyRoms {
        expected: usize,
        actual: usize,
    },
    TooFewRoms {
        expected: usize,
        actual: usize,
    },
    MissingCsConfig {
        line: &'static str,
    },
    MissingPointer {
        id: usize,
    },
    InvalidServeAlg {
        serve_alg: ServeAlg,
    },
    InconsistentCsLogic {
        first: CsLogic,
        other: CsLogic,
    },
    InvalidConfig {
        error: String,
    },
    UnsupportedConfigVersion {
        version: u32,
    },
    DuplicateFile {
        id: usize,
    },
    InvalidFile {
        id: usize,
        total: usize,
    },
    MissingFile {
        id: usize,
    },
    UnsupportedRomType {
        rom_type: RomType,
    },
    InvalidLicense {
        id: usize,
    },
    UnvalidatedLicense {
        id: usize,
    },
    BadLocation {
        id: usize,
        reason: String,
    }
}
type Result<T> = core::result::Result<T, Error>;

pub fn crate_version() -> &'static str {
    env!("CARGO_PKG_VERSION")
}

pub fn metadata_version() -> &'static str {
    METADATA_VERSION_STR
}
