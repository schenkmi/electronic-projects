// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! onerom-studio library

mod analyse;
pub mod app;
mod built;
mod config;
mod create;
mod device;
mod hw;
mod image;
pub mod log;
mod studio;
pub mod style;

pub use app::manifest::{Link as AppLink, ManifestType, PathType, Schema};
pub use app::manifest::{manifest_read as app_manifest, update_manifest as update_app_manifest};
pub use app::{App, AppMessage};

/// Helper macro to turn a message into a Task<AppMessage>.
/// This allows you to call task_from_msg!(any message type) or
/// task_from_msg!(Option<any message type>) or task_from_msg!(None)
/// and get a Task<AppMessage> back.
#[macro_export]
macro_rules! task_from_msg {
    ($msg:expr) => {
        match Into::<Option<AppMessage>>::into($msg) {
            Some(m) => iced::Task::done(m),
            None => iced::Task::none(),
        }
    };
}

/// Helper macro to turn messages into a Task<AppMessage>.
/// This allows you to call task_from_msgs! with:
/// - Vec<any message type>
/// - Vec<Option<any message type>> (filters out None values)
/// - Arrays like [msg1, msg2] where each can be a message or Option<message>
/// - Option<Vec<any message type>>
/// - None
/// and get a Task<AppMessage> back.
#[macro_export]
macro_rules! task_from_msgs {
    ($msgs:expr) => {
        match Into::<Option<_>>::into($msgs) {
            Some(ms) => {
                let tasks: Vec<_> = ms
                    .into_iter()
                    .filter_map(|m| Into::<Option<AppMessage>>::into(m))
                    .map(iced::Task::done)
                    .collect();
                if tasks.is_empty() {
                    iced::Task::none()
                } else {
                    iced::Task::batch(tasks)
                }
            }
            None => iced::Task::none(),
        }
    };
}
