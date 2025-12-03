// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! onerom-fw - Firmware generator for One ROM

use clap::Parser;
#[allow(unused_imports)]
use log::{debug, error, info, trace, warn};
use std::io::Write;

use onerom_config::fw::{FirmwareProperties, ServeAlg};
use onerom_gen::{Builder, License};

use onerom_fw::Error;
use onerom_fw::args::Args;
use onerom_fw::net::{Releases, fetch_license};
use onerom_fw::{create_firmware, get_rom_files, read_rom_config, validate_sizes};

fn main() {
    if let Err(e) = sub_main() {
        eprintln!();
        eprintln!("Firmware generation failed - details error information follows");
        eprintln!("---");
        eprintln!("{e}");
        std::process::exit(1);
    }
}

fn sub_main() -> Result<(), Error> {
    // Get args
    let mut args = Args::parse();

    // Enable logging
    init_logging(args.verbose);

    // Validate args
    if args.validate()? {
        return Ok(());
    }

    // Output version
    debug!(
        "One ROM CLI Firmware Generator v{}",
        env!("CARGO_PKG_VERSION")
    );

    // Get CLI args
    let version = args.fw.unwrap();
    let board = args.board.unwrap();
    let mcu = args.mcu.unwrap();
    let out_filename = args.out.as_ref().unwrap();
    let rom_config_filename = args.rom.as_ref();

    // Get firmware releases
    let releases = Releases::from_network()?;
    if releases.release(&version).is_none() {
        return Err(Error::release_not_found());
    }

    // Get the blank firmware image
    let firmware_data = releases.download_firmware(&version, &board, &mcu)?;

    // Build firmware properties
    let fw_props = FirmwareProperties::new(version, board, mcu, ServeAlg::default(), true).unwrap();

    // Load the config file
    let (metadata, image_data, desc) = if let Some(rom_config_filename) = rom_config_filename {
        debug!("Using ROM config file: {}", rom_config_filename);

        // Read ROM config file
        let config = read_rom_config(&rom_config_filename)?;

        // Create builder
        let mut builder = Builder::from_json(&config).map_err(Error::parse)?;

        // Accept any licenses
        let licenses = builder.licenses();
        for license in licenses {
            propose_license(&license)?;
            builder.accept_license(&license).map_err(Error::license)?;
        }

        // Get ROM files and feed into the builder
        get_rom_files(&mut builder)?;

        // Generate metadata/ROM images
        let (m, i) = builder.build(fw_props).map_err(Error::build)?;
        if i.len() > 0 {
            // Cannot have ROM image data without metadata
            assert!(m.len() > 0);
        }

        (Some(m), Some(i), Some(builder.description()))
    } else {
        println!("No ROM config specified, creating firmware with no metadata or image data");
        (None, None, None)
    };

    // Check everything fits
    validate_sizes(&fw_props, &firmware_data, &metadata, &image_data)?;

    // Create the firmware file
    let size = create_firmware(&out_filename, firmware_data, metadata, image_data)?;

    // Output success
    println!("---");
    println!(
        "Successfully created One ROM firmware:\n---\n- Version:  v{}.{}.{}\n- Board:    {}\n- MCU:      {}\n- Filename: {}\n- Size:     {} bytes",
        version.major(),
        version.minor(),
        version.patch(),
        board.name(),
        mcu.to_string().to_ascii_lowercase(),
        out_filename,
        size
    );

    // Output ROMs config
    if let Some(desc) = desc {
        println!("---\n{desc}");
    }

    println!("---");

    // Done
    Ok(())
}

fn propose_license(license: &License) -> Result<(), Error> {
    // Get license text
    debug!("License required: {}", license.url);
    let text = fetch_license(&license.url)?;

    // Output it
    println!("You must accept this license to proceed:");
    println!("---");
    println!("{}", text);
    println!("---");

    // Prompt user
    print!("Do you accept this license? (y/N): ");
    std::io::stdout().flush().map_err(Error::write)?;
    let mut input = String::new();
    std::io::stdin()
        .read_line(&mut input)
        .map_err(Error::read)?;
    let input = input.trim().to_lowercase();
    if input == "y" || input == "yes" {
        Ok(())
    } else {
        Err(Error::license_not_accepted())
    }
}

fn init_logging(verbose: bool) {
    let mut log_builder = env_logger::Builder::from_default_env();
    if verbose {
        log_builder.filter_level(log::LevelFilter::Debug);
    } else {
        log_builder.filter_level(log::LevelFilter::Info);
    }
    log_builder.format(|buf, record| {
        let level = format!("{}: ", record.level());
        writeln!(buf, "{:07}{}", level, record.args())
    });
    log_builder.init();
}
