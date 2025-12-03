# Changelog

All notables changes between versions are documented in this file.

## v0.5.6 - 2025-??-??

### Fixed

- Comment in Makefile - B is now default serving algorithm.

## v0.5.5 - 2025-11-18

This release adds support for the RP2350 One ROM serving ROMs using the RP2350's PIO/DIO peripheral, allowing fully autonomous ROM serving without any CPU involvement.  A VIC-20 kernal can be served successfully with the RP2350 clocked at just 22MHz, the C64 kernal at 41MHz and the both systems' character ROMs at 51MHz.  There are some limitations, meaning this is not yet the default Fire algorithm:
- Dynamically bank switched ROMs _are_ supported.
- Only CS lines which are contiguous are supported - hence the 2316 is _not_ supported on either rev A or USB rev B.
- Multi-ROM sets, via X1/X2, are _not_ supported, as they are not contiguous with the CS lines in current hardware.

For full support a hardware revision must order the CS lines contiguously either:
- X2/X1/CS1/A12/A11 or
- A11/A12/CS1/X1/X2

To build use `EXTRA_C_FLAGS=-DRP_PIO` when running `make`.  See `sdrr/src/piorom.c` for further details of the PIO/DMA algorithm, and configuration options.

### Fixed

- Enabled FP extensions on both Ice and Fire to avoid hard fault if floating point instructions are used by the compiler.

## v0.5.4 - 2025-11-12

This release adds support for the One ROM Fire (RP2350) USB version, via hardware revision `fire-24-usb-b`.  Current USB support is per Ice - plugging in USB disables ROM serving, and puts the RP2350 into DFU mode to allow firmware updates.  A future release is expected to add Fire USB support in parallel to ROM serving. 

### Added

- Added first RP2350 USB version, [Fire 24 USB B](sdrr-pcb/unverified/fire-24-24-b/README.md), as unverified.
- Added [Ice 24 USB H3](sdrr-pcb/unverified/one-rom-ice-usb-h3-24-pin/README.md) as unverified.
- Moved [Ice 24 USB H2](sdrr-pcb/verified/one-rom-ice-usb-h2-24-pin/README.md) to verified.

### Added

- `onerom-config` 0.2.2 - Added method to query ROM power pins.
- Studio:
    - See [rust/studio/CHANGELOG.md](rust/studio/CHANGELOG.md) for details.
    - Studio is released independently of firmware - see `studio-*` github tags.
- ROM Configs:
    - Blank ROM config (for manufacturing/testing) - /rom-configs/blank.json
    - Added pincoder 2021 version system 3, 5, 6 and 7 ROM configs (2332 ROMs)
- Allow `sdrr-fw-parser` to parse up to v0.5.999 firmware versions. 

### Fixes

- [#43](https://github.com/piersfinlayson/one-rom/issues/43) - Let sdrr-fw-parser parse later versions of fw. Supports up to v0.5.999 with no code/wasm/site changes required.
- Allow multi-ROM sets to be built in One ROM Studio.  Unsure when this was regressed

## v0.5.3 - 2025-10-24

The major addition in this release is the companion desktop application, One ROM Studio, which provides a native GUI for creating One ROM firmware images, and analysing and flashing One ROM devices.

<img src="docs/images/one-rom-studio-win-v0.1.0.png" alt="One ROM Studio on Windows" width="500">

Features include:
- Supported platforms: Windows, Mac, Linux (Ubuntu, Debian and Raspberry Pi OS)
- Supported One ROMs: all variants including Ice/Fire and Pro/USB
- Program One ROMs with a choice of ROM images
- Generate and save One ROM firmware files
- Analyse One ROM devices and firmware files
- Automatic debug probe and One ROM USB detection

One ROM Studio can be downloaded from https://onerom.org/studio/.

### Added

- Added "limp mode" support to detect when an incompatible firmware has been flashed to an Ice One ROM.  It blinks fast in this state and, if it is a USB model, allows the device to drop into DFU mode when USB is connected, to allow flashing of a compatible firmware.  Note that "slower" MCU firmwares are permitted by "faster" MCUs - but not the other way around.  See #37 for details.

### Fixes

## v0.5.2 - 2025-10-14

New in this release is a command line firmware image creation tool `rust/fw`.  This dynamically creates a custom One ROM firmware image from a specified:
- set of ROM images (specified as a JSON config file)
- model, board and MCU type (specified as command line arguments)
- optional firmware version (defaults to the latest version available)

To build:
```bash
cd rust/fw
cargo build --release --bin onerom-fw
# Binary is located at /rust/target/release/onerom-fw
```

This is a precursor to simplifying the CI builds to avoid having to create every combination of hardware/ROM config as build artifacts.  The hardware combinations can be pre-built with empty metadata and ROM image data, and this tool then composes a complete firmware image, ready for flashing.

As v0.5.1, and empty firmware image can also be flashed - One ROM then blinks its status LED slowly, and can have metadata and ROM images flashed to it later.

The complete list of available "empty" hardware configuration firmwares can be found at https://images.onerom.org/releases.json.

This command line tool may also be augmented with a native GUI, in parallel to the web-based tool at https://onerom.org/prog/.

### Changes

- Improved `onerom-gen` testing, and improved `onerom-config` and `onerom-gen` validation.

### Fixes

- Fix rust/gen/tests for boards with address lines all >=8.
- Fix `sdrr-info` processing of firmware from v0.5.1 onwards with detailed metadata content in a valid, but unexpected, order.

## v0.5.1 - 2025-10-13

For the average user, there are no particularly notable changes in this release, except the addition of the [Atari 800XL BASIC ROM config](/config/atari800xl.mk).

The firmware generator process underwent a major overhaul in this release:
- Support ROM types and hardware (PCB) revisions are now parsed at build time, which can be included in Web Assembly code.
- `sdrr-common` has been retired and mostly replaced with `onerom-config`
- Much of `sdrr-gen` has been moved out to `onerom-gen` crate, which can be used in other Rust projects, including Web Assembly.
- There is a new `onerom-wasm` crate at https://github.com/piersfinlayson/one-rom-wasm, which can be used to build Web Assembly code to generate One ROM firmware images in the browser.  Web Assembly packages, documentation and examples are located at https://wasm.onerom.org/.
- A metadata and ROM-less firmware can be built with `EXCLUDE_METADATA=1`.  When flashed with ths firmware, One ROM blinks its status LED slowly.  It can subsequently have metadata and ROM image fragments flashed, and, when reset, serves the newly flashed images.  This is expected to be useful for release artifacts and manufacturing, as a single firmware per hardware variant per release can be built, with metadata and ROM images added later, rather than the current need to build a firmware per hardware variant **per configuration** per release.

There is more work planned to the firmware upgrade process, including multi-stage USB device updates using the new capabilities, but this release has laid the groundwork and enabled some exciting new web-based features.

Also, the first, prototype 28 pin ROM support using hardware revision `ice-28-a` is in this release.  It successfully emulates a 27128 ROM (i.e. without the 3rd CS line on a 23128).  It has been tested successfully on a C64C, replacing the combined KERNAL/BASIC ROM with a One ROM Ice 28 A, clocked at just 55MHz using an STM32F446RCT6. This hardware revision is unlikely to be taken forwards - a different hardware layout is required to support 23128 with the 3rd CS line being used, as well as 32KB and 64KB ROMs.

Some default firmware configuration has been changed:
- BOOT_LOGGING is now disabled by default to improve boot times.

### New

- [Atari 800XL BASIC ROM config](/config/atari800xl.mk) included (and tested and working!)

### Changes

- Call out from sdrr-gen to wget to retrieve images located on sourceforge, as cloudfare seems to spot and block Rust TLS.
- Moved the PCB config/property files from `/hw-config` to `/rust/config/json`.

### Fixes

- Make "no ROMs installed" LED blink pattern slower, to be more visible.  Now on for 0.5s, off for 2.5s.  Previously flashed much too fast to be used properly.

## v0.5.0 - 2025-10-07

This release adds a bunch of hardware revisions, plus a modified flash and firmware format, to ease future device re-programming.

As a consequence of the new flash/firmware format, some of the STM32 variants (F401RB/RC, F411RC, F446RC) support 2 fewer ROM images than before.

### New

- New flash/firmware format, with firmware code, followed by ROM metadata, followed by ROM images. 
- Added One ROM Ice USB H2 (unverified).
- Added One Rom Ice USB H (verified) kicad files.
- Added One ROM Fire USB B (unverified)

### Changes

Moved USB programmer site to https://github.com/piersfinlayson/one-rom-site repo.

## v0.4.4 - 2025-09-30

This is a point release that changes the release artifact generation, to set up the One ROM USB programmer to be able to offer to flash pre-built firmware images from the release artifacts.

Release artifact change summary:
- Include additional hardware variants
- Only include .bin files (not .elf, .dis, .map) in the release artifacts.
- Remove some of the less common STM32 variants from the release artifacts (to save build time and space)
- Include a build artifact manifest JSON file. 

If the particular release artifact you want is no longer included, you can build it yourself from source.

### Changes

Updated:
- USB One ROM site (onerom.piers.rocks):
  - Added the ability to select a local file as the firmware source, in addition to a URL.
  - Add check to prevent non-USB firmware being flashed.
  - Add check to ensure the MCU the firmware was build for matches the MCU the user selected.
- CI build process, to create release artifacts:
  - Now only creates .bin files (not .elf, .dis, .map) - if you want the other types, build them yourself.
  - Creates images for multiple different hardware revisions.

## v0.4.3 - 2025-09-29

Added USB DFU support for firmware updates over USB, along with STM32 24-pin rev H hardware (24-h) which includes a micro-USB connector.  One ROM detects when USB is connected, disables ROM serving, and enters STM32 DFU mode to allow the firmware to be updated.

There is also a new web-based programmer for One ROM USB, at https://onerom.piers.rocks/.  This can be used on Chrome or Chromium based browsers on Windows, Linux, or MacOS to program an attached One ROM USB.

### Changes

Updated:
- sdrr
- sdrr-hw-config
- sdrr-pcb
- sdrr-common
- sdrr-fw-parser
- sdrr-gen
- sdrr-info

### Fixes

## v0.4.2 - 2025-09-06

Added [One ROM Lab](rust/lab/README.md) support, which allows a One ROM to be used as a ROM reader.

### Changes

- Added fw-parser for One ROM Lab
- Modify sdrr-info/parser to support Airfrog custom firmware changes

### Fixes

- Probably a few here and there.

## v0.4.1 - 2025-08-28

### Changes

- Move STM32F4 hardware rev G to verified.
- Add KiCad design files for RP2350 rev A and STM32F4 rev G.

### Fixes

- #8 - reduce severity of VOS not ready warning, as it appears to be benign.
- Include RP2350 images in github release.
- Add RP2350 build commands to README.md and generally update the docs to refer to One ROM/RP2350.

## v0.4.0 - 2025-08-24

**The RP2350 release.**

This version contains the first RP2350 PCB revision, and mostly complete firmware support.

Should you use the new RP2350 hardware revision A?  Only limited testing of the RP2350 One ROM has been done so far, but it has generally performed well.

There is one outstanding, known issue - when using the RP2350 One ROM a character ROM on a PAL VIC-20 occasionally the machine boots to a black screen background - that is the machine boots to BASIC and shows the expected text, but the screen is black, not white.  This may be a boot timing issue - that perhaps One ROM RP2350 is not booting fast enough for the VIC chip, which is getting corrupted somehow.  This issue does not appear on a C64 (which has a different video bus architecture).

You may want to order and test small quantities of RP2350 based boards for now, as there is some risk of a hardware design issue coming to light.  However, the hardware appears solid in early testing, so it is likely most issues can be overcome by firmware changes - and it is expected that the RP2350 revision A will continue to be supported in future releases, even should another variant be released.

Other notable changes:

- Instead of building with `STM=<mcu variant> make`, you now need to use `MCU`:

  ```bash
  MCU=<mcu_variant> make
  ```

### Changes

- Added RP2350 support.
  - Hardware rev A.
  - Includes single ROM images, dynamically bank switched, and multi-ROM sets.
  - Includes image select jumpers, status LED, overclocking.
  - Features not supported include: C main loop, MCO output.
  - For the gory details of supporting the RP2350, see [RP2350](docs/RP2350.md).
- Added STM32F4 24-pin PCB rev G hardware configuration.  This adds a different programming header and one more image select jumper (so 5 in total, plus X1/2).
- Added hardware and firmware configuration to specify whether the image select jumpers and X1/X2 pins are pulled high or low when the PCB jumper is closed, to allow for different PCB designs.
- Added firmware support for up to 7 image select jumpers.
- Change STM32 MCO (and MCO2) divider to be /5 (previous value was /4).  Makes it easier to measure the clock speed of an overclocked STM32F4.
- Substantially refactored platform specific code to break out platform agnostic code - significant work to `sdrr/src/main.c`, `utils.c` and `rom_impl.c`.
- Tested overclocking and various STM32 clones.

### Fixes

- It is likely that the 4th image select pin on revs E/F didn't work properly - this has been fixed.

## v0.3.1 - 2025-08-16

The project has been renamed One ROM (To Rule Them All).

This release is a few odds and ends including some hardware improvements:
- One ROM hardware revision [F2](/sdrr-pcb/verified/stm32f4-24-pin-rev-f2/README.md) is currently recommended.
- An **unverified** hardware revision [G](/sdrr-pcb/unverified/stm32f4-24-pin-rev-g/README.md) is in testing.  This brings mostly layout improvements and slightly reduced manufacturing costs.
- The fastest STM32F4 MCU, the STM32F446 has been verified to work.   This brings a max supported clock speed of 180MHz, and has run stably up to 300MHz in testing.
- The STM32F405 has provided slower than expected (more details below).  It is supported and a decent choice, but the GigaDevices GD32F405 appears to be more performant.

### Changes

- Speed up STM32F405 support:
  - The STM32F405 is under-performant vs the other devices at the same clock speed - needs around 30-40% faster clock speed.
  - Added CCM RAM support for the F405, bringing the uplift in clock speed down to around 15-20%.
  - To disable CCM RAM set `C_EXTRA_FLAGS=-DDISABLE_CCM=1` when building.
  - The STM32F405 is still a decent MCU choice for One ROM, as its max clock speed is 168MHz compared with the F411's 100MHz.  However, users may wish to use the GigaDevices clone GD32F405, which appears to have no performance penalty. 
- Hardware revision 24-f2 is now verified.  JLC have successfully fabbed using the hardware files both STM32F411 and STM32F405 variants.
- Allow more aggressive overclocking (up to 400MHz).
- Validated STM32F446RCT6 (STM32F446RET6 highly likely to work as well).  Successfully tested as C64 char ROM, and verified clock speed of 180MHz (via MCO1 showing 45MHz = SYSCLK/4).  Also overclocked to 300MHz, ran stably.
- Added **unverified** hardware revision 24-g.

### Fixes

- Explicitly prevent COUNT_ROM_ACCESS and C_MAIN_LOOP being configured together, as they are incompatible.
- Fixed ability to run main loop from RAM (this tends to be slower than from flash, so isn't recommended).

## v0.3.0 - 2025-08-12

The main user facing change in this release is the addition of support for remote analysis and co-processing alongside the SDRR device via plug-ins, such as [Airfrog](https://piers.rocks/u/airfrog) - **a tiny $3 probe for ARM devices**.  This allows you to inspect the firmware and runtime state of the SDRR device, and change its configuration and ROM data - **while it is serving ROMs**.

There is also new ROM access counting feature, which causes SDRR to count how times the CS line(s) go active.  This can be extracted and visualised using [Airfrog](https://piers.rocks/u/airfrog) and other SWD probes, to determine how often the ROMs are accessed based on host activity.

![ROM Access Graph](docs/images/access-rate.png)

The Rust tooling has been substantially refactored to easier to integrate SDRR support in third-party tooling, such as [Airfrog](https://piers.rocks/u/airfrog).  In particular there is [Firmware Parser](rust/sdrr-fw-parser/README.md) crate, which can be used to parse the firmware from a file or running SDRR, and extract information about the configuration, ROM images, and to extract ROM images from the firmware.

### Changes

- TI-99/4A and CoCo2 configurations have been added to the [third-party configs](config/third-party/README.md) directory.  Thanks to [@keronian](https://github.com/keronian) for contributing these.
- Added a C main loop implementation for which GCC produces the assembly/machine code.  This requires a roughly 25% faster clock speed.  Use `EXTRA_C_FLAGS=-DC_MAIN_LOOP` when running `make` to use this version.
- Stored off image files used to create the firmware in `output/images/`.  This allows post build inspection of the images used.  It also enables additional tests - `sdrr-info` can be now be used as an additional automated check (along with `test`), to ensure the images in the firmware are correct, and validate the behaviour of `sdrr-info` and `test` to be compared.
- Substantial refactoring of `sdrr-gen`, to make it more maintainable.
- Substantial refactoring of `sdrr-fw-parser` in order to make it suitable for airfrog integration.
- Added ROM access counting behind COUNT_ROM_ACCESS feature flag.  When enabled, the firmware updates a u32 counter at RAM address 0x20000008 every time the chip select line(s) go active - i.e. the ROM is selected.  This can be read by an SWD probe, such as [Airfrog](https://piers.rocks/u/sdrr). 
- Changed default Makefile configuration to HW_REV=24-f COUNT_ROM_ACCESS=1 STATUS_LED=1.
- Added a manufacturing test tool [`sdrr-check`](rust/sdrr-check/README.md).
- Changed default build config:
  - HW_REV=24-f
  - STATUS_LED=1
  - COUNT_ROM_ACCESS=1
- Added retrieval of mangled ROM images from firmware.  This can be used to compare the embedded images between different firmwares and to collect a pre-mangled ROM images in order to overwrite a running SDRR's RAM image with it.
- Added new "One ROM To Rule Them All" BASIC program for upcoming video. 

### Fixes

- Probably a few here and there.

## v0.2.1 - 2025-07-22

The main new feature in this version of SDRR is the addition of dynamic [bank switching](docs/MULTI-ROM-SETS.md#dynamic-bank-switching) of ROM images.  This allows SDRR to hold up to 4 different ROM images in RAM, and to switch between them **while the host is running** by using the X1/X2 pins (hardware revision F and later) to switch between them.  Some fun [C64](config/bank-c64-char-fun.mk) and [VIC-20](config/bank-vic20-char-fun.mk) character ROM configurations that support bank switching are included.

In other news:
- The default ROM serving algorithm has been improved, leading to better performance, and hence the ability to support more systems with lower powered STM32F4 devices than before.  Check out [STM32 Selection](docs/STM32-SELECTION.md). The current price/performance sweet spot is the F411.
- [Hardware revision E](sdrr-pcb/verified/stm32f4-24-pin-rev-e/README.md) is now fully verified, so manufacture these with confidence.
- If you'd rather use [revision F](sdrr-pcb/unverified/stm32f4-24-pin-rev-f/README.md) (required for multi-ROM and bank switching support), at least once user has reported getting these manufactured and working with his NTSC VIC-20 - although they did not testing either multi-ROM or bank switching support.

### Changes

- Added pull-up/downs to X1/X2 in multi-ROM cases, so that when a multi-set ROM is configured, but X1/X2 are not connected, the other ROMs in the set still serve properly.
- Improved serving algorithm `B` in the CS active low case.
- Moved to algorithm `B` by default.
- Measured performance of both algorithm on all targets.
- Refactor `rom_impl.c`, breaking out assembly code to `rom_asm.h` to make the main_loop easier to read, and commonalising a bunch of the code for greater maintainability.
- Added detection of hardware reported STM32F4 device and flash size at runtime, and comparison to firmware values - warning logs are produced in event of a mismatch.
- Verified [hw revision e](/sdrr-pcb/verified/stm32f4-24-pin-rev-e/) - supports STM32F4x5 variants in addition to F401/F411, all passives are now 0603, contains a status LED and a 4th image select jumper.
- Added [documentation](/docs/STM32-CLONES.md) on STM32 clones.
- Moved firmware parsing to [`rust/sdrr-fw-parser`](/rust/sdrr-fw-parser/README.md) crate, which can be used to parse the firmware and extract information about the configuration, ROM images, and to extract ROM images from the firmware.  Done in preparation for using the same code from a separate MCU.
- Moved Rust code to [`rust/`](/rust/) directory to declutter the repo a bit.
- Added experimenta; [build containers](/ci/docker/README.md) to assist with building SDRR, and doing so with the recommended build environment.
- Added dynamic [bank switchable](docs/MULTI-ROM-SETS.md#dynamic-bank-switching) ROM image support, using X1/X2 (you can use __either__ multi-ROM __or__ bank switching in a particular set).
- Added fun banked character ROM configs.
- Added VIC-20 NTSC config.
- Added retry in [ci/build.sh](ci/build.sh) to allow for intermittent network issues when downloading dependencies.
- Added [demo programs](demo/README.md) for C64 and VIC-20 to list SDRR features and other information/

### Fixes

- Fixed status LED behaviour, by placing outside of MAIN_LOOP_ONE_SHOT, and using the configured pin.
- Got `sdrr` firmware working on STM32F401RB/RC variants.  These have 64KB RAM, so can only support individual ROM images (quantity limited by flash) and do not support banked or multi-set ROMs.

## v0.2.0 - 2025-07-13

This version brings substantial improvements to the SDRR project, including:

- A single SDRR can be used to replace multiple ROM chips simultaneously.
- New [`sdrr-info`] tool to extract details and ROM images from firmware.
- Add your own hardware configurations, by adding a simple JSON file.
- New STM32F4 variants supported.
- Comprehensive testing of compiled in images to ensure veracity.

Care has been taken to avoid non-backwards compatible interface (such as CLI) changes, but some may may have been missed.  If you find any, please report them as issues.

### New Features

- Added support for ROM sets, allowing SDRR to serve multiple ROM images simultaneously, for certain combinations of ROM types.  This is done by connecting just the chip selects from other, empty sockets to be served, to pins X1/X2 (hardware revision 24-f onwards).  Currently tested only on VIC-20 (PAL) and C64 (PAL), serving kernal and BASIC ROMs simultaneously on VIC-20 and kernal/BASIC/character ROMs simultaneously on the C64.  See [Multi-ROM Sets](/docs/MULTI-ROM-SETS.md) for more details.
- Added [`sdrr-info`](/rust/sdrr-info/README.md) tool to parse the firmware and extract information about the configuration, ROM images, and to extract ROM images from the firmware.  In particular this allows
  - listing which STM32F4 device the firmware was built for
  - extraction of ROM images from the firmware, for checksumming and/or comparing with the originals.
- Moved hardware configuration to a dynamic model, where the supported hardware configurations are defined in configuration files, and the desired version is selected at build time.  Users can easily add configurations for their own PCB layouts, and either submit pull requests to include them in the main repository, or keep them locally.  For more details see [Custom Hardware](/docs/CUSTOM-HARDWARE.md).
- Added support F446 STM32F446R C/E variants - max clock speed 180 MHz (in excess of the F405's 168 MHz).  Currently untested.
- Added [`test`](/test/README.md), to verify the images source code files which are built into the firmware image, output the correct bytes, given the mangling that has taken place.

### Changes

- Updated VIC-20 PAL config to use VIC-20 dead-test v1.1.01.
- 24-pin PCB rev E/F gerbers provided (as yet unverified).
- Many previously compile time features now moved to runtime.
- Makefile produces more consistent and less verbose output.
- Added `sddr_info` struct to main firmware, containing firmware properties, for use at runtime, and later extraction.  This should also allow querying the firmware of a running system via SWD in future.

### Fixed

- Moved to fast speed outputs for data lines, instead of high speed, to ensure VOL is 0.4V, within the 6502's 0.8V requirement.  With high speed outputs, the VOL can be as high as 1.3V, which is beyond the 6502's 0.8V requirement.

## v0.1.0 - 2025-06-29

First release of SDRR.

- Supports F401, F411, and F405 STM32F4xxR variants.
- Includes configurations and pre-built firmware for C64, VIC-20 PAL, PET, 1541 disk drive, and IEEE disk drives.
- PCB rev D design included.
- Release binaries
