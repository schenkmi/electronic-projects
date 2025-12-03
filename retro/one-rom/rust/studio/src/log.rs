// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! Logging functionality for the application.
//!
//! Integrated with the `log` crate to capture log messages.
//!
//! Sets up a global logger that captures log messages and sends them to
//! the application's log view.

use chrono::{DateTime, Local};
use iced::futures::channel::mpsc::{Sender, channel as mpsc_channel};
use iced::futures::{SinkExt, StreamExt};
use iced::stream::channel;
use iced::widget::{Column, Space, column, row};
use iced::{Element, Subscription, Task, clipboard};
#[allow(unused_imports)]
use log::{debug, error, info, trace, warn};
use std::env;
use std::sync::{Mutex, OnceLock};
use std::time::SystemTime;

use crate::app::AppMessage;
use crate::studio::RuntimeInfo;
use crate::style::Style;

// Global log sender for logging from anywhere
static LOG_SENDER: OnceLock<Mutex<Sender<LogEntry>>> = OnceLock::new();

// Default maximum number of log entries to keep
const DEFAULT_LOG_ENTRIES: usize = 1024;

// Maximum channel size for log messages
const MAX_CHANNEL_SIZE: usize = 1024;

/// Log config
#[derive(Debug, Clone)]
pub struct Config {
    /// Max number of log entries to keep
    max_entries: usize,

    /// Minimum log level to record
    max_level: Level,
}

impl Default for Config {
    fn default() -> Self {
        Self {
            max_entries: DEFAULT_LOG_ENTRIES,
            max_level: Level::default(),
        }
    }
}

/// Log levels
#[derive(Debug, Default, Clone, Copy, PartialEq, Eq, PartialOrd, Ord)]
#[allow(dead_code)]
pub enum Level {
    /// Trace log entry
    Trace,
    /// Debug log entry
    Debug,
    /// Informational log entry
    #[default]
    Info,
    /// Warning log entry
    Warning,
    /// Error log entry
    Error,
}

// All log levels, for a pick list
const LOG_LEVELS: [Level; 5] = [
    Level::Trace,
    Level::Debug,
    Level::Info,
    Level::Warning,
    Level::Error,
];

// Conversion from log::Level to our Level
impl From<log::Level> for Level {
    fn from(level: log::Level) -> Self {
        match level {
            log::Level::Trace => Level::Trace,
            log::Level::Debug => Level::Debug,
            log::Level::Info => Level::Info,
            log::Level::Warn => Level::Warning,
            log::Level::Error => Level::Error,
        }
    }
}

// Conversion from our Level to log::LevelFilter
impl Into<log::LevelFilter> for Level {
    fn into(self) -> log::LevelFilter {
        match self {
            Level::Trace => log::LevelFilter::Trace,
            Level::Debug => log::LevelFilter::Debug,
            Level::Info => log::LevelFilter::Info,
            Level::Warning => log::LevelFilter::Warn,
            Level::Error => log::LevelFilter::Error,
        }
    }
}

impl Level {
    // Get the string representation of the log level.  Used in the actual log
    const fn as_str(&self) -> &'static str {
        match self {
            Level::Trace => "TRACE",
            Level::Debug => "DEBUG",
            Level::Info => "INFO",
            Level::Warning => "WARN",
            Level::Error => "ERROR",
        }
    }

    // Get the colour associated with the log level.  Used in the actual log
    const fn colour(&self) -> iced::Color {
        match self {
            Level::Trace => Style::COLOUR_TRACE,
            Level::Debug => Style::COLOUR_DEBUG,
            Level::Info => Style::COLOUR_INFO,
            Level::Warning => Style::COLOUR_WARN,
            Level::Error => Style::COLOUR_ERROR,
        }
    }
}

impl std::fmt::Display for Level {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Level::Trace => write!(f, "Trace"),
            Level::Debug => write!(f, "Debug"),
            Level::Info => write!(f, "Info"),
            Level::Warning => write!(f, "Warning"),
            Level::Error => write!(f, "Error"),
        }
    }
}

/// Log Messages - used by the application to interact with Log
#[derive(Debug, Clone)]
pub enum Message {
    /// Add a log entry
    AddEntry(LogEntry),

    /// Set the maximum log level
    MaxLogLevel(Level),

    /// Copy all logs to clipboard
    CopyToClipboard,

    /// Clear all logs
    ClearLogs,
}

impl std::fmt::Display for Message {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Message::AddEntry(_) => write!(f, "AddEntry"),
            Message::MaxLogLevel(level) => write!(f, "MinLogLevel({level})"),
            Message::CopyToClipboard => write!(f, "CopyToClipboard"),
            Message::ClearLogs => write!(f, "ClearLogs"),
        }
    }
}

/// Log entry
///
/// Used within a Message::AddEntry to add a log entry to the log.  Rarely
/// constructed outside of the `log`` module - users should prefer logging
/// macros
#[derive(Debug, Clone)]
pub struct LogEntry {
    level: Level,
    timestamp: SystemTime,
    text: String,
}

impl LogEntry {
    /// Create a new log entry
    pub fn new(level: Level, text: String) -> Self {
        Self {
            level,
            timestamp: SystemTime::now(),
            text,
        }
    }

    // Get the log entry as a row to display
    fn as_row(&self) -> Element<'_, AppMessage> {
        // Get the log type as a string, fixed width for alignment
        let level_str = format!("{:05}", self.level.as_str());

        // Create a "[LEVEL]" row, with LEVEL coloured appropriately
        let level = row![
            Style::text_trace("[", Style::COLOUR_TEXT),
            Style::text_trace(level_str, self.level.colour()),
            Style::text_trace("]", Style::COLOUR_TEXT),
        ];

        // Create a full log row with level, timestamp and text.  If the text
        // wraps, it will wrap under the text, not the level or timestamp.
        row![
            level,
            Style::text_trace(format!("[{}]", self.time_as_str()), Style::COLOUR_TEXT),
            Style::text_trace(&self.text, Style::COLOUR_TEXT),
        ]
        .spacing(5)
        .into()
    }

    // Get the time and date as desired format string
    fn time_and_date_as_str(&self) -> String {
        DateTime::<Local>::from(self.timestamp)
            .format("%Y-%m-%d %H:%M:%S")
            .to_string()
    }

    // Get the time as desired format string
    fn time_as_str(&self) -> String {
        DateTime::<Local>::from(self.timestamp)
            .format("%H:%M:%S")
            .to_string()
    }

    // Return the log entry as a string suitable for copying to clipboard.
    // Note this returns the full date and time, whereas within the app we
    // only display the time for brevity.
    fn to_clipboard(&self) -> String {
        format!(
            "[{:05}] [{}] {}\n",
            self.level.as_str(),
            self.time_and_date_as_str(),
            self.text
        )
    }
}

/// Log state
#[derive(Debug, Clone)]
pub struct Log {
    // Log configuration
    config: Config,

    // Stored log entries as a list, from oldest to newest
    entries: Vec<LogEntry>,
}

impl Log {
    /// Get the name of the top level button to display in the app
    pub const fn top_level_button_name() -> &'static str {
        "Logs"
    }

    /// Create the Log instance
    pub fn new() -> Self {
        Self {
            config: Config::default(),
            entries: Vec::new(),
        }
    }

    /// Log Message handler
    pub fn update(&mut self, _runtime_info: &RuntimeInfo, message: Message) -> Task<AppMessage> {
        match message {
            Message::AddEntry(log_entry) => {
                self.add_entry(log_entry);
                Task::none()
            }
            Message::MaxLogLevel(level) => {
                debug!("Max log level changed: {}", level);
                self.config.max_level = level;
                log::set_max_level(level.into());
                Task::none()
            }
            Message::CopyToClipboard => {
                debug!("Copy logs to clipboard");
                self.copy_to_clipboard()
            }
            Message::ClearLogs => {
                debug!("Clear logs");
                self.entries.clear();
                Task::none()
            }
        }
    }

    // Copy all visible logs (i.e. not those filtered out) to the clipboard
    fn copy_to_clipboard(&self) -> Task<AppMessage> {
        let mut all_logs = String::new();
        for entry in self.get_visible_logs() {
            let line = entry.to_clipboard();
            all_logs.push_str(&line);
        }
        clipboard::write(all_logs)
    }

    // Add a log entry, throwing away any excess entries, oldest first
    fn add_entry(&mut self, log_entry: LogEntry) {
        // Check if the log level is sufficient
        if log_entry.level < self.config.max_level {
            return;
        }

        // Add the log entry
        self.entries.push(log_entry);

        // Trim the log entries if necessary
        self.trim_entries();
    }

    // Throw away oldest log entries if we have exceeded the max entries
    fn trim_entries(&mut self) {
        if self.entries.len() > self.config.max_entries {
            let to_drain = self.entries.len() - self.config.max_entries;
            self.entries.drain(0..to_drain);
        }
    }

    // Create the options row in the app for the log view
    fn options_row(&self) -> Element<'_, AppMessage> {
        // Minimum log level pick list
        let min_log_level = row![
            Style::text_small("Max Log Level:",),
            Style::pick_list_small(LOG_LEVELS, Some(self.config.max_level), |level| {
                AppMessage::Log(Message::MaxLogLevel(level))
            },)
        ]
        .spacing(10)
        .align_y(iced::Alignment::Center);

        // Create the clear and copy buttons
        let clear_logs = Style::text_button_small("Clear", Some(Message::ClearLogs.into()), true);
        let copy_to_clipbard =
            Style::text_button_small("Copy", Some(Message::CopyToClipboard.into()), true);

        // Combine pick list and buttons into a row
        row![
            min_log_level,
            Space::with_width(iced::Length::Fill),
            clear_logs,
            copy_to_clipbard,
        ]
        .spacing(20)
        .align_y(iced::Alignment::Center)
        .into()
    }

    // Get the log entries that are above the configured log level
    fn get_visible_logs(&self) -> Vec<&LogEntry> {
        self.entries
            .iter()
            .filter(|e| e.level >= self.config.max_level)
            .collect()
    }

    // Create the logs container element, which holds the actual log entries
    fn logs_container(&self) -> Element<'_, AppMessage> {
        // Turn log entries in a vec of rows, the into a column, then into a
        // scroll box, within a container (box).  Need to only include logs
        // that are above the configured level - as logs may have been added
        // before the level change.
        let logs = self
            .get_visible_logs()
            .iter()
            .map(|e| e.as_row())
            .collect::<Vec<_>>();
        let column = Column::with_children(logs);
        let scrollable = Style::box_scrollable_element(column, 463.0, false).anchor_bottom();
        Style::container(scrollable).into()
    }

    /// Create the view for the log tab.  Called from the app view when the
    /// Log tab is selected.
    pub fn view(&self, _runtime_info: &RuntimeInfo) -> Element<'_, AppMessage> {
        column![self.options_row(), self.logs_container(),]
            .spacing(20)
            .into()
    }

    /// Create the subscription for the log tab.  This sets up the chanel that
    /// the global logger uses to send log entries to the app.
    pub fn subscription(&self) -> Subscription<AppMessage> {
        Subscription::run(|| channel(100, log_channel))
    }

    /// Check if any serious errors (warnings or errors) have occurred.  This
    /// is used to highlight the log button red if so.
    pub fn serious_errors_occurred(&self) -> bool {
        self.entries.iter().any(|e| e.level >= Level::Error)
    }
}

/// Global logger implementation
struct Logger;

impl log::Log for Logger {
    // Check if the log record should be logged
    fn enabled(&self, metadata: &log::Metadata) -> bool {
        // When using the crate name we have to turn - into _ as the latter is
        // what we get called with
        let crate_name = env!("CARGO_CRATE_NAME").replace("-", "_");
        metadata.target().starts_with(&crate_name)
            || metadata.target().starts_with("dfu")
            || metadata.target().starts_with("picoboot")
    }

    // Log the record by sending it to the log channel
    fn log(&self, record: &log::Record) {
        // Check if we should log this record
        if !self.enabled(record.metadata()) {
            return;
        }

        // Print out the log when on Windows/GNU (dev platform)
        #[cfg(all(target_os = "windows", target_env = "gnu"))]
        println!("[{:05}] {}", record.level().as_str(), record.args());

        // Send the log entry to the channel
        if let Some(sender) = LOG_SENDER.get() {
            let entry = LogEntry::new(record.level().into(), format!("{}", record.args()));
            let _ = sender.lock().unwrap().try_send(entry);
        }
    }

    // Flush the logger (no-op for us)
    fn flush(&self) {}
}

// Log channel task.  Listens for log entries and sends them to the app as
// messages.
async fn log_channel(mut sender: Sender<AppMessage>) {
    let (tx, mut rx) = mpsc_channel(MAX_CHANNEL_SIZE);
    let _ = LOG_SENDER.set(Mutex::new(tx));

    while let Some(log_entry) = rx.next().await {
        let _ = sender.send(Message::AddEntry(log_entry).into()).await;
    }
}

/// Initialize the global logger
pub fn init_logging() {
    log::set_logger(&Logger).unwrap();
    log::set_max_level(Level::default().into());
}

/// Helper macro for internal error
#[macro_export]
macro_rules! internal_error {
    ($($arg:tt)*) => {
        log::error!(target: env!("CARGO_CRATE_NAME"), "Internal error: {}\nPlease raise an issue.", format!($($arg)*));
    };
}
