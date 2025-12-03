// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! sdrr-gen - Main entry point for the SDRR generator.
//!
//! Generates files required to build main SDRR firmware for a particular set
//! of configuration and ROM images.

mod args;
mod config;
mod file;
mod fw;
mod generator;

use anyhow::{Context, Result};
use clap::Parser;
use std::io::{self, Write};

use onerom_config::hw::BOARDS;

use args::Args;
use config::Config;
use file::load_rom_files;
use generator::generate_files;

fn main() -> Result<()> {
    let args = Args::parse();

    // If `list_hw_revs` is set, we don't need to process any other arguments,
    // just output the list and exit.
    if args.list_hw_revs() {
        return list_hw_revs();
    }

    // Create configuration
    let mut config = args
        .gen_config()
        .map_err(|e| anyhow::anyhow!("Configuration error: {}", e))?;

    // Validate it
    config
        .validate()
        .map_err(|e| anyhow::anyhow!("Configuration validation error: {}", e))?;

    // Check and confirm licences before proceeding
    confirm_licences(&config)?;

    // Load ROM files into RAM
    let roms = load_rom_files(&config).with_context(|| "Failed to load ROM files")?;
    let num_roms = roms.len();

    // Create ROM sets - validation already done in config.validate()
    let rom_sets = config
        .create_rom_sets(roms, config.serve_alg)
        .map_err(|e| anyhow::anyhow!("ROM set creation error: {}", e))?;

    // Log some progress
    println!(
        "- Successfully loaded {} ROM file(s) in {} set(s)",
        num_roms,
        rom_sets.len()
    );

    // Generate output files
    generate_files(&config, &rom_sets).with_context(|| "Failed to generate output files")?;

    println!(
        "Successfully transformed ROM images and generated output files in `{}/`",
        config.output_dir.display()
    );

    Ok(())
}

fn list_hw_revs() -> Result<()> {
    // List available hardware revisions
    let boards = BOARDS;
    if boards.is_empty() {
        println!("No hardware revisions found.");
    } else {
        println!("Available hardware revisions:");
        for board in boards {
            println!("  {}: {}", board.name(), board.description());
        }
    }
    Ok(())
}

fn confirm_licences(config: &Config) -> Result<()> {
    let licensed_roms: Vec<_> = config
        .roms
        .iter()
        .filter(|rom| rom.licence.is_some())
        .collect();

    if licensed_roms.is_empty() {
        return Ok(());
    }

    println!("Some ROM images require licence acceptance:");
    println!();

    for rom in &licensed_roms {
        let source = rom.extract.as_ref().unwrap_or(&rom.original_source);
        let filename = source.split('/').next_back().unwrap_or(source);

        println!("ROM: {}", filename);
        println!("Licence: {}", rom.licence.as_ref().unwrap());
        println!();
    }

    print!("Do you accept the licence terms for the above ROM(s)? (y/n): ");
    io::stdout().flush().unwrap();

    if config.auto_yes {
        println!("- Automatically accepting licence terms due to --yes flag.");
        return Ok(());
    }
    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .map_err(|e| anyhow::anyhow!("Failed to read user input: {}", e))?;

    let response = input.trim().to_lowercase();
    if response != "y" && response != "yes" {
        return Err(anyhow::anyhow!("licence terms not accepted. Aborting."));
    }

    println!("- Licence terms accepted. Continuing...");
    println!();
    Ok(())
}
