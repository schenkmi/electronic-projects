# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands

This is an MPLAB X IDE project for PIC16F18056 microcontroller using XC8 compiler.

```bash
# Build the project (production)
make build CONF=default

# Clean build artifacts
make clean CONF=default

# Full rebuild
make clobber CONF=default && make build CONF=default
```

The project requires (currently configured — see `nbproject/private/configurations.xml`):
- MPLAB X IDE v6.35 at `/Applications/microchip/mplabx/v6.35/`
- XC8 compiler v4.00 at `/Applications/microchip/xc8/v4.00/`
- PIC16F1xxxx DFP pack 1.31.465

Code sizes and memory usage quoted in the documentation were measured with this
toolchain and will shift if the compiler version changes.

## Architecture Overview

This is embedded firmware for a 4-channel input selector with programmable attenuator controlled by rotary encoders and IR remote.

### Core Modules

- **main.c** - Application entry point, initializes system, timers, interrupts, and runs main loop (1ms cycle)
- **control_routines.c/h** - High-level control logic for channel selection, attenuation, encoder button handling, EEPROM save, and IR processing
- **irq_routines.c/h** - Interrupt service routines for rotary encoders (TMR0, 1ms) and IR sampling (TMR2, 66us); also holds `button_fsm()` for single/double/long press detection
- **rotary_encoder.c/h** - Table-driven quadrature decoding only (no button logic)
- **irmp/** - IR remote control library (IRMP) supporting RC5 protocol

For a full architecture walkthrough, hardware pin map, per-module explanation and
a status-tracked list of known bugs, see `../README.md`.

### Key Design Patterns

- **State machine in Instance_t** (`definitions.h`) - Single volatile struct holds all runtime state including channel/attenuation per channel, encoder states, save modes
- **Timer-based IRQ** - TMR0 at 1ms (encoder detent counting + button FSM), TMR2 at 66us / 15.151 kHz (IR sampling, required by IRMP)
- **EEPROM persistence** - Channel selection and default attenuation per channel stored in EEPROM; auto-save with 1s cooldown
- **Make-before-break relay control** - `ATT_CTRL_MAKE_BEFORE_BREAK` algorithm prevents audio pops during attenuation changes

### Configuration

Key constants in `definitions.h`:
- `ROTARY_MAX_CHANNEL` = 3 (4 channels: 0-3)
- `ROTARY_MAX_ATTENUATION` = 63 (6-bit, 0-63 steps)
- `IR_PROTOCOL` = RC5
- `ATT_CTRL` - Select relay control algorithm

### Main Loop Flow

```
init() → irmp_init() → while(1):
  process_ir() → handle remote commands
  process_channel() → update channel selection
  process_attenuation() → update attenuation with relay timing
  process_encoder_button() → handle single/double/long press
  eeprom_save_status() → persist changes with cooldown
```

## Known Issues

`../README.md` section 17 tracks 20 items with OPEN / PARTIAL / FIXED / NOT A BUG
status. Check it before changing anything, and update the status if you fix one.

The one bug with a severe consequence is **issue 1**: `init()` reads the channel
from EEPROM without range-checking it, so a corrupt value indexes
`channel_attenuation[]` (4 elements) out of bounds. It is a one-line clamp.

**Issue 5 is PARTIAL.** The `press` hand-off is now a `press_pending` handshake
and the lost-press / double-read defects are closed. What is still open is
narrower than the original write-up suggested: only `attenuation` and `channel`
are genuinely 16-bit shared fields, so shrinking those two to `int8_t` is all
that remains. `press` and `control` were never 2 bytes.

Three further notes worth knowing before editing:

- **XC8 v4.00 does narrow enums to 1 byte here** (`sizeof(enum ButtonPress) == 1`).
  An earlier version of the README claimed 2 and built a whole analysis on it;
  that claim is retracted. Do not assume an enum field is 16-bit on this
  toolchain — measure with a one-object link and read the section size from the
  map if it matters. `int` is 2, `bool` is 1, `sizeof(Instance_t)` is 69, and
  XC8 does not pad structs.
- `irq_routines.c` is the 1ms tick, so anything added there runs in an ISR —
  no `__delay_ms()`, no blocking calls. The relay delays in
  `control_routines.c` do block, for up to ~36ms.
- `rotary_encoder.c` emits 2 events per detent (half-step table), which is why
  `ROTARY_MULTI_CHANNEL` is 3 and the channel selector feels non-linear. The
  fix is in issue 13.
