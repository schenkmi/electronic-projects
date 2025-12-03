#!/bin/bash
set -e

cd rust
echo "Running tests for Rust crates..."

echo "Testing onerom-config..."
cargo test -p onerom-config

echo "Testing onerom-database..."
cargo test -p onerom-database

echo "Testing onerom-fw..."
cargo test -p onerom-fw

echo "Testing onerom-gen..."
cargo test -p onerom-gen

echo "Testing onerom-protocol..."
cargo test -p onerom-protocol

echo "Testing schema-gen..."
cargo test -p schema-gen

echo "Testing sdrr-fw-parser..."
cargo test -p sdrr-fw-parser