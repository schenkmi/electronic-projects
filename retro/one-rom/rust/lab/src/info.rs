//! One ROM Lab - Firmware Information

// Copyright (c) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT licence

use crate::types::{FlashInfo, RamInfo};

unsafe extern "C" {
    static _SEGGER_RTT: u8;
}

include!(concat!(env!("OUT_DIR"), "/built.rs"));

#[allow(static_mut_refs)]
#[allow(improper_ctypes)]
#[unsafe(link_section = ".lab_flash_info")]
#[used]
pub static LAB_FLASH_INFO: FlashInfo = FlashInfo {
    magic: *b"ONEL",
    major_version: PKG_VERSION_MAJOR,
    minor_version: PKG_VERSION_MINOR,
    patch_version: PKG_VERSION_PATCH,
    build_number: "",
    mcu: "f405rg",
    hw_rev: "24-f",
    features: FEATURES_LOWERCASE_STR,
    rtt: unsafe { &_SEGGER_RTT as *const u8 as *const core::ffi::c_void },
    reserved: [0; 192],
};

// This section gets placed in flash, and then copied into RAM at startup,
// using `copy_lab_ram_info()` below.
#[unsafe(link_section = ".lab_ram_info")]
#[used]
pub static mut LAB_RAM_INFO: RamInfo = RamInfo {
    magic: *b"onel",
    rom_data: core::ptr::null(),
    rpc_cmd_channel: core::ptr::null(),
    rpc_rsp_channel: core::ptr::null(),
    rpc_cmd_channel_size: 0,
    rpc_rsp_channel_size: 0,
    reserved: [0; 236],
};

// This section gets called before main(), and copies the info from flash to
// RAM.
#[cortex_m_rt::pre_init]
unsafe fn copy_lab_ram_info() {
    unsafe extern "C" {
        static __lab_ram_info_load: u8;
        static __lab_ram_info_start: u8;
        static __lab_ram_info_size: u8;
    }

    unsafe {
        let src = &__lab_ram_info_load as *const u8;
        let dst = &__lab_ram_info_start as *const u8 as *mut u8;
        let size = &__lab_ram_info_size as *const u8 as usize;
        core::ptr::copy_nonoverlapping(src, dst, size);
    }
}
