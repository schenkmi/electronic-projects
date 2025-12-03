# Releasing New Version of One ROM

## Update Version Number

To update the version:

- Add the new version to [CHANGELOG.md](CHANGELOG.md), and note key changes.
- Update the version in [Makefile](/Makefile).
- Update the version in [sddr-check/Cargo.toml](/rust/sdrr-check/Cargo.toml).
- Update the version in [sddr-fw-parser/Cargo.toml](/rust/sdrr-fw-parser/Cargo.toml).
- Update the version in [sddr-gen/Cargo.toml](/rust/sdrr-gen/Cargo.toml).
- Update the version in [sddr-info/Cargo.toml](/rust/sdrr-info/Cargo.toml).
- Update the version in [lab/Cargo.toml](/rust/lab/Cargo.toml).
- Update the version in [protocol/Cargo.toml](/rust/protocol/Cargo.toml).
- Update the version in [database/Cargo.toml](/rust/database/Cargo.toml).
- Update the version in [config/Cargo.toml](/rust/config/Cargo.toml).
- Update the version in [gen/Cargo.toml](/rust/gen/Cargo.toml).
- Update the version in [fw/Cargo.toml](/rust/fw/Cargo.toml).
- Update the version consts `MAX_VERSION_*` in [rust/sdrr-fw-parser/src/lib.rs](/rust/sdrr-fw-parser/src/lib.rs).

## Release Process

Ensure all changes are committed, including the [version number updates](#update-version-number).

```bash
git pull
git push
```

Locally run the following tests:

```bash
ci/build.sh test
ci/build.sh ci
ci/build.sh release v<x.y.z>
```

---

Publish `onerom-database` to crates.io:

```bash
cd rust
cargo publish --dry-run -p onerom-database
cargo publish -p onerom-database
```

Update link to `onerom-database` in [protocol/Cargo.toml](/rust/protocol/Cargo.toml) to use the crates.io version.

---

Publish `onerom-protocol` to crates.io:

```bash
cd rust
cargo publish --dry-run -p onerom-protocol
cargo publish -p onerom-protocol
```

Update links to `onerom-database` and `onerom-protocol` in [lab/Cargo.toml](/rust/lab/Cargo.toml) to use the crates.io versions.

---

Publish `onerom-config` to crates.io:

```bash
cd rust
cargo publish --dry-run -p onerom-config
cargo publish -p onerom-config
```

Update links to and `onerom-config` in others to use the crates.io versions.

---

Publish `onerom-gen` to crates.io:

```bash
cd rust
cargo publish --dry-run -p onerom-gen
cargo publish -p onerom-gen
```

Update links to and `onerom-gen` in others to use the crates.io versions.

---

Publish the new version of `sdrr-fw-parser` to crates.io:

```bash
cd rust
cargo publish --dry-run -p sdrr-fw-parser
cargo publish -p sdrr-fw-parser
```

---

If on a branch, submit a pull request and merge it into main.

Tag the version in git:

```bash
git tag -s -a v<x.y.z> -m "Release v<x.y.z>"
git push origin v<x.y.z>
```

## WASM/Site/Images updates

- Update `onerom-wasm` to the new sdrr-fw-parser/sdrr-gen version if required and release.
  - Make sure to bump the wasm development version releasing
  - Check release appears in wasm/releases, and new dev version on homepage
- Update `one-rom-site` to use the new `onerom-wasm` version, test and release
  - Ensure can read/write firmware correctly using web programmer
  - Ensure can see new firmware versions for images (comes from `one-rom/releases/releases.json)
- Update releases in `one-rom-images`
  - Within `one-rom` `main` branch run `ci/build-images.sh x.y.z ../one-rom-images`
  - Paste the new release manifest fragment to `one-rom-images/releases.json` and update `latest`
  - Ensure images exist under `one-rom-images/releases/x.y.z/`
  - Commit and push changes to `one-rom-images` repo
  - Test using Studio
