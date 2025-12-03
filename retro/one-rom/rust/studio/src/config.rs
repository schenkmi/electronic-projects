// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! Handles ROM metadata and image JSON format config files

#[allow(unused_imports)]
use log::{debug, error, info, trace, warn};
use std::path::PathBuf;

use crate::app::AppMessage;
use crate::studio::Message as StudioMessage;
use crate::{ManifestType, PathType};
use crate::{app_manifest, internal_error};

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct SelectedConfig {
    pub config: Config,
    pub data: Vec<u8>,
}

impl SelectedConfig {
    pub fn name(&self) -> String {
        self.config.name()
    }

    pub fn save_filename(&self) -> String {
        self.config.save_filename()
    }
}

/// Structure representing all available ROM configuration files
#[derive(Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
pub struct ConfigManifest {
    /// Version of the manifest
    pub version: usize,

    /// List of configuration file paths
    pub configs: Vec<String>,

    /// List of Config objects (derived from the manifest paths)
    #[serde(skip)]
    pub internal_configs: Vec<Config>,
}

impl From<Config> for SelectedConfig {
    fn from(config: Config) -> Self {
        SelectedConfig {
            config,
            data: Vec::new(),
        }
    }
}

impl std::fmt::Display for ConfigManifest {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "ConfigManifest({})", self.configs.len(),)
    }
}

impl ConfigManifest {
    /// Create a new ConfigManifest instance from JSON manifest file
    fn from_json(json: String) -> Result<Self, String> {
        // Parse the JSON
        let mut manifest: ConfigManifest = serde_json::from_str(&json)
            .map_err(|e| format!("Failed to parse Configs JSON:\n  - {e}"))?;

        // Create names from URLs
        let mut int_configs = manifest
            .configs
            .iter()
            .map(|url| {
                // Unwraps are safe here as split() and next() always return
                // Some() the first time around
                let name = url.split('/').last().unwrap().split('.').next().unwrap();
                (url.clone(), name.to_string())
            })
            .collect::<Vec<_>>();

        // Now sort them so that "blank" is first, then alphabetically
        int_configs
            .sort_by_key(|(_url, name)| (name.to_lowercase() != "blank", name.to_lowercase()));

        // Now turn into Config objects
        let configs = int_configs
            .into_iter()
            .map(|(url, name)| Config::Network { url, name })
            .collect::<Vec<_>>();

        manifest.internal_configs = configs;

        Ok(manifest)
    }

    pub fn urls(&self) -> &Vec<String> {
        &self.configs
    }

    /// Create ConfigManifest from network manifest
    ///
    /// Adds the special "Select Local File" entry, and config, if a local file
    pub async fn from_network_async(selected: Option<SelectedConfig>) -> Result<Self, String> {
        // Get the manifest from the network
        let url = Self::manifest_url();
        let response = reqwest::get(&url)
            .await
            .map_err(|e| format!("Network error fetching Configs manifest:\n  - {e}"))?;
        let text = response
            .text()
            .await
            .map_err(|e| format!("Network error reading Configs manifest:\n  - {e}"))?;

        // Construct from JSON
        let mut manifest = Self::from_json(text)?;

        // Add the special entries
        manifest.add_special();

        // If config if a file, add it to the manifest at the start
        if let Some(selected) = selected
            && selected.config.is_file()
        {
            manifest.internal_configs.insert(0, selected.config.clone());
        }

        Ok(manifest)
    }

    pub fn update_local_file(&mut self, config: Config) {
        // Remove any existing local file config
        self.remove_local_file();

        // Insert the new local file config at the start
        self.internal_configs.insert(0, config);
    }

    pub fn remove_local_file(&mut self) {
        // Remove any existing local file config
        self.internal_configs.retain(|c| !c.is_file());
    }

    fn add_special(&mut self) {
        // Add the SelectLocalFile entry at the start
        self.internal_configs.insert(0, Config::SelectLocalFile);
    }

    /// Return names of the configs
    pub fn names(&self) -> Vec<String> {
        // Iterate through configs to create a Vec of names
        self.internal_configs
            .iter()
            .filter_map(|config| {
                // Unwraps are safe here as split() and next() always return
                // Some() the first time around
                if !config.is_special() {
                    Some(config.name())
                } else {
                    None
                }
            })
            .collect::<Vec<_>>()
    }

    /// Return names of the configs as a single string with commas
    pub fn names_str(&self) -> String {
        self.names().join(", ")
    }

    /// Return config URL for a partial url
    pub fn config_url(url: &str) -> String {
        app_manifest()
            .url_from_path(PathType::RomConfig, url)
            .to_string()
    }

    /// Return configs manifest URL
    fn manifest_url() -> String {
        app_manifest()
            .manifest_url(ManifestType::RomConfig)
            .to_string()
    }
}

/// Fetch config file from URL
pub async fn get_config_from_partial_url(url: &String) -> Result<Vec<u8>, String> {
    // Build the full URL
    let full_url = ConfigManifest::config_url(url);

    let response = reqwest::get(full_url)
        .await
        .map_err(|e| format!("Network error fetching Config:\n  - {e}"))?;

    let status = response.status();
    if !status.is_success() {
        return Err(format!("HTTP error fetching Config: {status}"));
    }

    let bytes = response
        .bytes()
        .await
        .map_err(|e| format!("Network error reading Config:\n  - {e}"))?;

    Ok(bytes.to_vec())
}

/// Object representing a single ROM configuration
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Config {
    /// User has opted to upload their own configuration file
    File { filename: PathBuf },

    /// Dummy entry in the picklist to allow the user to select their own file
    SelectLocalFile,

    /// Config from the network manifest
    Network { url: String, name: String },
}

impl std::fmt::Display for Config {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Config::File { filename } => {
                write!(
                    f,
                    "File: {}",
                    filename.file_name().unwrap_or_default().to_string_lossy()
                )
            }
            Config::SelectLocalFile => {
                write!(f, "Select Local File...")
            }
            Config::Network { name, .. } => {
                write!(f, "{name}")
            }
        }
    }
}

impl From<SelectedConfig> for Config {
    fn from(selected: SelectedConfig) -> Self {
        selected.config
    }
}

impl Config {
    /// Is this a local file config?
    pub fn is_file(&self) -> bool {
        matches!(self, Config::File { .. })
    }

    /// Is this a network config?
    pub fn is_network(&self) -> bool {
        matches!(self, Config::Network { .. })
    }

    pub fn is_special(&self) -> bool {
        matches!(self, Config::SelectLocalFile)
    }

    /// Get URL if network config
    pub fn url(&self) -> Option<&String> {
        match self {
            Config::Network { url, .. } => Some(url),
            _ => None,
        }
    }

    /// Create SelectedConfig with data
    pub fn with_data(self, data: Vec<u8>) -> SelectedConfig {
        SelectedConfig { config: self, data }
    }

    /// Create Config from local file path
    pub fn from_local_path<P: AsRef<std::path::Path>>(path: P) -> Self {
        Config::File {
            filename: path.as_ref().to_path_buf(),
        }
    }

    // Return a suitable name for display
    pub fn name(&self) -> String {
        match self {
            Config::File { filename } => filename
                .file_name()
                .unwrap_or_default()
                .to_string_lossy()
                .to_string(),
            Config::SelectLocalFile => "none".to_string(),
            Config::Network { name, .. } => {
                // Strip off file extension if present
                let name = name.split('.').next().unwrap_or(name);
                name.to_string()
            }
        }
    }

    // Return a suitable filename for saving firmware image
    pub fn save_filename(&self) -> String {
        match self {
            Config::File { .. } => self
                .name()
                .split('.')
                .next()
                .unwrap_or("unknown")
                .to_string(),
            Config::SelectLocalFile => {
                internal_error!("Save filename requested for SelectLocalFile config.");
                "unknown".to_string()
            }
            Config::Network { .. } => self.name(),
        }
    }
}

/// Async download of a network config
pub async fn download_config_async(config: Config) -> AppMessage {
    // Download the config
    assert!(config.is_network());
    let url = config.url().unwrap();
    trace!("Downloading config from URL: {url}");
    match get_config_from_partial_url(url).await {
        Ok(data) => StudioMessage::ConfigLoaded(Ok(config.with_data(data))).into(),
        Err(e) => {
            let log = format!("Failed to download config from {url}: {e}");
            warn!("{log}");
            StudioMessage::ConfigLoaded(Err(log)).into()
        }
    }
}

/// Load a local config file
pub fn load_config_file(config: Config) -> AppMessage {
    // Load the config from local file
    assert!(config.is_file());
    if let Config::File { filename } = &config {
        match std::fs::read(filename) {
            Ok(data) => StudioMessage::ConfigLoaded(Ok(config.with_data(data))).into(),
            Err(e) => {
                let log = format!("Failed to read config file {}: {e}", filename.display());
                warn!("{log}");
                StudioMessage::ConfigLoaded(Err(log)).into()
            }
        }
    } else {
        unreachable!();
    }
}
