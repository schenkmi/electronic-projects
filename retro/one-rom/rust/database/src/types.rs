//! One ROM Database - Types

// Copyright (c) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT licence

use crate::Error;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Default, serde::Serialize, serde::Deserialize)]
#[repr(u8)]
pub enum CsActiveByte {
    #[default]
    Low = 0,
    High = 1,
}

impl CsActiveByte {
    pub fn from_byte(byte: u8) -> Result<Self, Error> {
        match byte {
            0 => Ok(CsActiveByte::Low),
            1 => Ok(CsActiveByte::High),
            _ => Err(Error::ParseError),
        }
    }

    pub fn to_byte(&self) -> u8 {
        *self as u8
    }
}

impl From<CsActive> for CsActiveByte {
    fn from(cs: CsActive) -> Self {
        match cs {
            CsActive::Low => CsActiveByte::Low,
            CsActive::High => CsActiveByte::High,
        }
    }
}

/// Whether a CS line is active low or active high
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default, serde::Serialize, serde::Deserialize)]
pub enum CsActive {
    #[allow(dead_code)]
    High,

    #[default]
    Low,
}

impl core::fmt::Display for CsActive {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        match self {
            CsActive::High => write!(f, "Active High"),
            CsActive::Low => write!(f, "Active Low"),
        }
    }
}

impl From<CsActiveByte> for CsActive {
    fn from(byte: CsActiveByte) -> Self {
        match byte {
            CsActiveByte::Low => CsActive::Low,
            CsActiveByte::High => CsActive::High,
        }
    }
}

impl CsActive {
    fn bit(&self) -> usize {
        match self {
            CsActive::High => 1,
            CsActive::Low => 0,
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
#[repr(u8)]
pub enum RomTypeByte {
    Type2364 = 0x00,
    Type2332 = 0x01,
    Type2316 = 0x02,
}

impl RomTypeByte {
    pub fn from_byte(byte: u8) -> Result<Self, Error> {
        match byte {
            0x00 => Ok(RomTypeByte::Type2364),
            0x01 => Ok(RomTypeByte::Type2332),
            0x02 => Ok(RomTypeByte::Type2316),
            _ => Err(Error::ParseError),
        }
    }

    pub fn to_byte(&self) -> u8 {
        *self as u8
    }
}

/// Supported types of ROMs.  This type includes the chip select behaviour of
/// the ROM, which was mask programmed at factory for the original ROM chips.
#[derive(Debug, Clone, Copy, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
pub enum RomType {
    /// A 2364 ROM
    Type2364 { cs: CsActive },

    /// A 2332 ROM
    Type2332 { cs1: CsActive, cs2: CsActive },

    /// A 2316 ROM
    Type2316 {
        cs1: CsActive,
        cs2: CsActive,
        cs3: CsActive,
    },
}

impl core::fmt::Display for RomType {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        write!(f, "{} ({})", self.type_str(), self.cs_str())
    }
}

impl RomType {
    const CS_2364_ADDR: usize = 13;
    const CS1_2332_ADDR: usize = 13;
    const CS2_2332_ADDR: usize = 12;
    const CS1_2316_ADDR: usize = 13;
    const CS2_2316_ADDR: usize = 11;
    const CS3_2316_ADDR: usize = 12;

    /// Returns the max size of ROM supported by this object.
    pub const fn max_size() -> usize {
        8192
    }

    /// Returns the size of this ROM.
    pub const fn size(&self) -> usize {
        match self {
            RomType::Type2364 { .. } => 8192,
            RomType::Type2332 { .. } => 4096,
            RomType::Type2316 { .. } => 2048,
        }
    }

    /// Returns the active CS mask for this ROM type.
    pub fn cs_active_mask(&self) -> usize {
        match self {
            RomType::Type2364 { cs } => cs.bit() << Self::CS_2364_ADDR,
            RomType::Type2332 { cs1, cs2 } => {
                cs1.bit() << Self::CS1_2332_ADDR | cs2.bit() << Self::CS2_2332_ADDR
            }
            RomType::Type2316 { cs1, cs2, cs3 } => {
                cs1.bit() << Self::CS1_2316_ADDR
                    | cs2.bit() << Self::CS2_2316_ADDR
                    | cs3.bit() << Self::CS3_2316_ADDR
            }
        }
    }

    /// Returns all supported ROM types.
    pub const fn all() -> &'static [RomType] {
        &ALL_ROM_TYPES
    }

    pub const fn type_str(&self) -> &'static str {
        match self {
            RomType::Type2364 { .. } => "2364",
            RomType::Type2332 { .. } => "2332",
            RomType::Type2316 { .. } => "2316",
        }
    }

    pub const fn cs_str(&self) -> &'static str {
        match self {
            RomType::Type2364 { cs } => match cs {
                CsActive::Low => "CS Low",
                CsActive::High => "CS High",
            },
            RomType::Type2332 { cs1, cs2 } => match (cs1, cs2) {
                (CsActive::Low, CsActive::Low) => "CS1 Low, CS2 Low",
                (CsActive::Low, CsActive::High) => "CS1 Low, CS2 High",
                (CsActive::High, CsActive::Low) => "CS1 High, CS2 Low",
                (CsActive::High, CsActive::High) => "CS1 High, CS2 High",
            },
            RomType::Type2316 { cs1, cs2, cs3 } => match (cs1, cs2, cs3) {
                (CsActive::Low, CsActive::Low, CsActive::Low) => "CS1 Low, CS2 Low, CS3 Low",
                (CsActive::Low, CsActive::Low, CsActive::High) => "CS1 Low, CS2 Low, CS3 High",
                (CsActive::Low, CsActive::High, CsActive::Low) => "CS1 Low, CS2 High, CS3 Low",
                (CsActive::Low, CsActive::High, CsActive::High) => "CS1 Low, CS2 High, CS3 High",
                (CsActive::High, CsActive::Low, CsActive::Low) => "CS1 High, CS2 Low, CS3 Low",
                (CsActive::High, CsActive::Low, CsActive::High) => "CS1 High, CS2 Low, CS3 High",
                (CsActive::High, CsActive::High, CsActive::Low) => "CS1 High, CS2 High, CS3 Low",
                (CsActive::High, CsActive::High, CsActive::High) => "CS1 High, CS2 High, CS3 High",
            },
        }
    }

    /// Retrieves the binary size of this structure when binary serialized.
    pub const fn binary_size() -> usize {
        4
    }

    /// Format is RomTypeByte followed by up to 3 CsActiveByte values.
    pub fn from_bytes(buf: &[u8]) -> Result<Self, Error> {
        if buf.len() < Self::binary_size() {
            return Err(Error::ParseError);
        }
        match RomTypeByte::from_byte(buf[0])? {
            RomTypeByte::Type2364 => {
                let cs = CsActiveByte::from_byte(buf[1])?.into();
                Ok(RomType::Type2364 { cs })
            }
            RomTypeByte::Type2332 => {
                let cs1 = CsActiveByte::from_byte(buf[1])?.into();
                let cs2 = CsActiveByte::from_byte(buf[2])?.into();
                Ok(RomType::Type2332 { cs1, cs2 })
            }
            RomTypeByte::Type2316 => {
                let cs1 = CsActiveByte::from_byte(buf[1])?.into();
                let cs2 = CsActiveByte::from_byte(buf[2])?.into();
                let cs3 = CsActiveByte::from_byte(buf[3])?.into();
                Ok(RomType::Type2316 { cs1, cs2, cs3 })
            }
        }
    }

    /// Serializes this structure into the given buffer.
    pub fn to_bytes(&self, buf: &mut [u8]) -> Result<(), Error> {
        if buf.len() < Self::binary_size() {
            return Err(Error::ParseError);
        }
        match self {
            RomType::Type2364 { cs } => {
                buf[0] = RomTypeByte::Type2364.to_byte();
                buf[1] = CsActiveByte::from(*cs).to_byte();
                buf[2] = 0;
                buf[3] = 0;
            }
            RomType::Type2332 { cs1, cs2 } => {
                buf[0] = RomTypeByte::Type2332.to_byte();
                buf[1] = CsActiveByte::from(*cs1).to_byte();
                buf[2] = CsActiveByte::from(*cs2).to_byte();
                buf[3] = 0;
            }
            RomType::Type2316 { cs1, cs2, cs3 } => {
                buf[0] = RomTypeByte::Type2316.to_byte();
                buf[1] = CsActiveByte::from(*cs1).to_byte();
                buf[2] = CsActiveByte::from(*cs2).to_byte();
                buf[3] = CsActiveByte::from(*cs3).to_byte();
            }
        }
        Ok(())
    }
}

// Enumeration of all possible ROM types.
const NUM_ROM_TYPES: usize = 14;
const ALL_ROM_TYPES: [RomType; NUM_ROM_TYPES] = [
    RomType::Type2364 { cs: CsActive::Low },
    RomType::Type2364 { cs: CsActive::High },
    RomType::Type2332 {
        cs1: CsActive::Low,
        cs2: CsActive::Low,
    },
    RomType::Type2332 {
        cs1: CsActive::Low,
        cs2: CsActive::High,
    },
    RomType::Type2332 {
        cs1: CsActive::High,
        cs2: CsActive::Low,
    },
    RomType::Type2332 {
        cs1: CsActive::High,
        cs2: CsActive::High,
    },
    RomType::Type2316 {
        cs1: CsActive::Low,
        cs2: CsActive::Low,
        cs3: CsActive::Low,
    },
    RomType::Type2316 {
        cs1: CsActive::Low,
        cs2: CsActive::Low,
        cs3: CsActive::High,
    },
    RomType::Type2316 {
        cs1: CsActive::Low,
        cs2: CsActive::High,
        cs3: CsActive::Low,
    },
    RomType::Type2316 {
        cs1: CsActive::Low,
        cs2: CsActive::High,
        cs3: CsActive::High,
    },
    RomType::Type2316 {
        cs1: CsActive::High,
        cs2: CsActive::Low,
        cs3: CsActive::Low,
    },
    RomType::Type2316 {
        cs1: CsActive::High,
        cs2: CsActive::Low,
        cs3: CsActive::High,
    },
    RomType::Type2316 {
        cs1: CsActive::High,
        cs2: CsActive::High,
        cs3: CsActive::Low,
    },
    RomType::Type2316 {
        cs1: CsActive::High,
        cs2: CsActive::High,
        cs3: CsActive::High,
    },
];
