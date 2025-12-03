// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

use clap::Parser;
#[allow(unused_imports)]
use log::{debug, error, info, trace, warn};

use onerom_config::fw::FirmwareVersion;
use onerom_config::hw::Board;
use onerom_config::mcu::Variant as McuVariant;

use crate::Error;
use crate::net::Releases;

#[derive(Parser, Debug)]
#[clap(
    name = "onerom-fw",
    about = "One ROM's CLI Firmware Generator",
    long_about = "One ROM's Command Line Firmware Generator\n\nAlternatively use https://onerom.org/prog/",
    version
)]
pub struct Args {
    /// List board types
    #[clap(
        long,
        long_help = "List supported board types",
        conflicts_with_all = &["board", "mcu", "rom", "out"],
        alias = "boards",
    )]
    pub list_boards: bool,

    /// List MCU variants
    #[clap(
        long,
        long_help = "List supported MCU variants",
        conflicts_with_all = &["board", "mcu", "rom", "out"],
        alias = "mcus",
    )]
    pub list_mcus: bool,

    /// List firmware versions
    #[clap(
        long,
        long_help = "List available firmware versions",
        conflicts_with_all = &["board", "mcu", "rom", "out"],
        alias = "versions",
    )]
    pub list_fw_versions: bool,

    /// Board type and revision
    #[clap(
        long,
        value_parser=board_value_parser,
        required_unless_present_any = &["list_boards", "list_mcus", "list_fw_versions"],
    )]
    pub board: Option<Board>,

    /// MCU variant
    #[clap(
        long,
        value_parser=mcu_value_parser,
        required_unless_present_any = &["list_boards", "list_mcus", "list_fw_versions"],
    )]
    pub mcu: Option<McuVariant>,

    /// Firmware version
    #[clap(
        short,
        long,
        long_help = "Firmware version to use (default latest)",
        value_parser=firmware_value_parser,
    )]
    pub fw: Option<FirmwareVersion>,

    /// ROM configuration JSON file
    #[clap(
        short,
        long,
        long_help = "ROM configuration JSON file.\nWithout this, a default firmware with no metadata or ROMs is generated.\nThis One ROM can then be updated later",
        value_parser
    )]
    pub rom: Option<String>,

    /// Output firmware binary filename
    #[clap(
        short,
        long,
        long_help = "Output firmware binary filename.\nIf not specified, a default name is used",
        value_parser
    )]
    pub out: Option<String>,

    /// Verbose output
    #[clap(short, long, action)]
    pub verbose: bool,
}

impl Args {
    pub fn validate(&mut self) -> Result<bool, Error> {
        // If listing, just list and exit
        let mut listed = false;
        if self.list_boards {
            listed = true;
            println!("Supported One ROM Boards: {}", board_values());
        }
        if self.list_mcus {
            listed = true;
            println!("Supported MCU Variants: {}", mcu_values());
        }
        if self.list_fw_versions {
            listed = true;
            let releases = Releases::from_network()?;
            let releases_str = releases
                .releases()
                .iter()
                .map(|r| r.version.as_str())
                .collect::<Vec<_>>()
                .join(", ");
            println!(
                "Available Firmware Versions (latest = {}): {}",
                releases.latest(),
                releases_str
            );
        }

        if listed {
            return Ok(true);
        }

        // Check required arguments
        if self.board.is_none() {
            return Err(Error::config("Board type is required".to_string()));
        }
        if self.mcu.is_none() {
            return Err(Error::config("MCU variant is required".to_string()));
        }

        // Check the board and MCU are compatible
        if self.board.as_ref().map(|b| b.mcu_family()) != self.mcu.as_ref().map(|m| m.family()) {
            return Err(Error::config(
                "MCU variant is not supported by the selected board".to_string(),
            ));
        }

        // Check the file exists if specified
        if let Some(ref rom_file) = self.rom {
            if !std::path::Path::new(rom_file).exists() {
                return Err(Error::config(format!(
                    "ROM configuration file `{}` does not exist",
                    rom_file
                )));
            }
        }

        // Check the release exists
        let releases = Releases::from_network()?;
        if let Some(version) = self.fw {
            debug!("Firmware version specified: {:?}", version);
            if releases.release(&version).is_none() {
                let error_message = format!(
                    "Firmware version `{}.{}.{}` not available.\n  Check {}\n  Available releases: {}\n  Latest release: {}",
                    version.major(),
                    version.minor(),
                    version.patch(),
                    Releases::manifest_url(),
                    releases.releases_str(),
                    releases.latest(),
                );
                return Err(Error::config(error_message));
            }
        } else {
            let latest = releases.latest();
            debug!("Firmware version not specified, using latest: {}", latest);
            self.fw = Some(FirmwareVersion::try_from_str(latest).map_err(Error::firmware_version)?);
        }

        // Generate a default output filename if not specified
        if self.out.is_none() {
            self.out = Some("onerom-fw.bin".to_string());
        }

        Ok(false)
    }
}

fn board_value_parser(s: &str) -> Result<Board, String> {
    Board::try_from_str(s).ok_or("Invalid board type".to_string())
}

fn mcu_value_parser(s: &str) -> Result<McuVariant, String> {
    McuVariant::try_from_str(s).ok_or("Invalid MCU variant".to_string())
}

fn firmware_value_parser(s: &str) -> Result<FirmwareVersion, String> {
    FirmwareVersion::try_from_str(s).map_err(|_| "Invalid firmware version".to_string())
}

fn board_values() -> String {
    onerom_config::hw::BOARDS
        .iter()
        .map(|b| b.name())
        .collect::<Vec<_>>()
        .join(", ")
        .into()
}

fn mcu_values() -> String {
    onerom_config::mcu::MCU_VARIANTS
        .iter()
        .map(|m| m.to_string().to_lowercase())
        .collect::<Vec<_>>()
        .join(", ")
        .into()
}
