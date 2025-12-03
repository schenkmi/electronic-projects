//! One ROM Lab - Types

// Copyright (c) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT licence

/// Information about One ROM Lab's firmware.
///
/// Note &'static str is a "fat" pointer, with 4 bytes pointer and 4 bytes
/// length.
#[repr(C)]
pub struct FlashInfo {
    pub magic: [u8; 4],
    pub major_version: &'static str,
    pub minor_version: &'static str,
    pub patch_version: &'static str,
    pub build_number: &'static str,
    pub mcu: &'static str,
    pub hw_rev: &'static str,
    pub features: &'static str,
    pub rtt: *const core::ffi::c_void,
    pub reserved: [u8; 192],
}

// Required to allow us to store a C pointer in the static LAB_FLASH_INFO
unsafe impl Sync for FlashInfo {}

/// Information about One ROM Lab's runtime state.
#[repr(C)]
pub struct RamInfo {
    pub magic: [u8; 4],
    pub rom_data: *const core::ffi::c_void,
    pub rpc_cmd_channel: *const core::ffi::c_void,
    pub rpc_rsp_channel: *const core::ffi::c_void,
    pub rpc_cmd_channel_size: u16,
    pub rpc_rsp_channel_size: u16,
    pub reserved: [u8; 236],
}
