// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

use std::collections::HashMap;
use std::fs;
use std::path::Path;

mod validation;

use validation::{HwConfigJson, McuFamily, Port};

pub const HW_CONFIG_DIRS: [&str; 1] = ["json"];
pub const HW_CONFIG_SUB_DIRS: [&str; 2] = ["user", "third-party"];
pub const HW_GENERATED_RS_FILENAME: &str = "hw/generated.rs";
pub const HW_MOD_RS_FILENAME: &str = "hw/mod.rs";

struct HwConfigData {
    name: String,
    alt: Vec<String>,
    variant_name: String,
    config: HwConfigJson,
    phys_pin_to_addr_map: [Option<usize>; 16],
    phys_pin_to_data_map: [usize; 8],
}

pub fn build(manifest_path: &Path) {
    // Find config directories
    let config_dirs = get_config_dirs(manifest_path);

    // Tell Cargo to rerun if any config changes
    for dir in &config_dirs {
        println!("cargo:rerun-if-changed={}", dir.display());
    }

    // Load and validate all configs
    let configs = load_all_configs(&config_dirs);

    // Generate Rust code
    let generated_code = generate_rust_code(&configs);
    let lib_code = generate_lib_rs(&configs);

    // Write generated files
    let generated_path = manifest_path.join("src").join(HW_GENERATED_RS_FILENAME);
    fs::write(&generated_path, &generated_code)
        .unwrap_or_else(|e| panic!("Failed to write {}: {}", generated_path.display(), e));

    let mod_path = manifest_path.join("src").join(HW_MOD_RS_FILENAME);
    fs::write(&mod_path, &lib_code)
        .unwrap_or_else(|e| panic!("Failed to write {}: {}", mod_path.display(), e));
}

fn get_config_dirs(repo_root: &Path) -> Vec<std::path::PathBuf> {
    let mut dirs = Vec::new();

    // Try to find root directory
    for dir in HW_CONFIG_DIRS.iter() {
        let path = repo_root.join(dir);
        if path.exists() {
            dirs.push(path.clone());

            // Add subdirectories
            for subdir in HW_CONFIG_SUB_DIRS.iter() {
                let subdir_path = path.join(subdir);
                if subdir_path.exists() {
                    dirs.push(subdir_path);
                }
            }
            break;
        }
    }

    if dirs.is_empty() {
        panic!("No hardware configuration directories found");
    }

    dirs
}

fn normalize_name(name: &str) -> String {
    name.to_lowercase().replace("_", "-")
}

fn name_to_variant(name: &str) -> String {
    let normalized = normalize_name(name);
    normalized
        .split('-')
        .map(|part| {
            let mut chars = part.chars();
            match chars.next() {
                None => String::new(),
                Some(first) => first.to_uppercase().collect::<String>() + chars.as_str(),
            }
        })
        .collect()
}

fn load_all_configs(config_dirs: &[std::path::PathBuf]) -> Vec<HwConfigData> {
    let mut configs = Vec::new();
    let mut seen_names: HashMap<String, std::path::PathBuf> = HashMap::new();

    for config_dir in config_dirs {
        for entry in fs::read_dir(config_dir)
            .unwrap_or_else(|e| panic!("Failed to read directory {}: {}", config_dir.display(), e))
        {
            let entry = entry.unwrap_or_else(|e| panic!("Failed to read directory entry: {}", e));
            let path = entry.path();

            if path.extension().and_then(|s| s.to_str()) == Some("json") {
                let filename = path
                    .file_stem()
                    .and_then(|s| s.to_str())
                    .unwrap_or_else(|| panic!("Invalid filename: {}", path.display()));

                // Skip rom-types.json - it's for ROM chip definitions, not hardware configs
                if filename == "rom-types" {
                    continue;
                }

                let normalized = normalize_name(filename);
                if normalized != filename {
                    panic!(
                        "Invalid hardware revision config filename '{}.json', must be lower-case with dashes",
                        filename
                    );
                }

                // Check starts with a letter
                if !normalized
                    .chars()
                    .next()
                    .map_or(false, |c| c.is_ascii_alphabetic())
                {
                    panic!(
                        "Invalid hardware revision config filename '{}.json', must start with a letter",
                        filename
                    );
                }

                // Check for duplicates
                if let Some(first_path) = seen_names.get(&normalized) {
                    panic!(
                        "Duplicate hardware revision '{}' found in {} and {}",
                        filename,
                        first_path.display(),
                        path.display()
                    );
                }
                seen_names.insert(normalized.clone(), path.clone());

                // Parse and validate
                let content = fs::read_to_string(&path)
                    .unwrap_or_else(|e| panic!("Failed to read {}: {}", path.display(), e));
                let config: HwConfigJson = serde_json::from_str(&content)
                    .unwrap_or_else(|e| panic!("Failed to parse {}: {}", path.display(), e));
                validation::validate_config(&normalized, &config);

                // Validate alt names
                for alt in &config.alt {
                    let normalized_alt = normalize_name(alt);
                    if normalized_alt != *alt {
                        panic!(
                            "Invalid alt name '{}' in config {}, must be lower-case with dashes",
                            alt, normalized
                        );
                    }
                    if seen_names.contains_key(&normalized_alt) {
                        panic!(
                            "Duplicate alt name '{}' in config {} conflicts with existing name",
                            alt, normalized
                        );
                    }
                    seen_names.insert(normalized_alt, path.clone());
                }

                // Figure out if the address pins will need to be shifted left by the MCU before using as an index
                let mut under_8 = false;
                let mut over_15 = false;
                for &phys_pin in &config.mcu.pins.addr {
                    if phys_pin < 8 {
                        under_8 = true;
                    }
                    if phys_pin > 15 {
                        over_15 = true;
                    }
                }
                if under_8 && over_15 {
                    panic!(
                        "Address pins in config {} mix low (<8) and high (>15) physical pins, which is not supported",
                        normalized
                    );
                }
                let shift_left_8 = if over_15 { true } else { false };

                // Compute pin maps
                let mut phys_pin_to_addr_map = [None; 16];
                for (addr_line, &phys_pin) in config.mcu.pins.addr.iter().enumerate() {
                    let mut phys_pin = phys_pin as usize;
                    if shift_left_8 {
                        assert!(phys_pin >= 8);
                        phys_pin -= 8;
                    }
                    assert!(phys_pin < 16);
                    phys_pin_to_addr_map[phys_pin] = Some(addr_line);
                }

                let mut phys_pin_to_data_map = [0; 8];
                for (data_line, &phys_pin) in config.mcu.pins.data.iter().enumerate() {
                    if phys_pin <= config.mcu.family.max_valid_data_pin() {
                        phys_pin_to_data_map[phys_pin as usize % 8] = data_line;
                    } else {
                        panic!("Invalid data pin {} in config {}", phys_pin, normalized);
                    }
                }

                configs.push(HwConfigData {
                    name: normalized.clone(),
                    alt: config.alt.clone(),
                    variant_name: name_to_variant(&normalized),
                    config,
                    phys_pin_to_addr_map,
                    phys_pin_to_data_map,
                });
            }
        }
    }

    if configs.is_empty() {
        panic!("No valid hardware configurations found");
    }

    // Sort by name for deterministic output
    configs.sort_by(|a, b| a.name.cmp(&b.name));

    configs
}

fn generate_lib_rs(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("// AUTO-GENERATED by build.rs - DO NOT EDIT MANUALLY\n");
    code.push_str("// Generated from hw-config/*.json\n");
    code.push_str("//\n");
    code.push_str("// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>\n");
    code.push_str("// MIT License\n\n");

    code.push_str("//! Hardware configuration for One ROM boards\n");
    code.push_str("//!\n");
    code.push_str(
        "//! This module provides compile-time hardware board specifications for One ROM.\n",
    );
    code.push_str(
        "//! All data is generated at build time from JSON configuration and embedded as\n",
    );
    code.push_str("//! const data - no runtime parsing or allocations needed.\n");
    code.push_str("//!\n");
    code.push_str("//! # Available Hardware Revisions\n");
    code.push_str("//!\n");

    for config in configs {
        code.push_str(&format!(
            "//! - **{}**: {}\n",
            config.name, config.config.description
        ));
    }

    code.push_str("//!\n");
    code.push_str("//! # Usage\n");
    code.push_str("//!\n");
    code.push_str("//! ```\n");
    code.push_str("//! use onerom_config::hw::Board;\n");
    code.push_str("//! use onerom_config::rom::RomType;\n");
    code.push_str("//!\n");
    code.push_str("//! // Parse from string\n");
    code.push_str("//! let hw = Board::try_from_str(\"24-d\").unwrap();\n");
    code.push_str("//! \n");
    code.push_str("//! // Get pin mappings\n");
    code.push_str("//! let data_pins = hw.data_pins();\n");
    code.push_str("//! let addr_pins = hw.addr_pins();\n");
    code.push_str("//! \n");
    code.push_str("//! // Check ROM-specific control pins\n");
    code.push_str("//! let cs1_pin = hw.pin_cs1(RomType::Rom2364);\n");
    code.push_str("//! \n");
    code.push_str("//! // Check capabilities\n");
    code.push_str("//! if hw.supports_banked_roms() {\n");
    code.push_str("//!     println!(\"Supports ROM banking\");\n");
    code.push_str("//! }\n");
    code.push_str("//! ```\n");

    code.push_str("\n#![deny(missing_docs)]\n");
    code.push_str("#![deny(unsafe_code)]\n\n");

    code.push_str("mod generated;\n\n");
    code.push_str("pub use generated::*;\n");

    code
}

fn generate_rust_code(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("// AUTO-GENERATED by build.rs - DO NOT EDIT MANUALLY\n");
    code.push_str("// Generated from hw-config/*.json\n");
    code.push_str("\n");
    code.push_str("// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>\n");
    code.push_str("//\n");
    code.push_str("// MIT License\n\n");
    code.push_str("#![allow(dead_code)]\n\n");

    code.push_str("use crate::rom::RomType;\n");
    code.push_str("use crate::mcu::{Port, Family};\n\n");

    // Generate models
    code.push_str(&generate_hw_models(configs));
    code.push_str("\n\n");

    // Generate HwConfig enum
    code.push_str(&generate_hw_config_enum(configs));
    code.push_str("\n\n");

    // Generate HwConfig implementation
    code.push_str(&generate_hw_config_impl(configs));

    code
}

fn generate_hw_config_enum(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("/// Hardware board configuration\n");
    code.push_str("///\n");
    code.push_str(
        "/// Defines pin mappings and capabilities for different One ROM board revisions.\n",
    );
    code.push_str("#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize)]\n");
    code.push_str("#[cfg_attr(feature = \"schemars\", derive(schemars::JsonSchema))]");
    code.push_str("pub enum Board {\n");

    for config in configs {
        code.push_str(&format!(
            "    /// {} - {}\n",
            config.name, config.config.description
        ));
        code.push_str(&format!("    #[serde(rename = \"{}\")]\n", config.name));
        code.push_str(&format!("    {},\n", config.variant_name));
    }

    code.push_str("}\n\n");

    // Define BOARDS array
    code.push_str("/// List of all supported hardware boards\n");
    code.push_str("pub const BOARDS: [Board; ");
    code.push_str(&configs.len().to_string());
    code.push_str("] = [\n");
    for config in configs {
        code.push_str(&format!("    Board::{},\n", config.variant_name));
    }
    code.push_str("];\n\n");

    // Implement Display for Board
    code.push_str("impl core::fmt::Display for Board {\n");
    code.push_str("    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {\n");
    code.push_str("        write!(f, \"{}\", self.name())\n");
    code.push_str("    }\n");
    code.push_str("}");

    code
}

fn generate_hw_config_impl(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("impl Board {\n");

    code.push_str(&generate_try_from_str(configs));
    code.push_str("\n\n");

    code.push_str(&generate_name_method(configs));
    code.push_str("\n\n");

    code.push_str(&generate_description_method(configs));
    code.push_str("\n\n");

    code.push_str(&generate_rom_pins_method(configs));
    code.push_str("\n\n");

    code.push_str(&generate_mcu_family_method(configs));
    code.push_str("\n\n");

    code.push_str(&generate_port_methods(configs));
    code.push_str("\n\n");

    code.push_str(&generate_data_pins_method(configs));
    code.push_str("\n\n");

    code.push_str(&generate_addr_pins_method(configs));
    code.push_str("\n\n");

    code.push_str(&generate_sel_pins_method(configs));
    code.push_str("\n\n");

    code.push_str(&generate_pin_status_method(configs));
    code.push_str("\n\n");

    code.push_str(&generate_rom_pin_methods(configs));
    code.push_str("\n\n");

    code.push_str(&generate_jumper_methods(configs));
    code.push_str("\n\n");

    code.push_str(&generate_pin_map_methods(configs));
    code.push_str("\n\n");

    code.push_str(&generate_capability_methods(configs));
    code.push_str("\n\n");

    code.push_str(&generate_model_method(configs));
    code.push_str("\n\n");

    code.push_str(&generate_supports_rom_type_method(configs));
    code.push_str("}\n");

    code
}

fn generate_try_from_str(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("    /// Parse hardware config from string identifier\n");
    code.push_str("    ///\n");
    code.push_str("    /// Supports both current naming (e.g., \"24-d\") and legacy names (\"d\" → \"24-d\").\n");
    code.push_str("    pub fn try_from_str(s: &str) -> Option<Self> {\n");
    code.push_str("        match s {\n");

    for config in configs {
        // Main name
        code.push_str(&format!(
            "            \"{}\" => Some(Board::{}),\n",
            config.name, config.variant_name
        ));

        // Alt names
        for alt in &config.alt {
            code.push_str(&format!(
                "            \"{}\" => Some(Board::{}),\n",
                alt, config.variant_name
            ));
        }
    }

    code.push_str("            _ => None,\n");
    code.push_str("        }\n");
    code.push_str("    }");
    code
}

fn generate_name_method(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("    /// Get the hardware revision name\n");
    code.push_str("    pub const fn name(&self) -> &'static str {\n");
    code.push_str("        match self {\n");

    for config in configs {
        code.push_str(&format!(
            "            Board::{} => \"{}\",\n",
            config.variant_name, config.name
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }");
    code
}

fn generate_description_method(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("    /// Get the hardware description\n");
    code.push_str("    pub const fn description(&self) -> &'static str {\n");
    code.push_str("        match self {\n");

    for config in configs {
        code.push_str(&format!(
            "            Board::{} => \"{}\",\n",
            config.variant_name, config.config.description
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }");
    code
}

fn generate_rom_pins_method(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("    /// Get the number of pins in supported ROM packages\n");
    code.push_str("    pub const fn rom_pins(&self) -> u8 {\n");
    code.push_str("        match self {\n");

    for config in configs {
        code.push_str(&format!(
            "            Board::{} => {},\n",
            config.variant_name, config.config.rom.pins.quantity
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }");
    code
}

fn generate_mcu_family_method(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("    /// Get the MCU family for this board\n");
    code.push_str("    pub const fn mcu_family(&self) -> Family {\n");
    code.push_str("        match self {\n");

    for config in configs {
        let family = match config.config.mcu.family {
            McuFamily::Stm32f4 => "Family::Stm32f4",
            McuFamily::Rp2350 => "Family::Rp2350",
        };
        code.push_str(&format!(
            "            Board::{} => {},\n",
            config.variant_name, family
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }");
    code
}

fn generate_port_methods(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    let port_methods = [
        ("port_data", "data_port", "Data port"),
        ("port_addr", "addr_port", "Address port"),
        ("port_cs", "cs_port", "Chip select port"),
        ("port_sel", "sel_port", "SEL port"),
        ("port_status", "status_port", "Status LED port"),
        ("port_usb", "usb_port", "USB pins port"),
    ];

    for (method_name, field_name, doc) in port_methods {
        code.push_str(&format!("    /// Get the {}\n", doc));
        code.push_str(&format!(
            "    pub const fn {}(&self) -> Port {{\n",
            method_name
        ));
        code.push_str("        match self {\n");

        for config in configs {
            let port = match field_name {
                "data_port" => &config.config.mcu.ports.data_port,
                "addr_port" => &config.config.mcu.ports.addr_port,
                "cs_port" => &config.config.mcu.ports.cs_port,
                "sel_port" => &config.config.mcu.ports.sel_port,
                "status_port" => &config.config.mcu.ports.status_port,
                "usb_port" => &config.config.mcu.usb.as_ref().and_then(|usb| usb.pins.as_ref().map(|pins| pins.port)).unwrap_or(Port::None),
                _ => unreachable!(),
            };
            let port_str = format_port(port);
            code.push_str(&format!(
                "            Board::{} => {},\n",
                config.variant_name, port_str
            ));
        }

        code.push_str("        }\n");
        code.push_str("    }");
        if method_name != "usb_port" {
            code.push_str("\n\n");
        }
    }

    code
}

fn format_port(port: &Port) -> String {
    match port {
        Port::None => "Port::None".to_string(),
        Port::Zero => "Port::Zero".to_string(),
        Port::A => "Port::A".to_string(),
        Port::B => "Port::B".to_string(),
        Port::C => "Port::C".to_string(),
        Port::D => "Port::D".to_string(),
    }
}

fn generate_data_pins_method(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("    /// Get data line pin assignments (D0-D7)\n");
    code.push_str("    pub const fn data_pins(&self) -> &'static [u8] {\n");
    code.push_str("        match self {\n");

    for config in configs {
        let pins_str = config
            .config
            .mcu
            .pins
            .data
            .iter()
            .map(|p| p.to_string())
            .collect::<Vec<_>>()
            .join(", ");
        code.push_str(&format!(
            "            Board::{} => &[{}],\n",
            config.variant_name, pins_str
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }");
    code
}

fn generate_addr_pins_method(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("    /// Get address line pin assignments\n");
    code.push_str("    pub const fn addr_pins(&self) -> &'static [u8] {\n");
    code.push_str("        match self {\n");

    for config in configs {
        let pins_str = config
            .config
            .mcu
            .pins
            .addr
            .iter()
            .map(|p| p.to_string())
            .collect::<Vec<_>>()
            .join(", ");
        code.push_str(&format!(
            "            Board::{} => &[{}],\n",
            config.variant_name, pins_str
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }");
    code
}

fn generate_sel_pins_method(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("    /// Get SEL pin assignments\n");
    code.push_str("    pub const fn sel_pins(&self) -> &'static [u8] {\n");
    code.push_str("        match self {\n");

    for config in configs {
        let pins_str = config
            .config
            .mcu
            .pins
            .sel
            .iter()
            .map(|p| p.to_string())
            .collect::<Vec<_>>()
            .join(", ");
        code.push_str(&format!(
            "            Board::{} => &[{}],\n",
            config.variant_name, pins_str
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }");
    code
}

fn generate_pin_status_method(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("    /// Get status LED pin\n");
    code.push_str("    pub const fn pin_status(&self) -> u8 {\n");
    code.push_str("        match self {\n");

    for config in configs {
        code.push_str(&format!(
            "            Board::{} => {},\n",
            config.variant_name, config.config.mcu.pins.status
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }");
    code
}

fn generate_rom_pin_methods(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    let pin_methods = [
        ("pin_cs1", "bit_cs1", "cs1", "CS1"),
        ("pin_cs2", "bit_cs2", "cs2", "CS2"),
        ("pin_cs3", "bit_cs3", "cs3", "CS3"),
        ("pin_ce", "bit_ce", "ce", "CE"),
        ("pin_oe", "bit_oe", "oe", "OE"),
    ];

    for (pin_method_name, bit_method_name, field_name, doc) in pin_methods {
        // Generate pin_XXX method (GPIO number)
        code.push_str(&format!(
            "    /// Get MCU pin for {} signal for a given ROM type (returns 255 if not defined)\n",
            doc
        ));
        code.push_str(&format!(
            "    pub const fn {}(&self, rom_type: RomType) -> u8 {{\n",
            pin_method_name
        ));
        code.push_str("        match self {\n");

        for config in configs {
            code.push_str(&format!(
                "            Board::{} => match rom_type {{\n",
                config.variant_name
            ));

            let pin_map = match field_name {
                "cs1" => &config.config.mcu.pins.cs1,
                "cs2" => &config.config.mcu.pins.cs2,
                "cs3" => &config.config.mcu.pins.cs3,
                "ce" => &config.config.mcu.pins.ce,
                "oe" => &config.config.mcu.pins.oe,
                _ => unreachable!(),
            };

            // Generate matches for each ROM type
            for (rom_name, pin) in pin_map {
                code.push_str(&format!(
                    "                RomType::Rom{} => {},\n",
                    rom_name, pin
                ));
            }

            code.push_str("                _ => 255,\n");
            code.push_str("            },\n");
        }

        code.push_str("        }\n");
        code.push_str("    }\n\n");

        // Generate bit_XXX method (bit position after shift)
        code.push_str(&format!(
            "    /// Get bit position for {} signal for a given ROM type (returns 255 if not defined)\n",
            doc
        ));
        code.push_str(&format!(
            "    pub const fn {}(&self, rom_type: RomType) -> u8 {{\n",
            bit_method_name
        ));
        code.push_str("        match self {\n");

        for config in configs {
            // On the RP2350 we have a single GPIO port, and if data lines are
            // 0-7, then address lines need to be left shifted 8 bits as
            // they'll be 8-23.
            let shift_left_8 = config.config.mcu.family == McuFamily::Rp2350 
                && config.config.mcu.pins.data[0] < 8;
            
            code.push_str(&format!(
                "            Board::{} => match rom_type {{\n",
                config.variant_name
            ));

            let pin_map = match field_name {
                "cs1" => &config.config.mcu.pins.cs1,
                "cs2" => &config.config.mcu.pins.cs2,
                "cs3" => &config.config.mcu.pins.cs3,
                "ce" => &config.config.mcu.pins.ce,
                "oe" => &config.config.mcu.pins.oe,
                _ => unreachable!(),
            };

            // Generate matches for each ROM type with shift applied
            for (rom_name, pin) in pin_map {
                let bit_pos = if shift_left_8 && *pin >= 8 {
                    pin - 8
                } else {
                    *pin
                };
                code.push_str(&format!(
                    "                RomType::Rom{} => {},\n",
                    rom_name, bit_pos
                ));
            }

            code.push_str("                _ => 255,\n");
            code.push_str("            },\n");
        }

        code.push_str("        }\n");
        code.push_str("    }\n");
        if field_name != "oe" {
            code.push_str("\n");
        }
    }
    // Add X1 and X2 pin methods
    code.push_str("\n");
    code.push_str("    /// Get X1 pin (returns 255 if not available)\n");
    code.push_str("    pub const fn pin_x1(&self) -> u8 {\n");
    code.push_str("        match self {\n");
    for config in configs {
        let pin = config.config.mcu.pins.x1.unwrap_or(255);
        code.push_str(&format!(
            "            Board::{} => {},\n",
            config.variant_name, pin
        ));
    }
    code.push_str("        }\n");
    code.push_str("    }\n\n");

    code.push_str("    /// Get X1 bit position (returns 255 if not available)\n");
    code.push_str("    pub const fn bit_x1(&self) -> u8 {\n");
    code.push_str("        match self {\n");
    for config in configs {
        let pin = config.config.mcu.pins.x1.unwrap_or(255);
        let shift_left_8 = config.config.mcu.family == McuFamily::Rp2350 
            && config.config.mcu.pins.data[0] < 8;
        let bit_pos = if pin != 255 && shift_left_8 && pin >= 8 {
            pin - 8
        } else {
            pin
        };
        code.push_str(&format!(
            "            Board::{} => {},\n",
            config.variant_name, bit_pos
        ));
    }
    code.push_str("        }\n");
    code.push_str("    }\n\n");

    code.push_str("    /// Get X2 pin (returns 255 if not available)\n");
    code.push_str("    pub const fn pin_x2(&self) -> u8 {\n");
    code.push_str("        match self {\n");
    for config in configs {
        let pin = config.config.mcu.pins.x2.unwrap_or(255);
        code.push_str(&format!(
            "            Board::{} => {},\n",
            config.variant_name, pin
        ));
    }
    code.push_str("        }\n");
    code.push_str("    }\n\n");

    code.push_str("    /// Get X2 bit position (returns 255 if not available)\n");
    code.push_str("    pub const fn bit_x2(&self) -> u8 {\n");
    code.push_str("        match self {\n");
    for config in configs {
        let pin = config.config.mcu.pins.x2.unwrap_or(255);
        let shift_left_8 = config.config.mcu.family == McuFamily::Rp2350 
            && config.config.mcu.pins.data[0] < 8;
        let bit_pos = if pin != 255 && shift_left_8 && pin >= 8 {
            pin - 8
        } else {
            pin
        };
        code.push_str(&format!(
            "            Board::{} => {},\n",
            config.variant_name, bit_pos
        ));
    }
    code.push_str("        }\n");
    code.push_str("    }\n\n");

    // Add pin_sel method
    code.push_str("    /// Get SEL pin by index (returns 255 if not available)\n");
    code.push_str("    pub const fn pin_sel(&self, sel: usize) -> u8 {\n");
    code.push_str("        let pins = self.sel_pins();\n");
    code.push_str("        if sel < pins.len() {\n");
    code.push_str("            pins[sel]\n");
    code.push_str("        } else {\n");
    code.push_str("            255\n");
    code.push_str("        }\n");
    code.push_str("    }\n\n");

    // Add cs_pin_for_rom_in_set method
    code.push_str("    /// Get chip select pin for ROM in set (0=CS1, 1=X1, 2=X2)\n");
    code.push_str("    pub const fn cs_pin_for_rom_in_set(&self, rom_type: RomType, set_index: usize) -> u8 {\n");
    code.push_str("        match set_index {\n");
    code.push_str("            0 => self.pin_cs1(rom_type),\n");
    code.push_str("            1 => self.pin_x1(),\n");
    code.push_str("            2 => self.pin_x2(),\n");
    code.push_str("            _ => 255,\n");
    code.push_str("        }\n");
    code.push_str("    }\n\n");

    code.push_str("    /// Get chip select bit position for ROM in set (0=CS1, 1=X1, 2=X2)\n");
    code.push_str("    pub const fn cs_bit_for_rom_in_set(&self, rom_type: RomType, set_index: usize) -> u8 {\n");
    code.push_str("        match set_index {\n");
    code.push_str("            0 => self.bit_cs1(rom_type),\n");
    code.push_str("            1 => self.bit_x1(),\n");
    code.push_str("            2 => self.bit_x2(),\n");
    code.push_str("            _ => 255,\n");
    code.push_str("        }\n");
    code.push_str("    }");

    code
}

fn generate_jumper_methods(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("    /// Get SEL jumper pull direction (0=down, 1=up)\n");
    code.push_str("    pub const fn sel_jumper_pull(&self) -> u8 {\n");
    code.push_str("        match self {\n");

    for config in configs {
        code.push_str(&format!(
            "            Board::{} => {},\n",
            config.variant_name, config.config.mcu.pins.sel_jumper_pull
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }\n\n");

    code.push_str("    /// Get X jumper pull direction (0=down, 1=up)\n");
    code.push_str("    pub const fn x_jumper_pull(&self) -> u8 {\n");
    code.push_str("        match self {\n");

    for config in configs {
        code.push_str(&format!(
            "            Board::{} => {},\n",
            config.variant_name, config.config.mcu.pins.x_jumper_pull
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }");

    code
}

fn generate_pin_map_methods(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("    /// Get physical pin to address line mapping\n");
    code.push_str("    ///\n");
    code.push_str("    /// Returns array indexed by physical pin number, with value being the\n");
    code.push_str("    /// address line number (Some) or None if pin is not an address line.\n");
    code.push_str(
        "    pub const fn phys_pin_to_addr_map(&self) -> &'static [Option<usize>; 16] {\n",
    );
    code.push_str("        match self {\n");

    for config in configs {
        code.push_str(&format!(
            "            Board::{} => &[{}],\n",
            config.variant_name,
            format_option_array(&config.phys_pin_to_addr_map)
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }\n\n");

    code.push_str("    /// Get physical pin to data line mapping\n");
    code.push_str("    ///\n");
    code.push_str("    /// Returns array indexed by physical pin number (modulo 8), with value\n");
    code.push_str("    /// being the data line number.\n");
    code.push_str("    pub const fn phys_pin_to_data_map(&self) -> &'static [usize; 8] {\n");
    code.push_str("        match self {\n");

    for config in configs {
        code.push_str(&format!(
            "            Board::{} => &[{}],\n",
            config.variant_name,
            config
                .phys_pin_to_data_map
                .iter()
                .map(|v| v.to_string())
                .collect::<Vec<_>>()
                .join(", ")
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }");

    code
}

fn format_option_array(arr: &[Option<usize>; 16]) -> String {
    arr.iter()
        .map(|opt| match opt {
            Some(v) => format!("Some({})", v),
            None => "None".to_string(),
        })
        .collect::<Vec<_>>()
        .join(", ")
}

fn generate_capability_methods(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("    /// Check if this board supports banked ROMs\n");
    code.push_str("    pub const fn supports_banked_roms(&self) -> bool {\n");
    code.push_str("        self.supports_multi_rom_sets()\n");
    code.push_str("    }\n\n");

    code.push_str(
        "    /// Check if this board supports multiple ROM sets (requires X1 and X2 pins)\n",
    );
    code.push_str("    pub const fn supports_multi_rom_sets(&self) -> bool {\n");
    code.push_str("        match self {\n");

    for config in configs {
        let supports = config.config.mcu.pins.x1.is_some() && config.config.mcu.pins.x2.is_some();
        code.push_str(&format!(
            "            Board::{} => {},\n",
            config.variant_name, supports
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }\n\n");

    code.push_str("    /// Check if this board has USB support\n");
    code.push_str("    pub const fn has_usb(&self) -> bool {\n");
    code.push_str("        match self {\n");

    for config in configs {
        let has_usb = config
            .config
            .mcu
            .usb
            .as_ref()
            .map_or(false, |usb| usb.present);
        code.push_str(&format!(
            "            Board::{} => {},\n",
            config.variant_name, has_usb
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }\n\n");

    // Get USB VBUS pin
    code.push_str("    /// Get the USB VBUS pin\n");
    code.push_str("    pub const fn usb_vbus_pin(&self) -> Option<u8> {\n");
    code.push_str("        match self {\n");

    for config in configs {
        let vbus_pin = config.config.mcu.usb.as_ref().and_then(|usb| usb.pins.as_ref().map(|pins| pins.vbus));
        code.push_str(&format!(
            "            Board::{} => {:?},\n",
            config.variant_name, vbus_pin
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }\n");

    code
}

fn generate_model_method(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("    /// Get the hardware model (Fire or Ice)\n");
    code.push_str("    pub const fn model(&self) -> Model {\n");
    code.push_str("        match self {\n");

    for config in configs {
        let model = if config.variant_name.starts_with("Fire") {
            "Model::Fire"
        } else if config.variant_name.starts_with("Ice") {
            "Model::Ice"
        } else {
            panic!("Unknown model for board: {}", config.variant_name);
        };
        code.push_str(&format!(
            "            Board::{} => {},\n",
            config.variant_name, model
        ));
    }

    code.push_str("        }\n");
    code.push_str("    }");

    code
}

fn generate_supports_rom_type_method(_configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("    /// Check if this board supports a given ROM type\n");
    code.push_str("    pub const fn supports_rom_type(&self, rom_type: RomType) -> bool {\n");
    code.push_str("        let board_pins = self.rom_pins();\n");
    code.push_str("        let rom_pins = rom_type.rom_pins();\n");
    code.push_str("        rom_pins == board_pins\n");
    code.push_str("    }");

    code
}

fn generate_hw_models(configs: &[HwConfigData]) -> String {
    let mut code = String::new();

    code.push_str("/// Hardware models\n");
    code.push_str("#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize)]\n");
    code.push_str("#[cfg_attr(feature = \"schemars\", derive(schemars::JsonSchema))]");
    code.push_str("pub enum Model {\n");
    code.push_str("    /// Fire (RP2350) Model\n");
    code.push_str("    Fire,\n");
    code.push_str("    /// Ice (STM32F4) Model\n");
    code.push_str("    Ice,\n");
    code.push_str("}\n\n");

    code.push_str("/// All hardware models\n");
    code.push_str("pub const MODELS: [Model; 2] = [Model::Fire, Model::Ice];\n\n");

    code.push_str("impl core::fmt::Display for Model {\n");
    code.push_str("    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {\n");
    code.push_str("        write!(f, \"{}\", self.name())\n");
    code.push_str("    }\n");
    code.push_str("}\n\n");

    code.push_str("impl Model {\n");
    code.push_str("    /// Get the model name\n");
    code.push_str("    pub fn name(&self) -> &'static str {\n");
    code.push_str("        match self {\n");
    code.push_str("            Model::Fire => \"Fire\",\n");
    code.push_str("            Model::Ice => \"Ice\",\n");
    code.push_str("        }\n");
    code.push_str("    }\n\n");

    code.push_str("    /// Try to create a model from a string\n");
    code.push_str("    pub fn try_from_str(s: &str) -> Option<Self> {\n");
    code.push_str("        if s.eq_ignore_ascii_case(\"fire\") {\n");
    code.push_str("            Some(Self::Fire)\n");
    code.push_str("        } else if s.eq_ignore_ascii_case(\"ice\") {\n");
    code.push_str("            Some(Self::Ice)\n");
    code.push_str("        } else {\n");
    code.push_str("            None\n");
    code.push_str("        }\n");
    code.push_str("    }\n\n");

    // Separate configs by model
    let mut fire_boards = Vec::new();
    let mut ice_boards = Vec::new();

    for config in configs {
        if config.variant_name.starts_with("Fire") {
            fire_boards.push(&config.variant_name);
        } else if config.variant_name.starts_with("Ice") {
            ice_boards.push(&config.variant_name);
        }
    }

    code.push_str("    /// Get the boards for this model\n");
    code.push_str("    pub fn boards(self) -> &'static [Board] {\n");
    code.push_str("        match self {\n");

    // Generate Fire boards
    code.push_str("            Model::Fire => &[\n");
    for board in &fire_boards {
        code.push_str(&format!("                Board::{},\n", board));
    }
    code.push_str("            ],\n");

    // Generate Ice boards
    code.push_str("            Model::Ice => &[\n");
    for board in &ice_boards {
        code.push_str(&format!("                Board::{},\n", board));
    }
    code.push_str("            ],\n");

    code.push_str("        }\n");
    code.push_str("    }\n\n");

    // Get the mcu family for this model
    code.push_str("    /// Get the MCU family for this model\n");
    code.push_str("    pub fn mcu_family(&self) -> Family {\n");
    code.push_str("        match self {\n");
    code.push_str("            Model::Fire => Family::Rp2350,\n");
    code.push_str("            Model::Ice => Family::Stm32f4,\n");
    code.push_str("        }\n");
    code.push_str("    }\n");


    code.push_str("}");
    code
}
