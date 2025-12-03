// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

#![allow(dead_code)]

use serde::{Deserialize, Deserializer};
use std::collections::{HashMap, HashSet};

include!("../../src/mcu.rs");

impl Port {
    pub fn from_str(s: &str) -> Option<Self> {
        match s.to_uppercase().as_str() {
            "0" => Some(Port::Zero),
            "A" => Some(Port::A),
            "B" => Some(Port::B),
            "C" => Some(Port::C),
            "D" => Some(Port::D),
            "NONE" => Some(Port::None),
            _ => None,
        }
    }
}

impl<'de> Deserialize<'de> for Port {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: Deserializer<'de>,
    {
        let s = String::deserialize(deserializer)?;
        Port::from_str(&s).ok_or_else(|| {
            serde::de::Error::custom(format!("Invalid port: {}, must be None, A, B, C, or D", s))
        })
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum McuFamily {
    Stm32f4,
    Rp2350,
}

impl From<&McuFamily> for Family {
    fn from(family: &McuFamily) -> Self {
        match family {
            McuFamily::Stm32f4 => Family::Stm32f4,
            McuFamily::Rp2350 => Family::Rp2350,
        }
    }
}

impl McuFamily {
    pub fn try_from_str(s: &str) -> Option<Self> {
        match s.to_lowercase().as_str() {
            "stm32f4" | "f4" => Some(McuFamily::Stm32f4),
            "rp2350" => Some(McuFamily::Rp2350),
            _ => None,
        }
    }

    pub fn max_valid_addr_pin(&self) -> u8 {
        match self {
            McuFamily::Stm32f4 => 13, // 15 - 2 (top two reserved for X1/X2)
            McuFamily::Rp2350 => 23,
        }
    }

    pub fn max_valid_addr_cs_pin(&self) -> u8 {
        match self {
            McuFamily::Stm32f4 => 15,
            McuFamily::Rp2350 => 23,
        }
    }

    pub fn max_valid_data_pin(&self) -> u8 {
        match self {
            McuFamily::Stm32f4 => 7,
            McuFamily::Rp2350 => 23,
        }
    }

    pub fn valid_pin_num(&self, pin: u8) -> bool {
        match self {
            McuFamily::Stm32f4 => pin <= 15,
            McuFamily::Rp2350 => pin <= 29,
        }
    }

    pub fn allowed_data_port(&self) -> Port {
        match self {
            McuFamily::Stm32f4 => Port::A,
            McuFamily::Rp2350 => Port::Zero,
        }
    }

    pub fn allowed_addr_port(&self) -> Port {
        match self {
            McuFamily::Stm32f4 => Port::C,
            McuFamily::Rp2350 => Port::Zero,
        }
    }

    pub fn allowed_cs_port(&self) -> Port {
        match self {
            McuFamily::Stm32f4 => Port::C,
            McuFamily::Rp2350 => Port::Zero,
        }
    }

    pub fn allowed_sel_port(&self) -> Port {
        match self {
            McuFamily::Stm32f4 => Port::B,
            McuFamily::Rp2350 => Port::Zero,
        }
    }

    pub fn valid_x1_pins(&self) -> Vec<u8> {
        match self {
            McuFamily::Stm32f4 => vec![14],
            McuFamily::Rp2350 => vec![
                0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
                23,
            ],
        }
    }

    pub fn valid_x2_pins(&self) -> Vec<u8> {
        match self {
            McuFamily::Stm32f4 => vec![15],
            McuFamily::Rp2350 => self.valid_x1_pins(),
        }
    }
}

#[derive(Debug, Deserialize, Clone)]
pub struct McuPorts {
    pub data_port: Port,
    pub addr_port: Port,
    pub cs_port: Port,
    pub sel_port: Port,
    pub status_port: Port,
}

#[derive(Debug, Deserialize, Clone)]
pub struct RomPins {
    pub quantity: u8,
}

#[derive(Debug, Deserialize, Clone)]
pub struct Rom {
    pub pins: RomPins,
}

#[derive(Debug, Deserialize, Clone)]
pub struct McuPins {
    pub data: Vec<u8>,
    pub addr: Vec<u8>,
    #[serde(default, deserialize_with = "deserialize_rom_map")]
    pub cs1: HashMap<String, u8>,
    #[serde(default, deserialize_with = "deserialize_rom_map")]
    pub cs2: HashMap<String, u8>,
    #[serde(default, deserialize_with = "deserialize_rom_map")]
    pub cs3: HashMap<String, u8>,
    pub x1: Option<u8>,
    pub x2: Option<u8>,
    #[serde(default, deserialize_with = "deserialize_rom_map")]
    pub ce: HashMap<String, u8>,
    #[serde(default, deserialize_with = "deserialize_rom_map")]
    pub oe: HashMap<String, u8>,
    pub x_jumper_pull: u8,
    pub sel: Vec<u8>,
    pub sel_jumper_pull: u8,
    pub status: u8,
}

#[derive(Debug, Deserialize, Clone)]
pub struct Mcu {
    #[serde(deserialize_with = "deserialize_mcu_family")]
    pub family: McuFamily,
    pub ports: McuPorts,
    pub pins: McuPins,
    #[serde(default)]
    pub usb: Option<McuUsb>,
}

#[derive(Debug, Deserialize, Clone)]
pub struct McuUsb {
    pub present: bool,
    pub pins: Option<McuUsbPins>,
}

#[derive(Debug, Deserialize, Clone)]
pub struct McuUsbPins {
    pub vbus: u8,
    pub port: Port,
}

#[derive(Debug, Clone, Deserialize)]
pub struct HwConfigJson {
    pub description: String,
    #[serde(default)]
    pub alt: Vec<String>,
    pub rom: Rom,
    pub mcu: Mcu,
}

fn deserialize_mcu_family<'de, D>(deserializer: D) -> Result<McuFamily, D::Error>
where
    D: serde::Deserializer<'de>,
{
    let s = String::deserialize(deserializer)?;
    McuFamily::try_from_str(&s)
        .ok_or_else(|| serde::de::Error::custom(format!("Invalid MCU family: {}", s)))
}

fn deserialize_rom_map<'de, D>(deserializer: D) -> Result<HashMap<String, u8>, D::Error>
where
    D: serde::Deserializer<'de>,
{
    HashMap::deserialize(deserializer)
}

pub fn validate_config(name: &str, config: &HwConfigJson) {
    // Check data pins are exactly 8
    if config.mcu.pins.data.len() != 8 {
        panic!(
            "{}: data pins must be exactly 8, found {}",
            name,
            config.mcu.pins.data.len()
        );
    }

    // Validate pins consistent within pin arrays
    validate_pin_array(&config.mcu, &config.mcu.pins.data, "data", name, 8);
    validate_pin_array(&config.mcu, &config.mcu.pins.addr, "addr", name, 16);
    validate_pin_array(&config.mcu, &config.mcu.pins.sel, "sel", name, 7);

    // Validate values in pin arrays are within valid ranges
    validate_pin_values(
        &config.mcu.pins.data,
        "data",
        name,
        8,
        config.mcu.family.max_valid_data_pin(),
    );

    match config.rom.pins.quantity {
        24 => validate_pin_values(
            &config.mcu.pins.addr,
            "addr",
            name,
            13,
            config.mcu.family.max_valid_addr_pin(),
        ),
        28 => validate_pin_values(
            &config.mcu.pins.addr,
            "addr",
            name,
            14,
            config.mcu.family.max_valid_addr_cs_pin(),
        ),
        _ => panic!(
            "{}: unsupported ROM type {}, expected 24 or 28-pin ROM",
            name, config.rom.pins.quantity
        ),
    }

    // Validate data pins are contiguous within 8-bit window on 8-boundary
    {
        let min_data_pin = *config.mcu.pins.data.iter().min().unwrap();
        let max_data_pin = *config.mcu.pins.data.iter().max().unwrap();

        if min_data_pin % 8 != 0 {
            panic!(
                "{}: data pins must start on 8-byte boundary, got min pin {}",
                name, min_data_pin
            );
        }

        if max_data_pin >= min_data_pin + 8 {
            panic!(
                "{}: data pins must be within 8-bit window, got range {}-{}",
                name, min_data_pin, max_data_pin
            );
        }
    }

    // Validate address pins are contiguous within 16-bit window on 8-boundary
    {
        let min_addr_pin = *config.mcu.pins.addr.iter().min().unwrap();
        let max_addr_pin = *config.mcu.pins.addr.iter().max().unwrap();

        if min_addr_pin % 8 != 0 {
            panic!(
                "{}: address pins must start on 8-byte boundary, got min pin {}",
                name, min_addr_pin
            );
        }

        if max_addr_pin >= min_addr_pin + 16 {
            panic!(
                "{}: address pins must be within 16-bit window, got range {}-{}",
                name, min_addr_pin, max_addr_pin
            );
        }
    }

    // Validate ports
    if config.mcu.ports.data_port != config.mcu.family.allowed_data_port() {
        panic!(
            "{}: data port must be {:?}, found {:?}",
            name,
            config.mcu.family.allowed_data_port(),
            config.mcu.ports.data_port
        );
    }
    if config.mcu.ports.addr_port != config.mcu.family.allowed_addr_port() {
        panic!(
            "{}: address port must be {:?}, found {:?}",
            name,
            config.mcu.family.allowed_addr_port(),
            config.mcu.ports.addr_port
        );
    }
    if config.mcu.ports.cs_port != config.mcu.family.allowed_cs_port() {
        panic!(
            "{}: CS port must be {:?}, found {:?}",
            name,
            config.mcu.family.allowed_cs_port(),
            config.mcu.ports.cs_port
        );
    }
    if config.mcu.ports.sel_port != config.mcu.family.allowed_sel_port() {
        panic!(
            "{}: SEL port must be {:?}, found {:?}",
            name,
            config.mcu.family.allowed_sel_port(),
            config.mcu.ports.sel_port
        );
    }

    // Validate optional pins
    if let Some(pin) = config.mcu.pins.x1 {
        validate_pin_number(&config.mcu, pin, "x1", name);
    }
    if let Some(pin) = config.mcu.pins.x2 {
        validate_pin_number(&config.mcu, pin, "x2", name);
    }

    // Validate X1/X2 pins
    if let Some(x1_pin) = config.mcu.pins.x1 {
        let valid_pins = config.mcu.family.valid_x1_pins();
        if !valid_pins.contains(&x1_pin) {
            panic!(
                "{}: X1 pin must be within {:?}, found {}",
                name, valid_pins, x1_pin
            );
        }
    }
    if let Some(x2_pin) = config.mcu.pins.x2 {
        let valid_pins = config.mcu.family.valid_x2_pins();
        if !valid_pins.contains(&x2_pin) {
            panic!(
                "{}: X2 pin must be within {:?}, found {}",
                name, valid_pins, x2_pin
            );
        }
    }

    // Both X1 and X2 must be provided together
    if config.mcu.pins.x1.is_some() != config.mcu.pins.x2.is_some() {
        panic!(
            "{}: X1 and X2 pins must both be provided or both omitted",
            name
        );
    }

    // Validate sel_jumper_pull
    if config.mcu.pins.sel_jumper_pull > 1 {
        panic!(
            "{}: sel_jumper_pull must be 0 (pull down) or 1 (pull up), found {}",
            name, config.mcu.pins.sel_jumper_pull
        );
    }

    // Group pins by port for conflict checking
    let mut port_pins: HashMap<Port, Vec<(&str, u8)>> = HashMap::new();

    // Add data pins
    for &pin in &config.mcu.pins.data {
        port_pins
            .entry(config.mcu.ports.data_port)
            .or_default()
            .push(("data", pin));
    }

    // Add address pins
    for &pin in &config.mcu.pins.addr {
        port_pins
            .entry(config.mcu.ports.addr_port)
            .or_default()
            .push(("addr", pin));
    }

    // Add sel pins
    for &pin in &config.mcu.pins.sel {
        port_pins
            .entry(config.mcu.ports.sel_port)
            .or_default()
            .push(("sel", pin));
    }

    // Add CS pins
    for &pin in config.mcu.pins.cs1.values() {
        port_pins
            .entry(config.mcu.ports.cs_port)
            .or_default()
            .push(("cs1", pin));
    }
    for &pin in config.mcu.pins.cs2.values() {
        port_pins
            .entry(config.mcu.ports.cs_port)
            .or_default()
            .push(("cs2", pin));
    }
    for &pin in config.mcu.pins.cs3.values() {
        port_pins
            .entry(config.mcu.ports.cs_port)
            .or_default()
            .push(("cs3", pin));
    }

    // Add optional pins
    if let Some(pin) = config.mcu.pins.x1 {
        port_pins
            .entry(config.mcu.ports.cs_port)
            .or_default()
            .push(("x1", pin));
    }
    if let Some(pin) = config.mcu.pins.x2 {
        port_pins
            .entry(config.mcu.ports.cs_port)
            .or_default()
            .push(("x2", pin));
    }

    for &pin in config.mcu.pins.ce.values() {
        port_pins
            .entry(config.mcu.ports.cs_port)
            .or_default()
            .push(("ce", pin));
    }
    for &pin in config.mcu.pins.oe.values() {
        port_pins
            .entry(config.mcu.ports.cs_port)
            .or_default()
            .push(("oe", pin));
    }

    let pin = config.mcu.pins.status;
    port_pins
        .entry(config.mcu.ports.status_port)
        .or_default()
        .push(("status", pin));

    // Add USB pins
    if let Some(usb) = &config.mcu.usb {
        if usb.present {
            if let Some(usb_pins) = &usb.pins {
                port_pins
                    .entry(usb_pins.port)
                    .or_default()
                    .push(("usb_vbus", usb_pins.vbus));
            }
        }
    }

    // Check for conflicts within each port
    for (port, pins) in port_pins {
        let mut used_pins: HashMap<u8, Vec<&str>> = HashMap::new();

        for (pin_type, pin_num) in pins {
            used_pins.entry(pin_num).or_default().push(pin_type);
        }

        for (pin_num, pin_types) in used_pins {
            if pin_types.len() > 1 {
                let cs_types: HashSet<&str> =
                    ["cs1", "cs2", "cs3", "ce", "oe"].into_iter().collect();
                let has_cs = pin_types.iter().any(|t| cs_types.contains(t));
                let all_cs_or_addr = pin_types
                    .iter()
                    .all(|t| cs_types.contains(t) || *t == "addr");

                if !(has_cs && all_cs_or_addr) {
                    panic!(
                        "{}: pin {} on port {:?} used by multiple incompatible functions: {:?}",
                        name, pin_num, port, pin_types
                    );
                }
            }
        }
    }
}

fn validate_pin_number(mcu: &Mcu, pin: u8, pin_name: &str, config_name: &str) {
    if !mcu.family.valid_pin_num(pin) && pin != 255 {
        panic!(
            "{}: invalid pin number {} for {}, must be valid or 255 if pin not exposed",
            config_name, pin, pin_name,
        );
    }
}

fn validate_pin_array(mcu: &Mcu, pins: &[u8], pin_type: &str, config_name: &str, max_pins: u8) {
    let mut seen = HashSet::new();
    let mut num_pins = 0;
    for &pin in pins {
        validate_pin_number(mcu, pin, pin_type, config_name);
        if !seen.insert(pin) {
            panic!(
                "{}: duplicate pin {} in {} array",
                config_name, pin, pin_type
            );
        }
        num_pins += 1;
    }
    if num_pins > max_pins as usize {
        panic!(
            "{}: too many pins in {} array, maximum is {}",
            config_name, pin_type, max_pins
        );
    }
}

fn validate_pin_values(
    pins: &[u8],
    pin_type: &str,
    config_name: &str,
    min_valid: usize,
    valid_value: u8,
) {
    for (ii, &pin) in pins.iter().enumerate() {
        if ii >= min_valid {
            break;
        }
        if pin > valid_value {
            panic!(
                "{}: invalid pin value {} in {} array, must be 0-{}",
                config_name, pin, pin_type, valid_value
            );
        }
    }
}
