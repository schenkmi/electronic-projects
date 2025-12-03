// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! Create Message handling

use iced::Task;
#[allow(unused_imports)]
use log::{debug, error, info, trace, warn};
use std::path::PathBuf;

use onerom_config::hw::{Board, Model};
use onerom_config::mcu::Variant as McuVariant;
use onerom_fw::net::Release;

use crate::app::AppMessage;
use crate::config::Config;
use crate::create::Create;
use crate::create::build::{build_image, build_image_result};
use crate::create::file::{
    config_loaded, config_selected, save_firmware, save_firmware_complete, save_firmware_filename,
};
use crate::create::hw::{
    detect_hardware, detected_hardware_info, flash_firmware, flash_firmware_result,
};
use crate::studio::RuntimeInfo;
use crate::task_from_msg;

/// Create Messages
#[derive(Debug, Clone)]
pub enum Message {
    // Hardware and firmware release picklist values changed
    BoardSelected(Board),
    ModelSelected(Model),
    McuSelected(McuVariant),
    ReleaseSelected(Release),
    ReleaseDowloaded(Result<(), String>),

    // Detect hardware button operation.
    // Information can be detected via connected device using Analyse tab
    DetectHardware,
    DetectedHardwareInfo,

    // Releases and configs have been updated (from network)
    ReleasesUpdated,
    ConfigsUpdated,

    // ROM config has been selected via pick list
    ConfigSelected(Config),
    ConfigLoaded(Result<(), String>),

    // Build image
    BuildImage,
    BuildImageResult(Result<String, String>),

    // Save the firmware image as a file.
    // - SaveFirmware - save button pressed
    // - SaveFirmwareFilename(Option<PathBuf>) - filename selected (or
    //   cancelled)
    // - SaveFirmwareComplete - save operation complete
    SaveFirmware,
    SaveFirmwareFilename(Option<PathBuf>),
    SaveFirmwareComplete,

    // Flash firmware
    FlashFirmware,
    FlashFirmwareResult(Result<(), String>),

    // Progress tick from subscription during operation
    ProgressTick,
}

// Main Create Message handling function
pub fn message(create: &mut Create, runtime_info: &RuntimeInfo, msg: Message) -> Task<AppMessage> {
    match msg {
        // Hardware and firmware release picklist values changed
        Message::ModelSelected(model) => {
            debug!("Model selected: {}", model.name());
            create.model_selected(model);
            Task::none()
        }
        Message::BoardSelected(board) => {
            debug!("Board selected: {}", board.name());
            task_from_msg!(create.board_selected(runtime_info, board))
        }
        Message::McuSelected(mcu) => {
            debug!("MCU selected: {}", mcu);
            create.mcu_selected(mcu);
            task_from_msg!(create.select_latest_release(runtime_info.releases()))
        }
        Message::ReleaseSelected(release) => {
            debug!("Firmware release selected: {}", release.version);
            task_from_msg!(create.select_release(release))
        }
        Message::ReleaseDowloaded(result) => {
            debug!("Firmware release downloaded");
            match result {
                Ok(()) => debug!("Release download succeeded"),
                Err(e) => warn!("Release download failed: {e}"),
            }
            Task::none()
        }

        // Detect hardware button operation.
        Message::DetectHardware => detect_hardware(create),
        Message::DetectedHardwareInfo => detected_hardware_info(create, runtime_info),

        // Releases and configs have been updated (from network)
        Message::ReleasesUpdated => {
            let releases = runtime_info.releases();

            // Select the latest firmware, unless one is already selected
            if create.hardware_selected() && runtime_info.selected_firmware().is_none() {
                task_from_msg!(create.select_latest_release(releases))
            } else {
                Task::none()
            }
        }
        Message::ConfigsUpdated => Task::none(),

        // ROM config has been selected via pick list
        Message::ConfigSelected(config) => config_selected(create, config),
        Message::ConfigLoaded(result) => config_loaded(create, runtime_info, result),

        // Build image
        Message::BuildImage => build_image(create, runtime_info),
        Message::BuildImageResult(result) => build_image_result(create, result, runtime_info),

        // Save the firmware image as a file.
        Message::SaveFirmware => save_firmware(create, runtime_info),
        Message::SaveFirmwareFilename(filename) => {
            save_firmware_filename(create, runtime_info, filename)
        }
        Message::SaveFirmwareComplete => save_firmware_complete(create),

        // Flash firmware
        Message::FlashFirmware => flash_firmware(create, runtime_info),
        Message::FlashFirmwareResult(result) => flash_firmware_result(create, result),

        // Progress tick from subscription during operation
        Message::ProgressTick => {
            create.progress_tick();
            Task::none()
        }
    }
}

impl std::fmt::Display for Message {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Message::BoardSelected(board) => write!(f, "BoardSelected({})", board.name()),
            Message::ModelSelected(model) => write!(f, "ModelSelected({})", model.name()),
            Message::McuSelected(mcu) => write!(f, "McuSelected({mcu})"),
            Message::ReleaseSelected(release) => {
                write!(f, "ReleaseSelected({})", release.version)
            }
            Message::ReleaseDowloaded(result) => match result {
                Ok(()) => write!(f, "ReleaseDowloaded(Ok)"),
                Err(e) => write!(f, "ReleaseDowloaded(Err({e}))"),
            },

            Message::DetectHardware => write!(f, "DetectHardware"),
            Message::DetectedHardwareInfo => write!(f, "DetectedHardwareInfo"),

            Message::ReleasesUpdated => write!(f, "ReleasesUpdated"),
            Message::ConfigsUpdated => write!(f, "ConfigsUpdated"),

            Message::ConfigSelected(name) => write!(f, "ConfigSelected({})", name),
            Message::ConfigLoaded(result) => match result {
                Ok(()) => write!(f, "ConfigLoaded(Ok)"),
                Err(e) => write!(f, "ConfigLoaded(Err({e}))"),
            },

            Message::BuildImage => write!(f, "BuildImage"),
            Message::BuildImageResult(result) => {
                write!(f, "BuildImageResult({:?})", result)
            }

            Message::SaveFirmware => write!(f, "SaveFirmware"),
            Message::SaveFirmwareFilename(filename) => {
                write!(f, "SaveFirmwareFilename({:?})", filename)
            }
            Message::SaveFirmwareComplete => write!(f, "SaveFirmwareComplete"),

            Message::FlashFirmware => write!(f, "FlashFirmware"),
            Message::FlashFirmwareResult(result) => {
                write!(f, "FlashFirmwareResult({:?})", result)
            }

            Message::ProgressTick => write!(f, "ProgressTick"),
        }
    }
}
