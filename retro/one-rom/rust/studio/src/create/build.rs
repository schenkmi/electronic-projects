// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! Builds firmware images

use iced::Task;
#[allow(unused_imports)]
use log::{debug, error, info, trace, warn};

use crate::app::AppMessage;
use crate::create::{Create, State};
use crate::internal_error;
use crate::studio::{Message as StudioMessage, RuntimeInfo};

/// Kick off image build
pub fn build_image(create: &mut Create, runtime_info: &RuntimeInfo) -> Task<AppMessage> {
    debug!("Build image requested");

    if create.is_busy() {
        warn!("Busy - skipping build image");
        return Task::none();
    }

    if runtime_info.selected_config().is_none() {
        internal_error!("Build image requested with no selected config.");
        create.set_display_content("Unable to build image: no configuration selected.");
        return Task::none();
    }
    let selected = runtime_info.selected_config().unwrap();

    // Set state and content
    create.state = State::Building;
    create.set_display_content(format!("Building image: {} ...", selected.name()));

    // Send build image message to Studio
    Task::done(StudioMessage::BuildImage(create.selected_hw_info.clone()).into())
}

/// Handle the result of a build image operation
pub fn build_image_result(
    create: &mut Create,
    result: Result<String, String>,
    runtime_info: &RuntimeInfo,
) -> Task<AppMessage> {
    // Log the result
    debug!(
        "Build image result received: {}",
        if result.is_ok() { "OK" } else { "Error" }
    );

    // Ensure we were building
    if !create.is_building() {
        internal_error!("BuildImageResult received while not building.");
    }

    // Update state to idle
    create.state = State::Idle;

    match result {
        Ok(desc) => {
            create.display_content = format!(
                "Image built successfully, total: {} bytes ({}/{}/{} plus padding)\n\n{}\n ",
                runtime_info.built_full_image_len().unwrap_or(0),
                runtime_info.built_firmware_len().unwrap_or(0),
                runtime_info.built_metadata_len().unwrap_or(0),
                runtime_info.built_roms_len().unwrap_or(0),
                desc,
            );
        }
        Err(e) => {
            warn!("Error building : {e}");
            create.display_content = format!("Error building image:\n  - {e}");
        }
    }

    // Nothing to do
    Task::none()
}
