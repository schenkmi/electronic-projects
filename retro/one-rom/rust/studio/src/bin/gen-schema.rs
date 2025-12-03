// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! Generates application manifest JSON schema

use onerom_studio::app::manifest::Manifest;
use schemars::schema_for;
use std::path::PathBuf;

const SCHEMA_PATH: &str = "manifest/app-schema.json";

fn main() {
    // Generate JSON schema for application manifest
    let schema = schema_for!(Manifest);
    let json = serde_json::to_string_pretty(&schema).unwrap();

    // Get the path to write the schema to
    let workspace_root = workspace_root();
    let schema_path = workspace_root.join("studio");
    let schema_path = schema_path.join(SCHEMA_PATH);

    // Write it
    std::fs::write(schema_path, json).unwrap();
}

fn workspace_root() -> PathBuf {
    let output = std::process::Command::new("cargo")
        .args(["locate-project", "--workspace", "--message-format=plain"])
        .output()
        .unwrap();

    let cargo_toml = PathBuf::from(String::from_utf8(output.stdout).unwrap().trim());
    cargo_toml.parent().unwrap().to_path_buf()
}
