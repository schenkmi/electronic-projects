//! One ROM Lab firmware - Logging routines

// Copyright (c) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT licence

#[allow(unused_imports)]
use log::{debug, error, info, trace, warn};

use onerom_database::{RomEntry, RomType};

use crate::rom::Id as RomId;

pub fn log_good_rom_match(entry: &RomEntry) {
    info!("ROM match found:");
    info!("  Name:        {}", entry.name());
    info!("  Part:        {}", entry.part());
    info!("  Type:        {}", entry.rom_type());
    info!("  Checksum:    {:#010x}", entry.sum());
    info!("  SHA1:        {}", hex::encode(entry.sha1()));
}

pub fn log_bad_rom_match(entry: &RomEntry, rom_type: &RomType) {
    info!("ROM mismatch found:");
    info!("  Name:        {}", entry.name());
    info!("  Part:        {}", entry.part());
    info!("  Expected:    {}", entry.rom_type());
    info!("  Found:       {rom_type}");
    info!("  Checksum:    {:#010x}", entry.sum());
    info!("  SHA1:        {}", hex::encode(entry.sha1()));
}

pub fn log_rom_id(id: &RomId) {
    info!("{}", id.rom_type().type_str());
    info!("  Chip Select: {}", id.rom_type().cs_str());
    info!("  Checksum:    {:#010x}", id.sum());
    info!("  SHA1:        {}", hex::encode(id.sha1()));
}

#[allow(dead_code)]
pub fn dump_buf(buf: &[u8]) {
    for (i, chunk) in buf.chunks(16).enumerate() {
        let addr = i * 16;

        // Pad chunk to 16 bytes for consistent formatting
        let mut line = [0u8; 16];
        line[..chunk.len()].copy_from_slice(chunk);
        let len = chunk.len();

        if len == 16 {
            debug!(
                "{:04x}:  {:02x} {:02x} {:02x} {:02x}  {:02x} {:02x} {:02x} {:02x}  {:02x} {:02x} {:02x} {:02x}  {:02x} {:02x} {:02x} {:02x}",
                addr,
                line[0],
                line[1],
                line[2],
                line[3],
                line[4],
                line[5],
                line[6],
                line[7],
                line[8],
                line[9],
                line[10],
                line[11],
                line[12],
                line[13],
                line[14],
                line[15]
            );
        } else {
            // Handle partial lines
            debug!("{addr:04x}:  partial line, {len} bytes");
        }
    }
}

pub fn init() {
    rtt_target::rtt_init_log!(
        log::LevelFilter::Debug,
        rtt_target::ChannelMode::NoBlockSkip,
        2048
    );
}
