// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

use serde::{Deserialize, Serialize};
use std::collections::BTreeMap;
use std::fmt;

const MAX_ADDRESS_LINES: usize = 16;
const DATA_LINE_COUNT: usize = 8;
const MIN_PIN_NUMBER: u8 = 1;
const VALID_PIN_COUNTS: &[u8] = &[24, 28];
const VALID_READ_STATES: &[&str] = &["vcc", "high", "low", "chip_select"];
const VALID_CONTROL_LINES: &[&str] = &["cs1", "cs2", "cs3", "ce", "oe"];

#[derive(Debug, Clone, PartialEq, Serialize, Deserialize)]
#[serde(rename_all = "snake_case")]
pub enum ControlLineType {
    Configurable,
    FixedActiveLow,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ControlLine {
    pub pin: u8,
    #[serde(rename = "type")]
    pub line_type: ControlLineType,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ProgrammingPin {
    pub pin: u8,
    pub read_state: String,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ProgrammingConfig {
    #[serde(skip_serializing_if = "Option::is_none")]
    pub vpp: Option<ProgrammingPin>,

    #[serde(skip_serializing_if = "Option::is_none")]
    pub pgm: Option<ProgrammingPin>,

    #[serde(skip_serializing_if = "Option::is_none")]
    pub pe: Option<ProgrammingPin>,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct PowerPin {
    pub name: String,
    pub pin: u8,
    pub voltage: String,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct RomType {
    pub description: String,
    pub pins: u8,
    pub size: usize,
    pub address: Vec<u8>,
    pub data: Vec<u8>,
    pub control: BTreeMap<String, ControlLine>,

    #[serde(skip_serializing_if = "Option::is_none")]
    pub programming: Option<ProgrammingConfig>,

    #[serde(skip_serializing_if = "Option::is_none")]
    pub power: Option<Vec<PowerPin>>,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct RomTypesConfig {
    pub rom_types: BTreeMap<String, RomType>,
}

#[derive(Debug, Clone, PartialEq)]
pub enum ValidationError {
    JsonParseError(String),
    InvalidPinNumber {
        rom_type: String,
        pin: u8,
        max: u8,
    },
    AddressSizeMismatch {
        rom_type: String,
        address_lines: usize,
        expected_size: usize,
        actual_size: usize,
    },
    InvalidDataLineCount {
        rom_type: String,
        count: usize,
    },
    DuplicatePin {
        rom_type: String,
        pin: u8,
    },
    InvalidReadState {
        rom_type: String,
        pin_name: String,
        state: String,
    },
    InvalidPackagePinCount {
        rom_type: String,
        pins: u8,
    },
    TooManyAddressLines {
        rom_type: String,
        count: usize,
    },
    IncompatibleControlLines {
        rom_type: String,
        combination: String,
    },
    UnknownControlLine {
        rom_type: String,
        line_name: String,
    },
}

impl fmt::Display for ValidationError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            ValidationError::JsonParseError(msg) => {
                write!(f, "JSON parse error: {}", msg)
            }
            ValidationError::InvalidPinNumber { rom_type, pin, max } => {
                write!(
                    f,
                    "ROM type '{}': pin {} is out of range (valid: {}-{})",
                    rom_type, pin, MIN_PIN_NUMBER, max
                )
            }
            ValidationError::AddressSizeMismatch {
                rom_type,
                address_lines,
                expected_size,
                actual_size,
            } => {
                write!(
                    f,
                    "ROM type '{}': {} address lines should give {} bytes, but size is {}",
                    rom_type, address_lines, expected_size, actual_size
                )
            }
            ValidationError::InvalidDataLineCount { rom_type, count } => {
                write!(
                    f,
                    "ROM type '{}': must have {} data lines, found {}",
                    rom_type, DATA_LINE_COUNT, count
                )
            }
            ValidationError::DuplicatePin { rom_type, pin } => {
                write!(
                    f,
                    "ROM type '{}': pin {} is used multiple times",
                    rom_type, pin
                )
            }
            ValidationError::InvalidReadState {
                rom_type,
                pin_name,
                state,
            } => {
                write!(
                    f,
                    "ROM type '{}': invalid read state '{}' for pin '{}' (valid: {:?})",
                    rom_type, state, pin_name, VALID_READ_STATES
                )
            }
            ValidationError::InvalidPackagePinCount { rom_type, pins } => {
                write!(
                    f,
                    "ROM type '{}': invalid pin count {} (valid: {:?})",
                    rom_type, pins, VALID_PIN_COUNTS
                )
            }
            ValidationError::TooManyAddressLines { rom_type, count } => {
                write!(
                    f,
                    "ROM type '{}': {} address lines exceeds maximum of {}",
                    rom_type, count, MAX_ADDRESS_LINES
                )
            }
            ValidationError::IncompatibleControlLines {
                rom_type,
                combination,
            } => {
                write!(
                    f,
                    "ROM type '{}': incompatible chip select line combination: {}.\nCS1/2/3 cannot be used with CE/OE.",
                    rom_type, combination
                )
            }
            ValidationError::UnknownControlLine {
                rom_type,
                line_name,
            } => {
                let valid_lines = VALID_CONTROL_LINES.join(", ");
                write!(
                    f,
                    "ROM type '{}': unrecognised control line name '{}'.\nValid names are: {valid_lines}",
                    rom_type, line_name
                )
            }
        }
    }
}

impl std::error::Error for ValidationError {}

impl RomTypesConfig {
    pub fn from_json(json: &str) -> Result<Self, ValidationError> {
        let config: RomTypesConfig = serde_json::from_str(json)
            .map_err(|e| ValidationError::JsonParseError(e.to_string()))?;

        config.validate()?;

        Ok(config)
    }

    pub fn validate(&self) -> Result<(), ValidationError> {
        for (type_name, rom_type) in &self.rom_types {
            rom_type.validate(type_name)?;
        }
        Ok(())
    }
}

impl RomType {
    pub fn validate(&self, type_name: &str) -> Result<(), ValidationError> {
        if !VALID_PIN_COUNTS.contains(&self.pins) {
            return Err(ValidationError::InvalidPackagePinCount {
                rom_type: type_name.to_string(),
                pins: self.pins,
            });
        }

        if self.address.len() > MAX_ADDRESS_LINES {
            return Err(ValidationError::TooManyAddressLines {
                rom_type: type_name.to_string(),
                count: self.address.len(),
            });
        }

        let expected_size = 1usize << self.address.len();
        if expected_size != self.size {
            return Err(ValidationError::AddressSizeMismatch {
                rom_type: type_name.to_string(),
                address_lines: self.address.len(),
                expected_size,
                actual_size: self.size,
            });
        }

        if self.data.len() != DATA_LINE_COUNT {
            return Err(ValidationError::InvalidDataLineCount {
                rom_type: type_name.to_string(),
                count: self.data.len(),
            });
        }

        let mut used_pins = Vec::new();

        for &pin in &self.address {
            self.validate_pin_number(type_name, pin)?;
            self.check_duplicate_pin(type_name, pin, &mut used_pins)?;
        }

        for &pin in &self.data {
            self.validate_pin_number(type_name, pin)?;
            self.check_duplicate_pin(type_name, pin, &mut used_pins)?;
        }

        for (_line_name, control) in &self.control {
            self.validate_pin_number(type_name, control.pin)?;
            self.check_duplicate_pin(type_name, control.pin, &mut used_pins)?;
        }

        if let Some(ref prog) = self.programming {
            if let Some(ref vpp) = prog.vpp {
                self.validate_pin_number(type_name, vpp.pin)?;
                self.validate_read_state(type_name, "vpp", &vpp.read_state)?;
                // Don't check duplicates - programming pins can overlap
            }
            if let Some(ref pgm) = prog.pgm {
                self.validate_pin_number(type_name, pgm.pin)?;
                self.validate_read_state(type_name, "pgm", &pgm.read_state)?;
                // Don't check duplicates
            }
            if let Some(ref pe) = prog.pe {
                self.validate_pin_number(type_name, pe.pin)?;
                self.validate_read_state(type_name, "pe", &pe.read_state)?;
                // Don't check duplicates
            }
        }

        // Validate power pins
        if let Some(ref power_pins) = self.power {
            for power_pin in power_pins {
                self.validate_pin_number(type_name, power_pin.pin)?;
                self.check_duplicate_pin(type_name, power_pin.pin, &mut used_pins)?;
            }
        }

        for line_name in self.control.keys() {
            // Check for unrecognised chip select line names.
            if !VALID_CONTROL_LINES.contains(&line_name.as_str()) {
                return Err(ValidationError::UnknownControlLine {
                    rom_type: type_name.to_string(),
                    line_name: line_name.to_string(),
                });
            }

            // And unexpected line types
            if line_name == "ce" || line_name == "oe" {
                if self.control[line_name].line_type != ControlLineType::FixedActiveLow {
                    return Err(ValidationError::IncompatibleControlLines {
                        rom_type: type_name.to_string(),
                        combination: format!("{} must be of type 'fixed_active_low'", line_name),
                    });
                }
            }
        }

        // Check for incompatible chip select line combinations.
        let cs_lines: Vec<&str> = self.control.keys().map(|s| s.as_str()).collect();
        if (cs_lines.contains(&"cs1") || cs_lines.contains(&"cs2") || cs_lines.contains(&"cs3"))
            && (cs_lines.contains(&"ce") || cs_lines.contains(&"oe"))
        {
            return Err(ValidationError::IncompatibleControlLines {
                rom_type: type_name.to_string(),
                combination: format!("{:?}", cs_lines),
            });
        }

        Ok(())
    }

    fn validate_pin_number(&self, type_name: &str, pin: u8) -> Result<(), ValidationError> {
        if pin < MIN_PIN_NUMBER || pin > self.pins {
            return Err(ValidationError::InvalidPinNumber {
                rom_type: type_name.to_string(),
                pin,
                max: self.pins,
            });
        }
        Ok(())
    }

    fn check_duplicate_pin(
        &self,
        type_name: &str,
        pin: u8,
        used_pins: &mut Vec<u8>,
    ) -> Result<(), ValidationError> {
        if used_pins.contains(&pin) {
            return Err(ValidationError::DuplicatePin {
                rom_type: type_name.to_string(),
                pin,
            });
        }
        used_pins.push(pin);
        Ok(())
    }

    fn validate_read_state(
        &self,
        type_name: &str,
        pin_name: &str,
        state: &str,
    ) -> Result<(), ValidationError> {
        if !VALID_READ_STATES.contains(&state) {
            return Err(ValidationError::InvalidReadState {
                rom_type: type_name.to_string(),
                pin_name: pin_name.to_string(),
                state: state.to_string(),
            });
        }
        Ok(())
    }
}
