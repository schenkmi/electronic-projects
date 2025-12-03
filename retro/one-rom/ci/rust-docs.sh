#!/bin/bash
set -e

cd rust
echo "Generating documentation for Rust crates..."

echo "Generating documentation for onerom-config..."
cargo doc -p onerom-config

echo "Generating documentation for onerom-database..."
cargo doc -p onerom-database

echo "Generating documentation for onerom-fw..."
cargo doc -p onerom-fw

echo "Generating documentation for onerom-gen..."
cargo doc -p onerom-gen

echo "Generating documentation for onerom-protocol..."
cargo doc -p onerom-protocol

echo "Generating documentation for schema-gen..."
cargo doc -p schema-gen

echo "Generating documentation for sdrr-fw-parser..."
cargo doc -p sdrr-fw-parser