//! One ROM Lab - Error handling

// Copyright (c) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT licence

#[derive(Debug)]
pub enum Error {
    /// Invalid address
    Address,
    /// Buffer size too small
    Buffer,
}
