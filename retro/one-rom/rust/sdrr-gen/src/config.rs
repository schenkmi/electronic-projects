// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

use std::collections::BTreeMap;
use std::path::PathBuf;

use onerom_config::fw::ServeAlg;
use onerom_config::hw::Board;
use onerom_config::mcu::{Port, Variant as McuVariant};
use onerom_config::rom::RomType;

use onerom_gen::image::{CsConfig, Rom, RomSet, RomSetType, SizeHandling};

use crate::fw::PllConfig;

#[derive(Debug, Clone)]
pub struct Config {
    pub roms: Vec<RomConfig>,
    pub mcu_variant: McuVariant,
    pub output_dir: PathBuf,
    pub swd: bool,
    pub count_rom_access: bool,
    pub mco: bool,
    pub mco2: bool,
    pub boot_logging: bool,
    pub main_loop_logging: bool,
    pub main_loop_one_shot: bool,
    pub debug_logging: bool,
    pub overwrite: bool,
    pub hse: bool,
    pub board: Board,
    pub freq: u32,
    pub status_led: bool,
    pub overclock: bool,
    pub bootloader: bool,
    pub preload_to_ram: bool,
    pub auto_yes: bool,
    pub serve_alg: ServeAlg,
}

#[derive(Debug, Clone)]
pub struct RomConfig {
    pub file: PathBuf,
    pub original_source: String,
    pub extract: Option<String>,
    pub licence: Option<String>,
    pub rom_type: RomType,
    pub cs_config: CsConfig,
    pub size_handling: SizeHandling,
    pub set: Option<usize>,
    pub bank: Option<usize>,
}

impl Config {
    pub fn validate(&mut self) -> Result<(), String> {
        // Validate output directory
        if !self.overwrite && self.output_dir.exists() {
            for file_name in &["roms.h", "roms.c", "config.h", "sdrr_config.h"] {
                let file_path = self.output_dir.join(file_name);
                if file_path.exists() {
                    return Err(format!(
                        "Output file '{}' already exists. Use --overwrite to overwrite.",
                        file_path.display()
                    ));
                }
            }
        }

        // Validate status LED settings
        if self.status_led
            && ((self.board.port_status() == Port::None) || (self.board.pin_status() == 255))
        {
            return Err(
                "Status LED enabled but no status LED pin configured for selected hardware revision."
                    .to_string(),
            );
        }

        // Validate processor against family
        if self.mcu_variant.family() != self.board.mcu_family() {
            return Err(format!(
                "MCU variant {} does not match hardware revision MCU family {}.\nSpecify a different hardware revision or MCU variant.",
                self.mcu_variant.makefile_var(),
                self.board.mcu_family()
            ));
        }

        // Validate and set frequency
        #[allow(clippy::match_single_binding)]
        let pll = PllConfig::new(self.mcu_variant.processor());
        if !pll.is_frequency_valid(self.freq, self.overclock) {
            return Err(format!(
                "Frequency {}MHz is not valid for variant {}. Valid range: 16-{}MHz.",
                self.freq,
                self.mcu_variant.makefile_var(),
                self.mcu_variant.processor().max_sysclk_mhz()
            ));
        }

        // Check USB DFU support
        if self.board.has_usb() && !self.mcu_variant.supports_usb_dfu() {
            return Err(format!(
                "Selected hardware {} has USB, but chosen MCU variant {:?} does not support USB.",
                self.board.name(),
                self.mcu_variant,
            ));
        }

        // Check all ROMs are compatible with the selected board
        for rom in &self.roms {
            if self.board.rom_pins() != rom.rom_type.rom_pins() {
                return Err(format!(
                    "ROM type {} is not supported on selected hardware revision {}",
                    rom.rom_type.name(),
                    self.board.name()
                ));
            }
        }

        // Validate ROM sets (basic validation that doesn't need ROM images)
        let mut sets: Vec<usize> = self.roms.iter().filter_map(|rom| rom.set).collect();

        if !sets.is_empty() {
            // Check if all ROMs have sets specified
            let roms_with_sets = self.roms.iter().filter(|rom| rom.set.is_some()).count();
            if roms_with_sets != self.roms.len() {
                return Err("When using sets, all ROMs must specify a set number".to_string());
            }

            // Sort and check sequential from 0
            sets.sort();
            sets.dedup();

            for (i, &set_num) in sets.iter().enumerate() {
                if set_num != i {
                    return Err(format!(
                        "ROM sets must be numbered sequentially starting from 0. Missing set {}",
                        i
                    ));
                }
            }

            // Enhanced set validation for banking and multi-ROM modes
            for &set_id in &sets {
                let roms_in_set: Vec<_> = self
                    .roms
                    .iter()
                    .filter(|rom| rom.set == Some(set_id))
                    .collect();

                // Check if this set uses banking
                let banked_roms: Vec<_> = roms_in_set
                    .iter()
                    .filter(|rom| rom.bank.is_some())
                    .collect();

                let is_banked_set = !banked_roms.is_empty();

                if is_banked_set {
                    // Banking mode validation

                    // Check hardware variant supports banked sets
                    if !self.board.supports_banked_roms() {
                        return Err(
                            "Bank switched sets of ROMs are only supported on hardware revision F onwards".to_string(),
                        );
                    }

                    // Check STM variant supports banked sets
                    if !self.mcu_variant.supports_banked_roms() {
                        return Err(format!(
                            "Set {}: banked ROMs are not supported on STM32 variant {} due to lack of RAM and/or flash",
                            set_id,
                            self.mcu_variant.makefile_var()
                        ));
                    }

                    // All ROMs in set must have bank specified
                    if banked_roms.len() != roms_in_set.len() {
                        return Err(format!(
                            "Set {}: when using banks, all ROMs in the set must specify a bank number",
                            set_id
                        ));
                    }

                    // Max 4 ROMs for banked sets
                    if roms_in_set.len() > 4 {
                        return Err(format!(
                            "Set {}: banked sets can contain maximum 4 ROMs, found {}",
                            set_id,
                            roms_in_set.len()
                        ));
                    }

                    // Banks must be sequential from 0
                    let mut banks: Vec<usize> =
                        roms_in_set.iter().map(|rom| rom.bank.unwrap()).collect();
                    banks.sort();
                    banks.dedup();

                    for (i, &bank_num) in banks.iter().enumerate() {
                        if bank_num != i {
                            return Err(format!(
                                "Set {}: bank numbers must be sequential starting from 0. Missing bank {}",
                                set_id, i
                            ));
                        }
                    }

                    // All ROMs must have same type
                    let first_rom_type = &roms_in_set[0].rom_type;
                    for rom in &roms_in_set[1..] {
                        if rom.rom_type != *first_rom_type {
                            return Err(format!(
                                "Set {}: all ROMs in a banked set must have the same type. Found {} and {}",
                                set_id,
                                first_rom_type.name(),
                                rom.rom_type.name()
                            ));
                        }
                    }

                    // All ROMs must have same CS configuration
                    let first_cs_config = &roms_in_set[0].cs_config;
                    for rom in &roms_in_set[1..] {
                        if rom.cs_config != *first_cs_config {
                            return Err(format!(
                                "Set {}: all ROMs in a banked set must have the same CS configuration",
                                set_id
                            ));
                        }
                    }
                } else {
                    // Multi-ROM mode validation

                    // Check hardware variant supports multi-rom sets
                    if !self.board.supports_multi_rom_sets() {
                        return Err(
                            "Multi-ROM sets of ROMs are only supported on hardware revision F onwards".to_string(),
                        );
                    }

                    // Check this STM variant supports multi-ROM sets
                    if roms_in_set.len() > 1 {
                        #[allow(clippy::collapsible_if)]
                        if !self.mcu_variant.supports_multi_rom_sets() {
                            return Err(format!(
                                "Set {}: multi-set ROMs are not supported on STM32 variant {} due to lack of RAM and/or flash",
                                set_id,
                                self.mcu_variant.makefile_var()
                            ));
                        }
                    }

                    // Ensure no ROMs have bank specified
                    for rom in &roms_in_set {
                        if rom.bank.is_some() {
                            return Err(format!(
                                "Set {}: mixed banking modes not allowed - either all or no ROMs in set must specify bank",
                                set_id
                            ));
                        }
                    }

                    // Max 3 ROMs for multi-ROM sets
                    if roms_in_set.len() > 3 {
                        return Err(format!(
                            "Set {}: multi-ROM sets can contain maximum 3 ROMs, found {}",
                            set_id,
                            roms_in_set.len()
                        ));
                    }
                }
            }
        }

        Ok(())
    }

    pub fn create_rom_sets(
        &self,
        roms: Vec<Rom>,
        serve_alg: ServeAlg,
    ) -> Result<Vec<RomSet>, String> {
        let sets: Vec<usize> = self.roms.iter().filter_map(|rom| rom.set).collect();

        if sets.is_empty() {
            let rom_sets: Vec<RomSet> = roms
                .into_iter()
                .enumerate()
                .map(|(ii, rom)| RomSet::new(ii, RomSetType::Single, serve_alg, vec![rom]))
                .collect::<Result<Vec<_>, _>>()
                .map_err(|e| format!("Error creating ROM sets: {:?}", e))?;
            return Ok(rom_sets);
        }

        let mut sets_map: BTreeMap<usize, Vec<(usize, &RomConfig, Rom)>> = BTreeMap::new();

        for (ii, (rom_config, rom)) in self.roms.iter().zip(roms.into_iter()).enumerate() {
            if let Some(set_id) = rom_config.set {
                sets_map
                    .entry(set_id)
                    .or_default()
                    .push((ii, rom_config, rom));
            }
        }

        let mut rom_sets: Vec<RomSet> = Vec::new();

        for (set_id, mut roms_in_set) in sets_map {
            let num_roms = roms_in_set.len();

            let is_banked = roms_in_set
                .iter()
                .any(|(_, config, _)| config.bank.is_some());

            if is_banked {
                roms_in_set.sort_by_key(|(_, config, _)| config.bank.unwrap());
            }

            let rom_vec: Vec<Rom> = roms_in_set.into_iter().map(|(_, _, rom)| rom).collect();

            let rom_set = RomSet::new(
                set_id,
                if is_banked {
                    RomSetType::Banked
                } else if num_roms > 1 {
                    RomSetType::Multi
                } else {
                    // Single ROM sets are dealt with here if there are also
                    // multi-ROM or banked sets in the config
                    RomSetType::Single
                },
                serve_alg,
                rom_vec,
            )
            .map_err(|e| format!("Error creating ROM sets: {:?}", e))?;

            rom_sets.push(rom_set);
        }

        Ok(rom_sets)
    }
}
