#!/bin/bash
set -e

echo "Starting cross-compilation of onerom-fw CLI Firmware Generator"
echo "- The first time you do this may take a while for Rust to download all the targets, and to download the cross-rs container"

cd rust

# Windows - GNU
echo "- Building for Windows - GNU..."
cross build --release --target x86_64-pc-windows-gnu -p onerom-fw --bin onerom-fw

# macOS - Intel
echo "- Building for macOS - Intel..."
cross build --release --target x86_64-apple-darwin -p onerom-fw --bin onerom-fw

# macOS - Apple Silicon
echo "- Building for macOS - Apple Silicon..."
cross build --release --target aarch64-apple-darwin -p onerom-fw --bin onerom-fw
