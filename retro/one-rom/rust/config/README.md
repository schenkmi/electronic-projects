# onerom-config

One ROM configuration crate

This crate contains objects and functions for working with One ROM configurations:

- Supported ROM types (e.g. 2364, 27128) and their specifications
- One ROM Hardware revisions and their properties
- One ROM runtime image configuration

It is primarily intended for use by the One ROM firmware tooling, but may be useful in other embedded or WASM projects related to One ROM - for example, Airfrog and the One ROM website.

This crate is designed to be `no_std` compatible, but alloc is used by the runtime image configuration code.

The code supporting ROM types and One ROM hardware revisions is generated automatically by `build.rs` from JSON configuration files. This ensures that the data is always up to date and consistent, and avoids the need for runtime parsing or allocations.
