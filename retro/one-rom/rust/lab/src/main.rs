//! One ROM Lab firmware

// Copyright (c) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT licence

#![no_std]
#![no_main]
#![feature(type_alias_impl_trait)]
#![feature(impl_trait_in_assoc_type)]

extern crate alloc;

#[allow(unused_imports)]
use log::{debug, error, info, trace, warn};

use embassy_executor::Spawner;
use embassy_executor::main as embassy_main;
use embassy_stm32::gpio::Flex;
use embassy_stm32::rcc::{
    AHBPrescaler, APBPrescaler, Pll, PllMul, PllPDiv, PllPreDiv, PllQDiv, PllSource, Sysclk, clocks,
};
#[cfg(feature = "repeat")]
use embassy_time::Timer;
use embedded_alloc::LlffHeap as Heap;
use panic_rtt_target as _;

#[cfg(feature = "control")]
mod control;
mod error;
mod info;
mod logs;
mod rom;
mod types;

pub use error::Error;
pub use rom::{Id as RomId, Rom};

use info::{LAB_RAM_INFO, PKG_VERSION};

#[global_allocator]
static HEAP: Heap = Heap::empty();

#[embassy_main]
async fn main(_spawner: Spawner) {
    // Initialize the heap allocator
    {
        use core::mem::MaybeUninit;
        const HEAP_SIZE: usize = 1024;
        static mut HEAP_MEM: [MaybeUninit<u8>; HEAP_SIZE] = [MaybeUninit::uninit(); HEAP_SIZE];
        unsafe { HEAP.init(&raw mut HEAP_MEM as usize, HEAP_SIZE) }
    }

    logs::init();
    info!("-----");
    info!("One ROM Lab v{}", PKG_VERSION);
    info!("Copyright (c) 2025 Piers Finlayson");

    // Set up the clocks - assume we are running on an F405RG with max clock
    // of 168MHz
    let mut config = embassy_stm32::Config::default();
    config.rcc.hsi = true;
    config.rcc.pll_src = PllSource::HSI;
    config.rcc.pll = Some(Pll {
        prediv: PllPreDiv::DIV16,
        mul: PllMul::MUL336,
        divp: Some(PllPDiv::DIV2),
        divq: Some(PllQDiv::DIV7),
        divr: None,
    });
    config.rcc.sys = Sysclk::PLL1_P;
    config.rcc.ahb_pre = AHBPrescaler::DIV1; // 168MHz
    config.rcc.apb1_pre = APBPrescaler::DIV4; // 42MHz (max for APB1)
    config.rcc.apb2_pre = APBPrescaler::DIV2; // 84MHz (max for APB2)

    let p = embassy_stm32::init(config);

    let clocks = clocks(&p.RCC);
    info!("-----");
    match clocks.sys.to_hertz() {
        Some(hz) => debug!("SYSCLK: {hz}"),
        None => warn!("SYSCLK: Unknown"),
    }

    debug!(
        "One ROM Lab Flash Info address: {:#010X}",
        &info::LAB_FLASH_INFO as *const _ as usize
    );
    #[allow(static_mut_refs)]
    unsafe {
        debug!(
            "One ROM Lab RAM Info address:   {:#010X}",
            &LAB_RAM_INFO as *const _ as usize
        );
    }

    // Collate the address and data pins
    let addr_pins = [
        Flex::new(p.PC5),
        Flex::new(p.PC4),
        Flex::new(p.PC6),
        Flex::new(p.PC7),
        Flex::new(p.PC3),
        Flex::new(p.PC2),
        Flex::new(p.PC1),
        Flex::new(p.PC0),
        Flex::new(p.PC8),
        Flex::new(p.PC13),
        Flex::new(p.PC11),
        Flex::new(p.PC12),
        Flex::new(p.PC9),
        Flex::new(p.PC10), // 2364 CS pin, set as "A13"
    ];
    let data_pins = [
        Flex::new(p.PA7),
        Flex::new(p.PA6),
        Flex::new(p.PA5),
        Flex::new(p.PA4),
        Flex::new(p.PA3),
        Flex::new(p.PA2),
        Flex::new(p.PA1),
        Flex::new(p.PA0),
    ];

    // Create the ROM object
    let mut rom = Rom::new(addr_pins, data_pins);
    unsafe {
        LAB_RAM_INFO.rom_data = rom.buf.as_ptr() as *const core::ffi::c_void;
    }
    rom.init();

    #[cfg(not(feature = "control"))]
    {
        loop {
            match rom.read_rom().await {
                Some(_) => break,
                None => info!("Failed to read ROM"),
            }

            #[cfg(feature = "oneshot")]
            {
                info!("Done");
                return;
            }
            #[cfg(feature = "repeat")]
            {
                info!("Waiting 5 seconds before reading again");
                Timer::after_secs(5).await;
            }
        }
    }

    #[cfg(feature = "control")]
    {
        let mut control = control::Control::new(rom);
        control.run().await;
    }
}

#[cfg(all(feature = "control", feature = "oneshot"))]
compile_error!("Features 'control' and 'oneshot' are mutually exclusive");
