//! One ROM Protocol

// Copyright (c) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT licence

#![no_std]

extern crate alloc;

use onerom_database::Error as DbError;

pub mod lab;

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Error {
    /// Buffer too small for the data
    BufferTooSmall,
    /// Response was not as expected
    InvalidResponse,
    /// Invalid data received
    InvalidData,
    /// No ROM detected
    NoRom,
    /// ROM not recognised
    RomNotRecognised,
}

impl From<DbError> for Error {
    fn from(err: DbError) -> Self {
        match err {
            DbError::ParseError => Error::InvalidData,
        }
    }
}
