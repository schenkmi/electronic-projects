// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! Generates application manifest for first time use.
//!
//! Generates a manifest based on default values.  Only really useful the
//! first time the manifest is generated - after that the existing manifest
//! should be edited as required.

use onerom_studio::app::manifest::Manifest;
use std::path::PathBuf;

// Filename for sample "studio.json" manifest
const MANIFEST_PATH: &str = "manifest/sample-studio.json";

fn main() {
    // Generate default manifest
    let default_manifest = Manifest::default();

    // Get the path to write the manifest to
    let workspace_root = workspace_root();
    let manifest_path = workspace_root.join("studio");
    let manifest_path = manifest_path.join(MANIFEST_PATH);

    // Write it
    let manifest_json = serde_json::to_string_pretty(&default_manifest).unwrap();
    std::fs::write(manifest_path, manifest_json).unwrap();
}

fn workspace_root() -> PathBuf {
    let output = std::process::Command::new("cargo")
        .args(["locate-project", "--workspace", "--message-format=plain"])
        .output()
        .unwrap();

    let cargo_toml = PathBuf::from(String::from_utf8(output.stdout).unwrap().trim());
    cargo_toml.parent().unwrap().to_path_buf()
}
