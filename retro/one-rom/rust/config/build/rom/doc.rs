// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

use super::validation::{ControlLineType, RomType, RomTypesConfig};
use std::collections::BTreeMap;

/// Generate complete ROM types markdown documentation
pub fn generate_rom_types_markdown(config: &RomTypesConfig) -> String {
    let mut doc = String::new();

    // Header
    doc.push_str(r#"# ROM Type Specifications

This document provides detailed specifications for the different ROM types One ROM supports, and aims to support in future, including pinouts, control lines, and programming requirements.

The document is auto-generated from the [json/rom-types.json](/rust/config/json/rom-types.json) configuration file.  That file was created by researching datasheets for the various ROM types.

Some of the pin names have been modified from the datasheet values for consistency beween ROM types:

- /OE on 2704/2408 is called Program, but serves as /OE when in read mode.  Other 27xx ROMs use /OE for that pin, hence the /OE name is used here. 
- Similarly /CE on 2704/2708 ROMs is called /CS, but is called /CE for consistency with other ROM types.
- 23256/23512 chip select lines are often called CE/OE on datasheets, but are mask programmable to be active high or low, hence these are referred to within this doc as CS lines, like the other 23xx ROMs.

There are also some other inconsistencies between types:

- 2332's CS2 is pin 21 and pin 18 is A11.  On the 2316, CS2 is pin 18, and CS3 pin 21.
- The 2332's A11 is pin18, but the 2732's A11 is pin 21.

## Contents

- [24-pin Mask ROM Family (23xx)](#24-pin-mask-rom-family-23xx)
- [28-pin Mask ROM Family (23xxx)](#28-pin-mask-rom-family-23xx)
- [24-pin EPROM Family (27xx)](#24-pin-eprom-family-27xx)
- [28-pin EPROM Family (2764 and 27xxx)](#28-pin-eprom-family-27xx)
- [Pin Function Comparison](#pin-function-comparison)
- [Detailed Pinouts](#detailed-pinouts)

"#);

    // Group ROMs by family
    let families = group_by_family(config);

    // Family comparison tables
    if let Some(roms) = families.get("mask_24pin") {
        doc.push_str(&generate_family_comparison_table(
            "24-pin Mask ROM Family (23xx)",
            roms,
            config,
        ));
        doc.push_str("\n");
    }

    if let Some(roms) = families.get("mask_28pin") {
        doc.push_str(&generate_family_comparison_table(
            "28-pin Mask ROM Family (23xx)",
            roms,
            config,
        ));
        doc.push_str("\n");
    }

    if let Some(roms) = families.get("eprom_24pin") {
        doc.push_str(&generate_family_comparison_table(
            "24-pin EPROM Family (27xx)",
            roms,
            config,
        ));
        doc.push_str("\n");
    }

    if let Some(roms) = families.get("eprom_28pin") {
        doc.push_str(&generate_family_comparison_table(
            "28-pin EPROM Family (27xx)",
            roms,
            config,
        ));
        doc.push_str("\n");
    }

    // Pin comparison tables
    doc.push_str("## Pin Function Comparison\n\n");
    doc.push_str(&generate_pin_comparison_table_24pin(config));
    doc.push_str("\n");
    doc.push_str(&generate_pin_comparison_table_28pin(config));
    doc.push_str("\n");

    // Detailed pinout tables
    doc.push_str("## Detailed Pinouts\n\n");
    let sorted_roms = get_sorted_rom_types(config);
    for (type_name, rom_type) in sorted_roms {
        doc.push_str(&generate_detailed_pinout(type_name, rom_type));
        doc.push_str("\n");
    }

    doc
}

/// Group ROM types by family (mask/eprom and pin count)
fn group_by_family(config: &RomTypesConfig) -> BTreeMap<&'static str, Vec<(&String, &RomType)>> {
    let mut families: BTreeMap<&'static str, Vec<(&String, &RomType)>> = BTreeMap::new();

    for (type_name, rom_type) in &config.rom_types {
        let key = if type_name.starts_with("23") {
            if rom_type.pins == 24 {
                "mask_24pin"
            } else {
                "mask_28pin"
            }
        } else if type_name.starts_with("27") {
            if rom_type.pins == 24 {
                "eprom_24pin"
            } else {
                "eprom_28pin"
            }
        } else {
            continue;
        };

        families
            .entry(key)
            .or_insert_with(Vec::new)
            .push((type_name, rom_type));
    }

    // Sort each family by size
    for roms in families.values_mut() {
        roms.sort_by_key(|(_, rom)| rom.size);
    }

    families
}

/// Generate comparison table for a ROM family
fn generate_family_comparison_table(
    title: &str,
    roms: &[(&String, &RomType)],
    _config: &RomTypesConfig,
) -> String {
    let mut table = String::new();

    table.push_str(&format!("## {}\n\n", title));
    table.push_str("| ROM Type | Size | Address Lines | Control Lines | Programming |\n");
    table.push_str("|----------|------|---------------|---------------|-------------|\n");

    for (type_name, rom_type) in roms {
        let size_str = format_size(rom_type.size);
        let addr_lines = format!(
            "{} (A0-A{})",
            rom_type.address.len(),
            rom_type.address.len() - 1
        );

        let control_str = format_control_lines(rom_type);
        let prog_str = format_programming_pins(rom_type);

        table.push_str(&format!(
            "| {} | {} | {} | {} | {} |\n",
            type_name, size_str, addr_lines, control_str, prog_str
        ));
    }

    table
}

/// Generate 24-pin package pin comparison table
fn generate_pin_comparison_table_24pin(config: &RomTypesConfig) -> String {
    let mut table = String::new();

    // Get all 24-pin ROMs sorted by size
    let mut roms_24pin: Vec<_> = config
        .rom_types
        .iter()
        .filter(|(_, rom)| rom.pins == 24)
        .collect();
    roms_24pin.sort_by_key(|(name, rom)| {
        let family = if name.starts_with("23") { 0 } else { 1 };
        (family, rom.size, *name)
    });

    if roms_24pin.is_empty() {
        return table;
    }

    table.push_str("### 24-pin Package\n\n");
    table.push_str("| Pin |");
    for (type_name, _) in &roms_24pin {
        table.push_str(&format!(" {} |", type_name));
    }
    table.push_str("\n|-----|");
    for _ in &roms_24pin {
        table.push_str("------|");
    }
    table.push_str("\n");

    // Generate row for each pin
    for pin in 1..=24 {
        table.push_str(&format!("| {} |", pin));
        for (_, rom_type) in &roms_24pin {
            let function = get_pin_function(pin, rom_type);
            table.push_str(&format!(" {} |", function));
        }
        table.push_str("\n");
    }

    table
}

/// Generate 28-pin package pin comparison table
fn generate_pin_comparison_table_28pin(config: &RomTypesConfig) -> String {
    let mut table = String::new();

    // Get all 28-pin ROMs sorted by size
    let mut roms_28pin: Vec<_> = config
        .rom_types
        .iter()
        .filter(|(_, rom)| rom.pins == 28)
        .collect();
    roms_28pin.sort_by_key(|(name, rom)| {
        let family = if name.starts_with("23") { 0 } else { 1 };
        (family, rom.size, *name)
    });

    if roms_28pin.is_empty() {
        return table;
    }

    table.push_str("### 28-pin Package\n\n");
    table.push_str("| Pin |");
    for (type_name, _) in &roms_28pin {
        table.push_str(&format!(" {} |", type_name));
    }
    table.push_str("\n|-----|");
    for _ in &roms_28pin {
        table.push_str("------|");
    }
    table.push_str("\n");

    // Generate row for each pin
    for pin in 1..=28 {
        table.push_str(&format!("| {} |", pin));
        for (_, rom_type) in &roms_28pin {
            let function = get_pin_function(pin, rom_type);
            table.push_str(&format!(" {} |", function));
        }
        table.push_str("\n");
    }

    table
}

/// Generate detailed pinout for a single ROM type
fn generate_detailed_pinout(type_name: &str, rom_type: &RomType) -> String {
    let mut doc = String::new();

    doc.push_str(&format!("### {} - {}\n\n", type_name, rom_type.description));
    doc.push_str(&format!("**Package:** {}-pin DIP  \n", rom_type.pins));
    doc.push_str(&format!("**Capacity:** {} bytes  \n", rom_type.size));

    // Control line summary
    let control_summary = format_control_lines_detailed(rom_type);
    doc.push_str(&format!("**Control:** {}  \n\n", control_summary));

    // Pin table
    doc.push_str("| Function | Pins | Notes |\n");
    doc.push_str("|----------|------|-------|\n");

    // Address lines
    let addr_pins: Vec<String> = rom_type.address.iter().map(|p| p.to_string()).collect();
    doc.push_str(&format!(
        "| Address (A0-A{}) | {} | {} address lines |\n",
        rom_type.address.len() - 1,
        addr_pins.join(","),
        rom_type.address.len()
    ));

    // Data lines
    let data_pins: Vec<String> = rom_type.data.iter().map(|p| p.to_string()).collect();
    doc.push_str(&format!(
        "| Data (D0-D7) | {} | 8 data lines |\n",
        data_pins.join(",")
    ));

    // Control lines
    let mut control_lines: Vec<_> = rom_type.control.iter().collect();
    control_lines.sort_by_key(|(name, _)| *name);

    for (name, control) in control_lines {
        let polarity = match control.line_type {
            ControlLineType::Configurable => "Configurable polarity",
            ControlLineType::FixedActiveLow => "Active low",
        };
        doc.push_str(&format!(
            "| {} | {} | {} |\n",
            name.to_uppercase(),
            control.pin,
            polarity
        ));
    }

    // Programming pins
    if let Some(ref prog) = rom_type.programming {
        if let Some(ref vpp) = prog.vpp {
            doc.push_str(&format!(
                "| VPP | {} | {} during read |\n",
                vpp.pin,
                format_read_state(&vpp.read_state)
            ));
        }
        if let Some(ref pgm) = prog.pgm {
            doc.push_str(&format!(
                "| /PGM | {} | {} during read |\n",
                pgm.pin,
                format_read_state(&pgm.read_state)
            ));
        }
        if let Some(ref pe) = prog.pe {
            doc.push_str(&format!(
                "| PE | {} | {} during read |\n",
                pe.pin,
                format_read_state(&pe.read_state)
            ));
        }
    }

    // Power pins
    if let Some(ref power_pins) = rom_type.power {
        for power_pin in power_pins {
            doc.push_str(&format!(
                "| {} | {} | {} |\n",
                power_pin.name, power_pin.pin, power_pin.voltage
            ));
        }
    }

    doc
}

// Helper functions

fn get_sorted_rom_types(config: &RomTypesConfig) -> Vec<(&String, &RomType)> {
    let mut types: Vec<_> = config.rom_types.iter().collect();
    types.sort_by_key(|(name, rom_type)| {
        let family = if name.starts_with("23") { 0 } else { 1 };
        (family, rom_type.size, *name)
    });
    types
}

fn format_size(bytes: usize) -> String {
    if bytes >= 1024 {
        format!("{}KB", bytes / 1024)
    } else {
        format!("{}B", bytes)
    }
}

fn format_control_lines(rom_type: &RomType) -> String {
    let mut lines = Vec::new();
    let mut control_vec: Vec<_> = rom_type.control.iter().collect();
    control_vec.sort_by_key(|(name, _)| *name);

    for (name, control) in control_vec {
        let polarity = match control.line_type {
            ControlLineType::Configurable => "",
            ControlLineType::FixedActiveLow => "/",
        };
        lines.push(format!(
            "{}{} (pin {})",
            polarity,
            name.to_uppercase(),
            control.pin
        ));
    }

    if lines.is_empty() {
        "None".to_string()
    } else {
        lines.join(", ")
    }
}

fn format_control_lines_detailed(rom_type: &RomType) -> String {
    let count = rom_type.control.len();
    if count == 0 {
        return "None".to_string();
    }

    let has_configurable = rom_type
        .control
        .values()
        .any(|c| c.line_type == ControlLineType::Configurable);

    if has_configurable {
        format!(
            "{} configurable CS line{}",
            count,
            if count > 1 { "s" } else { "" }
        )
    } else {
        let names: Vec<_> = rom_type
            .control
            .keys()
            .map(|n| format!("/{}", n.to_uppercase()))
            .collect();
        names.join(", ")
    }
}

fn format_programming_pins(rom_type: &RomType) -> String {
    if let Some(ref prog) = rom_type.programming {
        let mut parts = Vec::new();

        if let Some(ref vpp) = prog.vpp {
            parts.push(format!(
                "VPP: pin {} ({})",
                vpp.pin,
                format_read_state(&vpp.read_state)
            ));
        }

        if let Some(ref pgm) = prog.pgm {
            parts.push(format!(
                "/PGM: pin {} ({})",
                pgm.pin,
                format_read_state(&pgm.read_state)
            ));
        }

        if parts.is_empty() {
            "None".to_string()
        } else {
            parts.join("; ")
        }
    } else {
        "None".to_string()
    }
}

fn format_read_state(state: &str) -> String {
    match state {
        "vcc" => "VCC during read".to_string(),
        "high" => "High during read".to_string(),
        "low" => "Low during read".to_string(),
        "chip_select" => "Acts as /OE".to_string(),
        _ => state.to_string(),
    }
}

fn get_pin_function(pin: u8, rom_type: &RomType) -> String {
    let mut functions = Vec::new();

    // Check address lines
    if let Some(pos) = rom_type.address.iter().position(|&p| p == pin) {
        return format!("A{}", pos);
    }

    // Check data lines
    if let Some(pos) = rom_type.data.iter().position(|&p| p == pin) {
        return format!("D{}", pos);
    }

    // Check control lines
    for (name, control) in &rom_type.control {
        if control.pin == pin {
            let prefix = match control.line_type {
                ControlLineType::FixedActiveLow => "/",
                ControlLineType::Configurable => "",
            };
            functions.push(format!("{}{}", prefix, name.to_uppercase()));
        }
    }

    // Check programming pins
    if let Some(ref prog) = rom_type.programming {
        if let Some(ref vpp) = prog.vpp {
            if vpp.pin == pin {
                functions.push("VPP".to_string());
            }
        }
        if let Some(ref pgm) = prog.pgm {
            if pgm.pin == pin {
                functions.push("/PGM".to_string());
            }
        }
        if let Some(ref pe) = prog.pe {
            if pe.pin == pin {
                functions.push("PE".to_string());
            }
        }
    }

    if !functions.is_empty() {
        return functions.join("+");
    }

    // Check power pins
    if let Some(ref power_pins) = rom_type.power {
        for power_pin in power_pins {
            if power_pin.pin == pin {
                return power_pin.name.clone();
            }
        }
    }

    "NC".to_string()
}
