# Changelog

## v0.1.4 - ????-??-??

### Fixed

- Set Windows PE file and product versions to match Cargo version.

## v0.1.3 - 2025-11-24

### Fixed

- Panic (crash) when analyzing a Fire with a debug probe.  Moved to fork of probe-rs with fix for panic.
- Allow multi-rom sets to be built
- Statically link with vcruntime

## v0.1.2 - 2025-11-09

- Built with rustc 1.91
- Move to probe-rs 0.30
- Added ability to load ROM config JSON files from disk in Create view
- Added online manifest to access latest URLs, with local cache file backup, and defaults as further backup
- Added app version update check and download link

## v0.1.1 - 2025-10-30

- Built with rustc 1.90
- Mac and Windows releases now signed.
- Mac app now uses the One ROM liquid glass icon.
- Moved to libusb-less DFU implementation using `dfu-rs` and `nusb` crates.
- Moved to manual rescanning to detect probes and USB devices.
- Added network connectivity icon.
- Single universal macOS dmg installer instead of separate Intel and Apple Silicon versions.
- Added ability to load ROM config JSON files from disk in Create view.