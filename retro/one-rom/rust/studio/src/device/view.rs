// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! Device view methods
//!
//! Device gets the top right corner of the app, with probe and USB device
//! pick lists and buttons - and a help icon.

use iced::alignment::Alignment::Center;
use iced::alignment::Horizontal;
use iced::widget::{Button, Column, Space, column, container, row};
use iced::{Element, Length};
#[allow(unused_imports)]
use log::{debug, error, info, trace, warn};

use crate::device::probe::ProbeType;
use crate::device::usb::UsbDeviceType;
use crate::device::{Device, DeviceType, Message};
use crate::style::Style;
use crate::{AppLink, AppMessage};

/// Create the device view (top right of the app)
pub fn view<'a>(device: &'a Device, style: &'a Style) -> Column<'a, AppMessage> {
    // Create the left hand column - labels for pick lists and buttons
    let left_col = left_column(device, style);

    // Create the right hand column, the pick lists and buttons
    let right_col = right_column(device, style);

    // Create the row for everything
    let single_row = row![
        left_col.width(Length::FillPortion(1)),
        right_col.width(Length::FillPortion(5))
    ]
    .spacing(10)
    .align_y(Center);

    // Turn it into a column, as that is what App wants
    column![single_row,]
        .spacing(20)
        .width(Length::Fill)
        .align_x(Horizontal::Center)
}

fn left_column<'a>(_device: &'a Device, _style: &'a Style) -> Column<'a, AppMessage> {
    column![
        container(Style::text_small("Probe:"))
            .height(Length::Fixed(25.0))
            .align_y(Center),
        container(Style::text_small("USB:"))
            .height(Length::Fixed(25.0))
            .align_y(Center),
        container(Style::text_small("Use:"))
            .height(Length::Fixed(30.0))
            .align_y(Center),
    ]
    .spacing(10)
    .align_x(Horizontal::Right)
}

fn right_column<'a>(device: &'a Device, style: &'a Style) -> Column<'a, AppMessage> {
    // Create the probe and USB pick lists
    let probe_list = probe_pick_list(device);
    let usb_device_list = usb_device_pick_list(device);

    // Create the buttons
    let probe_button = probe_button(device);
    let usb_button = usb_button(device);
    let rescan_button = rescan_button(device);
    let help_icon = style.help_icon("Device Help");

    // Create the button row
    let button_row = button_row(vec![probe_button, usb_button, rescan_button], help_icon);

    column![probe_list, usb_device_list, button_row,].spacing(10)
}

fn button_row<'a>(
    buttons: Vec<Button<'a, AppMessage>>,
    help_icon: Element<'a, AppMessage>,
) -> Element<'a, AppMessage> {
    let mut row = row![];
    for button in buttons {
        row = row.push(button);
    }
    row = row
        .push(Space::with_width(Length::Fill))
        .push(help_icon)
        .spacing(10)
        .align_y(Center);

    container(row)
        .height(Length::Fixed(30.0))
        .align_y(Center)
        .into()
}

/// Create the Probe pick list
fn probe_pick_list(device: &Device) -> Element<'static, AppMessage> {
    let probe_list: Element<'_, AppMessage> = if device.has_detected_probes() {
        let options = device.probes.clone();
        let msg = if device.is_busy() {
            |_| AppMessage::Nop // Ignore picklist selection while busy
        } else {
            |p: ProbeType| Message::SelectProbe(p.clone()).into()
        };
        Style::pick_list_small(options, device.selected_probe.clone(), msg).into()
    } else {
        Style::text_body("Not detected")
            .color(Style::COLOUR_DARK_GOLD)
            .into()
    };

    container(probe_list)
        .height(Length::Fixed(25.0))
        .align_y(Center)
        .into()
}

fn usb_device_pick_list(device: &Device) -> Element<'_, AppMessage> {
    // Create the USB device pick list
    let msg = if device.is_busy() {
        |_| AppMessage::Nop // Ignore picklist selection while busy
    } else {
        |d: UsbDeviceType| DeviceType::from_usb(d.clone()).selected_message()
    };
    let usb_device_list: Element<'_, AppMessage> = if device.has_detected_usb_devices() {
        let options = device.usb_devices.as_slice();
        Style::pick_list_small(options, device.selected_usb_device.clone(), msg).into()
    } else {
        Style::text_body("Not detected")
            .color(Style::COLOUR_DARK_GOLD)
            .into()
    };
    container(usb_device_list)
        .height(Length::Fixed(25.0))
        .align_y(Center)
        .into()
}

fn probe_button<'a>(device: &'a Device) -> Button<'a, AppMessage> {
    let highlight_probe_button = device.selected().probe().is_some();
    let on_press_probe = if device.is_idle()
        && device.selected().probe().is_none()
        && device.selected_probe.is_some()
    {
        Some(
            Message::SelectDevice(DeviceType::from_probe(
                device.selected_probe.as_ref().unwrap().clone(),
            ))
            .into(),
        )
    } else {
        None
    };

    Style::text_button_small("Probe", on_press_probe, highlight_probe_button)
}

fn usb_button<'a>(device: &'a Device) -> Button<'a, AppMessage> {
    let highlight_usb_button = device.selected().usb_device().is_some();
    let on_press_usb = if device.is_idle()
        && device.selected().usb_device().is_none()
        && device.selected_usb_device.is_some()
    {
        Some(
            Message::SelectDevice(DeviceType::from_usb(
                device.selected_usb_device.as_ref().unwrap().clone(),
            ))
            .into(),
        )
    } else {
        None
    };

    Style::text_button_small("USB", on_press_usb, highlight_usb_button)
}

fn rescan_button<'a>(device: &'a Device) -> Button<'a, AppMessage> {
    let highlight_rescan_button = !device.is_busy();
    let on_press_rescan = if !device.is_busy() {
        Some(Message::Rescan.into())
    } else {
        None
    };

    Style::text_button_small("Rescan", on_press_rescan, highlight_rescan_button)
}

/// Create the device help overlay
pub fn help_overlay() -> Element<'static, AppMessage> {
    let main_content = if cfg!(target_os = "windows") {
        help_content_win()
    } else if cfg!(target_os = "linux") {
        help_content_linux()
    } else if cfg!(target_os = "macos") {
        help_content_macos()
    } else {
        Style::text_body("No device help available for this platform").into()
    };

    let exit_button = row![Style::text_button(
        "Exit",
        Some(AppMessage::Help(false)),
        true
    ),];

    column![
        Style::text_h2("Device Help").align_x(Horizontal::Center),
        Style::horiz_line(),
        main_content,
        exit_button,
    ]
    .align_x(Horizontal::Center)
    .spacing(20)
    .into()
}

fn help_content_linux() -> Element<'static, AppMessage> {
    let help_row_1 = row![
        Style::text_body(
            "When installing from the official One ROM Studio .deb package, udev rules should be automatically set up to allow One ROM Studio to access debug probes and One ROM USB devices."
        ),
        Space::with_width(Length::Fill),
    ];
    let help_row_2 = row![
        Style::text_body(
            "If you have compiled One ROM Studio from source, or are using a different distribution method, you may need to set up udev rules manually."
        ),
        Space::with_width(Length::Fill),
    ];
    let help_row_3 = row![
        Style::text_body("See "),
        Style::link("here", Style::FONT_SIZE_BODY, AppLink::LinuxUdev),
        Style::text_body(" for instructions."),
        Space::with_width(Length::Fill),
    ];
    let help_row_4 = row![
        Style::text_body(
            "Also try reconnecting the device, restarting One ROM Studio, and rebooting your machine."
        ),
        Space::with_width(Length::Fill),
    ];
    column![help_row_1, help_row_2, help_row_3, help_row_4,]
        .spacing(20)
        .align_x(Horizontal::Center)
        .into()
}

fn help_content_macos() -> Element<'static, AppMessage> {
    let help_row_1 = row![
        Style::text_body(
            "There is no special USB device setup required on macOS to allow One ROM Studio to access your devices.  However, when plugging in devices you may need to choose 'Allow' so that your Mac can access them."
        ),
        Space::with_width(Length::Fill),
    ];
    let help_row_2 = row![
        Style::text_body(
            "If One ROM does detect a connected device, try reconnecting it, restarting One ROM Studio, and rebooting your Mac."
        ),
        Space::with_width(Length::Fill),
    ];
    let help_row_3 = row![
        Style::text_body("If problems persist, please raise a "),
        Style::link("GitHub issue", Style::FONT_SIZE_BODY, AppLink::GitHubIssue),
        Style::text_body("."),
        Space::with_width(Length::Fill),
    ];
    column![help_row_1, help_row_2, help_row_3,]
        .spacing(20)
        .align_x(Horizontal::Center)
        .into()
}

fn help_content_win() -> Element<'static, AppMessage> {
    let help_row_1 = row![
        Style::text_body(
            "If you have plugged in a One ROM USB and it has not been detected, you may need to install the WinUSB driver for it."
        ),
        Space::with_width(Length::Fill),
    ];
    let help_row_2 = row![
        Style::text_body("See "),
        Style::link("here", Style::FONT_SIZE_BODY, AppLink::WinUsb),
        Style::text_body(" for instructions."),
        Space::with_width(Length::Fill),
    ];
    let help_row_3 = row![
        Style::text_body(
            "Generic debug probes should be automatically detected when plugged in, although specific probes may need a custom driver."
        ),
        Space::with_width(Length::Fill),
    ];
    let help_row_4 = row![
        Style::text_body(
            "Try reconnecting the device, restarting One ROM Studio, and rebooting your PC."
        ),
        Space::with_width(Length::Fill),
    ];
    let help_row_5 = row![
        Style::text_body("If problems persist, please raise a "),
        Style::link("GitHub issue", Style::FONT_SIZE_BODY, AppLink::GitHubIssue),
        Style::text_body("."),
        Space::with_width(Length::Fill),
    ];
    column![help_row_1, help_row_2, help_row_3, help_row_4, help_row_5,]
        .spacing(20)
        .align_x(Horizontal::Center)
        .into()
}
