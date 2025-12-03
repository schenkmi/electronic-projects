// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! One ROM Studio - a GUI application for managing One ROMs

// Prevent console window on Windows in release builds using MSVC
#![cfg_attr(
    all(target_os = "windows", not(target_env = "gnu")),
    windows_subsystem = "windows"
)]

use onerom_studio::App;
use onerom_studio::app;
use onerom_studio::log;
use onerom_studio::style;

// Main - application entry point
fn main() -> iced::Result {
    // Initialize logging
    log::init_logging();

    // Run the application
    iced::application("One ROM Studio", App::update, App::view)
        .subscription(App::subscription)
        .window(window_settings())
        .font(style::font_michroma_bytes())
        .font(style::font_courier_reg_bytes())
        .default_font(style::Style::FONT_MICHROMA)
        .theme(|_| style::ICED_THEME)
        .run_with(|| (App::new(), app::startup_task()))
}

// Create the window settings
fn window_settings() -> iced::window::Settings {
    // Create the window settings
    iced::window::Settings {
        size: iced::Size {
            width: 900.0,
            height: 850.0,
        },
        min_size: Some(iced::Size {
            width: 900.0,
            height: 850.0,
        }),
        max_size: None,
        resizable: true,
        decorations: true,
        transparent: false,
        icon: Some(style::icon()),
        position: iced::window::Position::Centered,
        visible: true,
        level: iced::window::Level::Normal,
        exit_on_close_request: true,
        ..Default::default()
    }
}
