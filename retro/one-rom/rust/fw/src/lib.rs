// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

pub mod args;
pub mod error;
pub mod net;

pub use error::Error;

#[allow(unused_imports)]
use log::{debug, error, info, trace, warn};
use std::collections::HashMap;
use std::io::Write;

use onerom_config::fw::FirmwareProperties;
use onerom_gen::builder::{Builder, FileData};
use onerom_gen::{FIRMWARE_SIZE, MAX_METADATA_LEN};

use net::{fetch_rom_file, fetch_rom_file_async};

pub fn validate_sizes(
    fw_props: &FirmwareProperties,
    firmware_data: &[u8],
    metadata: &Option<Vec<u8>>,
    image_data: &Option<Vec<u8>>,
) -> Result<(), Error> {
    let mut total_size = 0;

    let fw_size = firmware_data.len();
    debug!("Firmware size: {} bytes", fw_size);
    if fw_size > FIRMWARE_SIZE {
        return Err(Error::too_large(
            "Firmware".to_string(),
            fw_size,
            FIRMWARE_SIZE,
        ));
    }
    total_size += fw_size;

    if let Some(meta) = metadata {
        // Padding after firmware
        total_size += FIRMWARE_SIZE - total_size;

        let meta_size = meta.len();
        debug!("Metadata size: {} bytes", meta_size);
        if meta_size > MAX_METADATA_LEN {
            return Err(Error::too_large(
                "Metadata".to_string(),
                meta_size,
                MAX_METADATA_LEN,
            ));
        }
        total_size += meta_size;
    }

    if let Some(image) = image_data {
        // Padding after metadata
        total_size += MAX_METADATA_LEN + FIRMWARE_SIZE - total_size;

        let image_size = image.len();
        debug!("Image data size: {} bytes", image_size);
        total_size += image_size;
    }

    let max_size = fw_props.mcu_variant().flash_storage_bytes();
    debug!(
        "Total firmware size: {} bytes (max {})",
        total_size, max_size
    );
    debug!("MCU flash size: {} bytes", max_size);
    if total_size > max_size {
        return Err(Error::too_large(
            "Total firmware".to_string(),
            total_size,
            max_size,
        ));
    }

    Ok(())
}

pub fn create_firmware(
    out_path: &str,
    firmware_data: Vec<u8>,
    metadata: Option<Vec<u8>>,
    image_data: Option<Vec<u8>>,
) -> Result<usize, Error> {
    let mut total_size = 0;

    // Open file
    let mut out_file = std::fs::File::create(out_path).map_err(Error::write)?;

    // Output firmware data
    let firmware_size = firmware_data.len();
    assert!(firmware_size <= FIRMWARE_SIZE);
    let pad_size = FIRMWARE_SIZE - firmware_size;
    out_file.write_all(&firmware_data).map_err(Error::write)?;
    total_size += firmware_size;
    debug!("Wrote {} bytes of firmware", firmware_size);

    if metadata.is_none() {
        // Cannot have image data without metadata
        assert!(image_data.is_none());
        return Ok(total_size);
    }

    // Pad to beginning of metadata
    out_file
        .write_all(&vec![0xFF; pad_size])
        .map_err(Error::write)?;
    total_size += pad_size;
    debug!("Wrote {} bytes of padding after firmware", pad_size);

    // Write metadata
    assert!(total_size == FIRMWARE_SIZE);
    let metadata = metadata.unwrap();
    let metadata_size = metadata.len();
    assert!(metadata_size <= MAX_METADATA_LEN);
    out_file.write_all(&metadata).map_err(Error::write)?;
    total_size += metadata_size;
    debug!("Wrote {} bytes of metadata", metadata_size);

    if image_data.is_none() {
        return Ok(total_size);
    }

    // Pad to beginning of image data
    let pad_size = MAX_METADATA_LEN - metadata_size;
    debug!("Adding {} bytes of padding before image data", pad_size);
    out_file
        .write_all(&vec![0xFF; pad_size])
        .map_err(Error::write)?;
    total_size += pad_size;
    debug!("Wrote {} bytes of padding after metadata", pad_size);

    // Write image data
    assert!(total_size == FIRMWARE_SIZE + MAX_METADATA_LEN);
    let image_data = image_data.unwrap();
    let image_size = image_data.len();
    out_file.write_all(&image_data).map_err(Error::write)?;
    total_size += image_size;
    debug!("Wrote {} bytes of image data", image_size);

    Ok(total_size)
}

pub fn get_rom_files(builder: &mut Builder) -> Result<(), Error> {
    // Get firmware files
    let file_specs = builder.file_specs();
    let mut cached_files: HashMap<String, Vec<u8>> = HashMap::new();
    for spec in file_specs {
        let source = spec.source;
        let extract = spec.extract;

        // See if we hae the file in our cache
        let cache = if let Some(data) = cached_files.get(&source) {
            data.as_slice()
        } else {
            &[]
        };

        let (data, cache) = fetch_rom_file(&source, cache, extract, true)?;

        builder
            .add_file(FileData { id: spec.id, data })
            .map_err(Error::build)?;

        // Cache the returned file
        if !cache.is_empty() {
            cached_files.insert(source, cache);
        }
    }

    Ok(())
}

pub async fn get_rom_files_async(builder: &mut Builder) -> Result<(), Error> {
    // Get firmware files
    let file_specs = builder.file_specs();
    let mut cached_files: HashMap<String, Vec<u8>> = HashMap::new();
    for spec in file_specs {
        let source = spec.source;
        let extract = spec.extract;

        // See if we hae the file in our cache
        let cache = if let Some(data) = cached_files.get(&source) {
            data.as_slice()
        } else {
            &[]
        };

        let (data, cache) = fetch_rom_file_async(&source, cache, extract, true).await?;

        builder
            .add_file(FileData { id: spec.id, data })
            .map_err(Error::build)?;

        // Cache the returned file
        if !cache.is_empty() {
            cached_files.insert(source, cache);
        }
    }

    Ok(())
}

pub fn read_rom_config(rom_config_filename: &str) -> Result<String, Error> {
    // Load the config file
    std::fs::read_to_string(rom_config_filename).map_err(Error::read)
}
