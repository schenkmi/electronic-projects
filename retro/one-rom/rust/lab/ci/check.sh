# Cargo fmt
cargo fmt

# Basic builds
cargo build
cargo build --release

# Builds of supported hardware variants including "repeat" support
cargo build --release --no-default-features --features f401re,repeat
cargo build --release --no-default-features --features f405rg,repeat
cargo build --release --no-default-features --features f411re,repeat
cargo build --release --no-default-features --features f446re,repeat

# Builds of supported hardware variants including "control" support
cargo build --release --no-default-features --features f401re,control
cargo build --release --no-default-features --features f405rg,control
cargo build --release --no-default-features --features f411re,control
cargo build --release --no-default-features --features f446re,control

# Builds of supported hardware variants including "oneshot" support
cargo build --release --no-default-features --features f401re,oneshot
cargo build --release --no-default-features --features f405rg,oneshot
cargo build --release --no-default-features --features f411re,oneshot
cargo build --release --no-default-features --features f446re,oneshot

# Check with logging
DEFMT_LOG=trace cargo build
DEFMT_LOG=debug cargo build --release
DEFMT_LOG=info cargo build --release
DEFMT_LOG=warn cargo build --release
DEFMT_LOG=error cargo build --release

# Clippy
cargo clippy -- -D warnings
cargo clippy --no-default-features --features f401re,repeat -- -D warnings 
cargo clippy --no-default-features --features f401re,control -- -D warnings 
cargo clippy --no-default-features --features f401re,oneshot -- -D warnings 

# Docs
cargo doc
