#!/usr/bin/env pwsh
#Requires -Version 5.0

# Builds the One ROM Studio application and NSIS installers for Windows.
#
# Pre-requisites:
# - Rust:
#
# ```powershell
#   Invoke-WebRequest -Uri https://win.rustup.rs/ -OutFile rustup-init.exe
#   .\rustup-init.exe -y
# ```

$ErrorActionPreference = "Stop"

# Parse command line arguments
$NoSign = $args -contains "nosign"
$NoDeps = $args -contains "nodeps"
$NoClean = $args -contains "noclean"

# Check for unexpected arguments
$ValidArgs = @("nosign", "nodeps", "noclean")
foreach ($arg in $args) {
    if ($arg -notin $ValidArgs) {
        Write-Error "Unknown argument: $arg. Valid arguments are: $($ValidArgs -join ', ')"
        exit 1
    }
}

# Log args
if ($NoSign) {
    Write-Host "!!!WARNING: Code signing disabled"
}
if ($NoDeps) {
    Write-Host "!!!WARNING: Dependency installation disabled"
}
if ($NoClean) {
    Write-Host "!!!WARNING: Clean disabled"
}

#
# Setup
#

$Target = "x86_64-pc-windows-msvc"

# Extract version from Cargo.toml
$Version = (Get-Content "Cargo.toml" | Select-String -Pattern '^version\s*=\s*"([^"]+)"').Matches.Groups[1].Value
Write-Host "Building version: $Version"

if (-not $NoDeps) {
    # Install the Rust targets
    rustup target add $Target

    # Install cargo-packager if not already installed
    cargo install cargo-packager --locked
}

#
# Clean previous builds
#

if (-not $NoClean) {
    cargo clean --target $Target
    Remove-Item -Path "dist\*.exe" -Force -ErrorAction SilentlyContinue
}
#
# Intel silicon (x86_64)
#

# Build One ROM Studio
Write-Host "Building for target: $Target"
cargo build --bin onerom-studio --release --target $Target | Out-Host
if ($LASTEXITCODE -ne 0) {
    Write-Error "Cargo build failed with exit code $LASTEXITCODE"
    exit $LASTEXITCODE
}

# Sign the executable
if (-not $NoSign) {
    Write-Host "Signing executable..."
    & "scripts\sign-win.ps1" "..\target\$Target\release\onerom-studio.exe"
    if ($LASTEXITCODE -ne 0) {
        Write-Error "Signing executable failed with exit code $LASTEXITCODE"
        exit $LASTEXITCODE
    }
}

# Create temporary versioned Packager.toml
$PackagerContent = Get-Content "Packager.toml"
$PackagerContent = $PackagerContent -replace "%VERSION%", $Version
$TempPackagerPath = "Packager_temp.toml"

# Write the temporary Packager.toml
$PackagerContent | Set-Content $TempPackagerPath

# Package as NSIS installer
Write-Host "Packaging NSIS installer for target: $Target"
cargo packager -c $TempPackagerPath --release --target $Target --formats nsis | Out-Host
if ($LASTEXITCODE -ne 0) {
    Write-Error "Cargo packager failed with exit code $LASTEXITCODE"
    Remove-Item -Path $TempPackagerPath -Force -ErrorAction SilentlyContinue
    exit $LASTEXITCODE
}

# Remove temporary Packager.toml
Remove-Item -Path $TempPackagerPath -Force

# Sign the installer
if (-not $NoSign) {
    Write-Host "Signing installer..."
    & "scripts\sign-win.ps1" "dist\onerom-studio_${Version}_x64-setup.exe"
    if ($LASTEXITCODE -ne 0) {
        Write-Error "Signing installer failed with exit code $LASTEXITCODE"
        exit $LASTEXITCODE
    }
}

Write-Host "Windows x86_64 build complete."
