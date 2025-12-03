//! One ROM Lab - ROM Database
//!
//! The primary approach taken to identifying ROMs is to use a SHA1 digest of
//! it.  If that fails to provide a match, we try a 32-bit summing checksum.
//!
//! This combination will always, uniquely, identify a ROM - in fact the SHA1
//! digest should.  This has the side effect of a unique ROM image needing a
//! single name and part number in the database.  If this turns out to be an
//! unsound assumption, we may need to add the concept of aliases.

// Copyright (c) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT licence

#![no_std]

extern crate alloc;

#[allow(unused_imports)]
use log::{debug, error, info, trace, warn};

use alloc::vec::Vec;
use core::num::Wrapping;
use hex_literal::hex;
use sha1::{Digest, Sha1};

pub mod types;
pub use types::{CsActive, RomType};

// Known ROM database
//
// - ROMs are in `roms/*.csv` files
// - See `scripts/url_checksum.py` for the script that generated the checksums
//   and SHA1 digests
include!(concat!(env!("OUT_DIR"), "/roms.rs"));

/// Type agonostic wrapping checksum function.  We typically only use the u32
/// version, as u16 and u8 values are the same, with the top bytes masked off.
pub fn checksum<T>(data: &[u8]) -> T
where
    T: Default + From<u8> + Copy,
    Wrapping<T>: core::ops::Add<Output = Wrapping<T>>,
{
    let mut checksum = Wrapping(T::default());
    for &byte in data {
        checksum = checksum + Wrapping(T::from(byte));
    }
    checksum.0
}

pub fn sha1_digest(data: &[u8]) -> [u8; 20] {
    let mut hasher = Sha1::new();
    hasher.update(data);
    let result = hasher.finalize();
    let mut sha1 = [0u8; 20];
    sha1.copy_from_slice(&result);
    sha1
}

/// A ROM database entry
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct RomEntry {
    // Human readable name for this ROM
    name: &'static str,

    // Part number for this ROM image, likely assigned by the OEM to the
    // original chip
    part: &'static str,

    // Wrapping 32-bit checksum of the ROM image.  If you require 16-bit or
    // 8-bit simply mask off the unnecessary bytes.
    sum: u32,

    // SHA1 digest for this ROM image.  In reality likely to be unique, except
    // where the same image is used for different ROM types (i.e. chip select
    // behaviour).
    sha1: [u8; 20],

    // The ROM type - both the model (2364/2332/2316) and the chip select line
    // behaviour.
    rom_type: RomType,
}

impl RomEntry {
    const fn new(
        name: &'static str,
        part: &'static str,
        sum: u32,
        sha1: [u8; 20],
        rom_type: RomType,
    ) -> Self {
        Self {
            name,
            part,
            sum,
            sha1,
            rom_type,
        }
    }

    /// Returns whether the given checksum matches this ROM image.
    pub fn matches_checksum(&self, sum: u32) -> bool {
        self.sum == sum
    }

    /// Returns whether the given SHA1 matches this ROM image.
    pub fn matches_sha1(&self, sha1: &[u8; 20]) -> bool {
        self.sha1 == *sha1
    }

    /// Returns the human readable name for this ROM.
    pub fn name(&self) -> &'static str {
        self.name
    }

    /// Returns the part number for this ROM, likely assigned by the OEM to
    /// the original chip
    pub fn part(&self) -> &'static str {
        self.part
    }

    /// Returns wrapping 8-bit checksum of the ROM image.
    pub fn sum8(&self) -> u8 {
        (self.sum & 0xFF) as u8
    }

    /// Returns wrapping 16-bit checksum of the ROM image.
    pub fn sum16(&self) -> u16 {
        (self.sum & 0xFFFF) as u16
    }

    /// Returns wrapping 32-bit checksum of the ROM image.
    pub fn sum(&self) -> u32 {
        self.sum
    }

    /// Returns the SHA1 digest for this ROM image.
    pub fn sha1(&self) -> &[u8; 20] {
        &self.sha1
    }

    /// Returns the ROM type for this ROM image.  Includes IC type (2364,
    /// 2332, 2316) and chip select line behaviour.
    pub fn rom_type(&self) -> RomType {
        self.rom_type
    }
}

#[allow(dead_code)]
fn identify_rom_checksum(sum: u32) -> impl Iterator<Item = &'static RomEntry> {
    ROMS.iter().filter(move |rom| rom.matches_checksum(sum))
}

fn identify_rom_sha1(sha1: &[u8; 20]) -> impl Iterator<Item = &'static RomEntry> {
    ROMS.iter().filter(move |rom| rom.matches_sha1(sha1))
}

/// Function to identify a ROM by SHA1.  We do not do checksum matching at all
/// because clashes are likely, and it complicates our logic (we have to only
/// do checksum matching if SHA1 fails for _all_ ROM types).
///
/// Returns a tuple of matching ROM entries and those that matched, but with
/// the wrong type.  These "bad" matches are likely due to chip select line
/// differences between the ROM tested and the information in the database.
pub fn identify_rom(
    rom_type: &RomType,
    _sum: u32,
    sha1: [u8; 20],
) -> (Vec<&'static RomEntry>, Vec<(&'static RomEntry, RomType)>) {
    let candidates = identify_rom_sha1(&sha1).collect::<Vec<_>>();

    let mut matches = Vec::new();
    let mut wrong_type_matches = Vec::new();

    for entry in candidates {
        if entry.rom_type == *rom_type {
            matches.push(entry);
        } else {
            wrong_type_matches.push((entry, *rom_type));
        }
    }

    (matches, wrong_type_matches)
}

/// Database errors
pub enum Error {
    /// Failed to parse the buffer into the requested type
    ParseError,
}
