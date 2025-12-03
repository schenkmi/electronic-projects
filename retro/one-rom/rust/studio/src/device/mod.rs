// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! Device handling module - USB (DFU) and debug probe devices
//!
//! This file primarily handles state and top-level methods.
//! Sub-modules handle view, messages and USB/probe specifics.

mod msg;
mod probe;
mod usb;
mod view;

use futures::stream::{self, Stream, StreamExt};
use iced::widget::Column;
use iced::{Element, Subscription, Task};
#[allow(unused_imports)]
use log::{debug, error, info, trace, warn};
use onerom_config::Model;

use crate::app::AppMessage;
use crate::hw::HardwareInfo;
use crate::internal_error;
use crate::studio::RuntimeInfo;
use crate::style::Style;
pub use msg::Message;
use probe::ProbeType;
use usb::UsbDeviceType;

/// At startup we want to check USB devices, then probe devices, so any
/// present USB device gets selected in preference to probe ones.
pub fn get_devices_startup() -> impl Stream<Item = AppMessage> {
    stream::once(usb::get_usb_device_list_async())
        .chain(stream::once(probe::get_probe_list_async()))
}

/// Sources of work for Device
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Client {
    /// Analyse tab
    Analyse,

    /// Create tab
    Create,
}

impl std::fmt::Display for Client {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Client::Analyse => write!(f, "Analyse"),
            Client::Create => write!(f, "Create"),
        }
    }
}

/// Addressing modes for device read/write
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Address {
    FlashStart,
    FlashOffset(u32),
    Absolute(u32),
}

impl std::fmt::Display for Address {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Address::FlashStart => write!(f, "FlashStart"),
            Address::FlashOffset(offset) => write!(f, "FlashOffset(0x{:X})", offset),
            Address::Absolute(addr) => write!(f, "Absolute(0x{:X})", addr),
        }
    }
}

impl Address {
    pub fn abs_from_hw_info(&self, hw_info: &HardwareInfo) -> Option<u32> {
        let offset = match self {
            Address::Absolute(addr) => return Some(*addr),
            Address::FlashStart => 0,
            Address::FlashOffset(offset) => *offset,
        };

        let base = if let Some(board) = &hw_info.board {
            board.mcu_family().get_flash_base()
        } else if let Some(variant) = &hw_info.mcu_variant {
            variant.family().get_flash_base()
        } else if let Some(model) = &hw_info.model {
            model.mcu_family().get_flash_base()
        } else {
            trace!("No board, MCU or model info to get flash base address");
            return None;
        };

        Some(base + offset)
    }

    pub fn abs_from_device(&self, device: &DeviceType) -> Option<u32> {
        match device {
            DeviceType::DebugProbe(_) => None,
            DeviceType::Usb(usb) => Some(self.abs_from_usb_device(usb)),
            DeviceType::None => None,
        }
    }

    pub fn abs_from_usb_device(&self, usb_device: &UsbDeviceType) -> u32 {
        let offset = match self {
            // Remap if the flash base address of the other model is requested
            Address::Absolute(addr) => {
                let addr = match usb_device {
                    UsbDeviceType::Fire(_) => {
                        if *addr == Model::Ice.mcu_family().get_flash_base() {
                            trace!("Attempt to read from Ice flash base address via Fire USB, remapping");
                            Model::Fire.mcu_family().get_flash_base()
                        } else {
                            *addr
                        }
                    }
                    UsbDeviceType::Ice(_) => {
                        if *addr == Model::Fire.mcu_family().get_flash_base() {
                            trace!("Attempt to read from Fire flash base address via Ice USB, remapping");
                            Model::Ice.mcu_family().get_flash_base()
                        } else {
                            *addr
                        }
                    }
                };
                return addr
            },
            Address::FlashStart => 0,
            Address::FlashOffset(offset) => *offset,
        };

        let base = match usb_device {
            UsbDeviceType::Ice(_) => Model::Ice.mcu_family().get_flash_base(),
            UsbDeviceType::Fire(_) => Model::Fire.mcu_family().get_flash_base(),
        };

        base + offset
    }
}

/// Device state
#[derive(Debug, Clone)]
pub struct Device {
    selected: DeviceType,
    selected_probe: Option<ProbeType>,
    selected_usb_device: Option<UsbDeviceType>,
    probes: Vec<ProbeType>,
    usb_devices: Vec<UsbDeviceType>,
    operating: Option<Client>,
}

impl Default for Device {
    fn default() -> Self {
        Self {
            selected: DeviceType::None,
            selected_probe: None,
            selected_usb_device: None,
            probes: Vec::new(),
            usb_devices: Vec::new(),
            operating: None,
        }
    }
}

impl Device {
    /// Instantiation
    pub fn new() -> Self {
        Self::default()
    }

    /// Is the device ready for operations?
    pub fn is_ready(&self) -> bool {
        !self.selected.is_none() && self.is_idle()
    }

    // Retrieve overall device object state (is a device operation underway)
    fn is_busy(&self) -> bool {
        self.operating.is_some()
    }
    fn is_idle(&self) -> bool {
        self.operating.is_none()
    }

    // Retrieve selected device
    fn selected(&self) -> &DeviceType {
        &self.selected
    }

    /// Main Device Message handling method
    pub fn update(&mut self, runtime_info: &RuntimeInfo, message: Message) -> Task<AppMessage> {
        msg::handle_message(self, runtime_info, message)
    }

    // Logic to handle a list of probes being updated:
    // - If one was selected before, see if it still exists
    // - If none exists (now), see if we can auto-select one
    // - If one now exists, and there's no device selected, select the probe
    fn probes_updated(&mut self) {
        // Check if selected probe is still connected
        if let Some(old_probe) = &self.selected_probe {
            if !self.probes.contains(&old_probe) {
                info!("Selected probe has been disconnected {old_probe}");
                self.selected_probe = None;
            } else {
                trace!("Still connected to probe {old_probe}");
            }
        }

        // Next, if there isn't a selected probe, see if there's one to auto-
        // select
        if self.selected_probe.is_none() {
            if let Some(probe) = self.probes.first().cloned() {
                info!("Selected Probe: {probe}");
                self.selected_probe = Some(probe.clone());
            } else {
                trace!("No probes detected");
            }
        }

        // Finally, if there' no selected device, but there's a selected probe,
        // select it.  This also clears the selected device if it has gone.
        self.check_selected();
    }

    // Same logic as probes_updated() for USB devices
    fn usb_devices_updated(&mut self) {
        // Check if selected USB device is still connected
        if let Some(old_device) = &self.selected_usb_device {
            if !self.usb_devices.contains(&old_device) {
                info!("Selected USB device has been disconnected: {old_device}");
                self.selected_usb_device = None;
            } else {
                trace!("Still connected to USB device {old_device}");
            }
        }

        // Next, if there isn't a selected USB device, see if there's one to
        // auto-select
        if self.selected_usb_device.is_none() {
            // If there is a USB device now, selecct it
            if let Some(usb_device) = self.usb_devices.first().cloned() {
                info!("Selected USB device: {usb_device}");
                self.selected_usb_device = Some(usb_device.clone());
            } else {
                trace!("No USB devices detected");
            }
        }

        // Finally, if there's no selected device, but there's a selected USB
        // device, select it.  This also clears the selected device if it has
        // gone
        self.check_selected();
    }

    // If a device is selected, make sure it still exists.  If there's no
    // device, select one if possible.
    fn check_selected(&mut self) {
        // See if the existing device is still valid
        let should_clear = match &self.selected {
            DeviceType::Usb(usb) => self.selected_usb_device.as_ref() != Some(usb),
            DeviceType::DebugProbe(probe) => self.selected_probe.as_ref() != Some(probe),
            DeviceType::None => false,
        };
        if should_clear {
            debug!("Clearing selected device as no longer valid");
            self.selected = DeviceType::None;
        }

        if self.selected.is_none() {
            // Prefer USB over debug probe
            if let Some(usb_device) = &self.selected_usb_device {
                self.selected = DeviceType::from_usb(usb_device.clone());
                info!("Auto-selected active device: {}", self.selected);
            } else if let Some(probe) = &self.selected_probe {
                self.selected = DeviceType::from_probe(probe.clone());
                info!("Auto-selected active device: {}", self.selected);
            } else {
                trace!("No device to auto-select");
            }
        }
    }

    // Methods called when device is selected
    fn select_device(&mut self, device: DeviceType) -> Task<AppMessage> {
        self.selected = device;
        self.check_selected();
        Task::none()
    }
    fn select_probe(&mut self, probe: ProbeType) -> Task<AppMessage> {
        self.selected_probe = Some(probe);
        self.check_selected();
        Task::none()
    }
    fn select_usb_device(&mut self, usb_device: UsbDeviceType) -> Task<AppMessage> {
        self.selected_usb_device = Some(usb_device);
        self.check_selected();
        Task::none()
    }

    // Methods for viewer to use to device how to populate pick lists
    fn has_detected_probes(&self) -> bool {
        !self.probes.is_empty()
    }
    fn has_detected_usb_devices(&self) -> bool {
        !self.usb_devices.is_empty()
    }

    /// Device view method - returns a Column directly so App can change
    /// control its width
    pub fn view<'a>(&'a self, style: &'a Style) -> Column<'a, AppMessage> {
        view::view(self, style)
    }

    /// Device help overlay
    pub fn help_overlay(&self) -> Element<'_, AppMessage> {
        view::help_overlay()
    }

    /// Device subscriptions
    pub fn subscription(&self) -> Subscription<Message> {
        Subscription::none()
    }
}

/// A type of a device.  Used to abstract between debug probe and USB
/// devices for read/flash operations.
#[derive(Debug, Default, Clone, PartialEq)]
pub enum DeviceType {
    /// None
    #[default]
    None,
    /// A device connected via a debug probe
    DebugProbe(ProbeType),
    /// A device connected via USB
    Usb(UsbDeviceType),
}

impl std::fmt::Display for DeviceType {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            DeviceType::DebugProbe(info) => write!(
                f,
                "{}, {}",
                info.identifier(),
                info.serial_number().unwrap_or("N/A")
            ),
            DeviceType::Usb(usb_type) => write!(f, "Usb({})", usb_type),
            DeviceType::None => write!(f, "None"),
        }
    }
}

impl DeviceType {
    fn probe(&self) -> Option<ProbeType> {
        if let DeviceType::DebugProbe(info) = self {
            Some(info.clone())
        } else {
            None
        }
    }

    fn usb_device(&self) -> Option<UsbDeviceType> {
        if let DeviceType::Usb(usb_type) = self {
            Some(usb_type.clone())
        } else {
            None
        }
    }

    pub fn is_none(&self) -> bool {
        matches!(self, DeviceType::None)
    }

    fn from_probe(info: ProbeType) -> Self {
        DeviceType::DebugProbe(info)
    }

    fn from_usb(usb_type: UsbDeviceType) -> Self {
        DeviceType::Usb(usb_type)
    }

    fn selected_message(&self) -> AppMessage {
        match self {
            DeviceType::DebugProbe(info) => Message::SelectProbe(info.clone()).into(),
            DeviceType::Usb(usb_type) => Message::SelectUsbDevice(usb_type.clone()).into(),
            DeviceType::None => unreachable!(),
        }
    }

    pub fn read(
        &self,
        client: Client,
        hw_info: HardwareInfo,
        address: Address,
        words: usize,
    ) -> Task<AppMessage> {
        Task::future(read_async(self.clone(), client, hw_info, address, words))
    }

    pub fn flash(&self, client: Client, hw_info: HardwareInfo, data: Vec<u8>) -> Task<AppMessage> {
        Task::future(flash_async(self.clone(), hw_info, client, data))
    }
}

// Generic read device method
async fn read_async(
    device: DeviceType,
    client: Client,
    hw_info: HardwareInfo,
    address: Address,
    words: usize,
) -> AppMessage {
    match device {
        DeviceType::DebugProbe(p) => {
            probe::read_async(p.clone(), client, hw_info, address, words).await
        }
        DeviceType::Usb(u) => usb::read_async(u.clone(), client, hw_info, address, words).await,
        DeviceType::None => {
            let log = "Attempted to read from None device";
            internal_error!("{log}");
            Message::ReadFailed(client, log.into()).into()
        }
    }
}

// Generic flash device method
async fn flash_async(
    device: DeviceType,
    hw_info: HardwareInfo,
    client: Client,
    data: Vec<u8>,
) -> AppMessage {
    match device {
        DeviceType::DebugProbe(p) => probe::flash_async(p.clone(), hw_info, client, data).await,
        DeviceType::Usb(u) => usb::flash_async(u.clone(), hw_info, client, data).await,
        DeviceType::None => {
            let log = "Attempted to flash None device";
            internal_error!("{log}");
            Message::ReadFailed(client, log.into()).into()
        }
    }
}
