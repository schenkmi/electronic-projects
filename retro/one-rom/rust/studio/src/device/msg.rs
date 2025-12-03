// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! Contains Device Message handling

use iced::task::Task;
#[allow(unused_imports)]
use log::{debug, error, info, trace, warn};
use std::time::Duration;

use crate::analyse::Message as AnalyseMessage;
use crate::app::AppMessage;
use crate::create::Message as CreateMessage;
use crate::device::probe::ProbeType;
use crate::device::usb::UsbDeviceType;
use crate::device::{Address, Client, Device, DeviceType};
use crate::hw::HardwareInfo;
use crate::internal_error;
use crate::studio::RuntimeInfo;

/// Device messages
#[derive(Debug, Clone)]
pub enum Message {
    // Rescan for all device types
    Rescan,

    // Detect probe or USB devices
    DetectProbes,
    DetectUsbDevices,

    // Probes or USB devices detected
    ProbesDetected(Vec<ProbeType>),
    UsbDevicesDetected(Vec<UsbDeviceType>),

    // Overall device, probe or USB device selected
    SelectDevice(DeviceType),
    SelectProbe(ProbeType),
    SelectUsbDevice(UsbDeviceType),

    // Flash firmware to a device
    FlashFirmware {
        client: Client,
        hw_info: HardwareInfo,
        data: Vec<u8>,
    },
    FlashFirmwareResult(Client, Result<(), String>),

    // Read data from a device
    ReadDevice {
        client: Client,
        hw_info: HardwareInfo,
        address: Address,
        words: usize,
    },
    DeviceData(Client, Vec<u8>),
    ReadFailed(Client, String),
}

impl std::fmt::Display for Message {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Message::DetectProbes => write!(f, "DetectProbes"),
            Message::ProbesDetected(probes) => {
                let probes_str = probes
                    .iter()
                    .map(|p| p.identifier())
                    .collect::<Vec<_>>()
                    .join(", ");
                write!(f, "ProbesDetected({probes_str})")
            }
            Message::SelectDevice(device) => write!(f, "SelectDevice({})", device),
            Message::SelectProbe(probe) => write!(f, "SelectProbe({})", probe),
            Message::SelectUsbDevice(usb_device) => write!(f, "SelectUsbDevice({})", usb_device),
            Message::ReadDevice {
                client,
                hw_info,
                address,
                words,
            } => {
                write!(
                    f,
                    "ReadDevice(client={client}, hw_info={hw_info}, address={address}, words={words})",
                )
            }
            Message::DetectUsbDevices => write!(f, "DetectUsbDevices"),
            Message::UsbDevicesDetected(devices) => {
                let devices_str = devices
                    .iter()
                    .map(|d| {
                        format!(
                            "VID={:04X}, PID={:04X}",
                            d.vid(),
                            d.pid()
                        )
                    })
                    .collect::<Vec<_>>()
                    .join(", ");
                write!(f, "UsbDevicesDetected({})", devices_str)
            }
            Message::FlashFirmware {
                client,
                hw_info,
                data,
            } => {
                write!(
                    f,
                    "FlashFirmware(client={client}, hw_info={hw_info}, data_len={})",
                    data.len()
                )
            }
            Message::FlashFirmwareResult(client, result) => match result {
                Ok(()) => write!(f, "FlashFirmwareResult(client={client}, Ok)"),
                Err(e) => write!(f, "FlashFirmwareResult(client={client}, Err: {})", e),
            },
            Message::DeviceData(client, data) => {
                write!(f, "DeviceData(client={client}, {} bytes)", data.len())
            }
            Message::ReadFailed(client, error) => {
                write!(f, "ReadFailed(client={client}, {})", error)
            }
            Message::Rescan => write!(f, "Rescan"),
        }
    }
}

// Top-level Device Message handling routine
pub fn handle_message(
    device: &mut Device,
    _runtime_info: &RuntimeInfo,
    message: Message,
) -> Task<AppMessage> {
    match message {
        // Rescan all device types
        Message::Rescan => {
            if device.is_idle() {
                Task::batch([
                    Task::done(Message::DetectUsbDevices.into()),
                    Task::done(Message::DetectProbes.into()),
                ])
            } else {
                trace!("Skipping device rescan while operating");
                Task::none()
            }
        }

        // Detect a list of probes or USB devices
        Message::DetectProbes => {
            if device.is_idle() {
                Task::future(crate::device::probe::get_probe_list_async())
            } else {
                trace!("Skipping probe detection while operating");
                Task::none()
            }
        }
        Message::DetectUsbDevices => {
            if device.is_idle() {
                Task::future(crate::device::usb::get_usb_device_list_async())
            } else {
                trace!("Skipping USB device detection while operating");
                Task::none()
            }
        }

        // A list of probes or USB devices has been detected
        Message::ProbesDetected(probes) => {
            device.probes = probes;
            device.probes_updated();
            Task::none()
        }
        Message::UsbDevicesDetected(devices) => {
            device.usb_devices = devices;
            device.usb_devices_updated();
            Task::none()
        }

        // The overall device, a probe or USB device has been selected
        Message::SelectDevice(dev) => {
            debug!("Selecting device: {}", dev);
            device.select_device(dev)
        }
        Message::SelectProbe(probe) => {
            debug!("Selecting probe: {}", probe);
            device.select_probe(probe)
        }
        Message::SelectUsbDevice(usb_device) => {
            debug!("Selecting USB device: {}", usb_device);
            device.select_usb_device(usb_device)
        }

        // Flash firmware request and result
        Message::FlashFirmware {
            client,
            hw_info,
            data,
        } => {
            debug!("{client} Flashing firmware");
            device.operating = Some(client.clone());
            device.selected.flash(client, hw_info, data)
        }
        Message::FlashFirmwareResult(client, result) => {
            debug!(
                "{client} Firmware flash complete: {}",
                if result.is_ok() { "OK" } else { "Error" }
            );
            // Force a device re-enumeration after flashing firmware
            device.operating = None;
            let msg = match client {
                Client::Analyse => AnalyseMessage::FlashComplete(result).into(),
                Client::Create => CreateMessage::FlashFirmwareResult(result).into(),
            };
            // Pause briefly before re-enumeration to allow the device to reset
            // and then send the done message
            Task::done(msg).chain(Task::future(crate::device::usb::get_usb_device_list_delay(
                Duration::from_millis(1000),
            )))
        }

        // Read device request and results
        Message::ReadDevice {
            client,
            hw_info,
            address,
            words,
        } => {
            debug!(
                "{client} Reading device memory at {address}, {words} words",
            );
            if client != Client::Analyse {
                internal_error!("Device read requested by unsupported client: {}", client);
                return Task::none();
            }
            device.operating = Some(client.clone());
            device.selected.read(client, hw_info, address, words)
        }
        Message::DeviceData(client, data) => {
            debug!("{client} Received device data: {} bytes", data.len());
            assert_eq!(client, Client::Analyse);
            device.operating = None;
            Task::done(AnalyseMessage::DeviceData(data).into())
        }
        Message::ReadFailed(client, error) => {
            debug!("{client} Device read failed: {}", error);
            assert_eq!(client, Client::Analyse);
            device.operating = None;
            Task::done(AnalyseMessage::ReadFailed(error).into())
        }
    }
}
