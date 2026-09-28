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
Twelve are now **FIXED** (1, 3, 4, 5, 6, 8, 9, 11, 14, 16, 17, 18), two are **NOT
A BUG** (2 and 7), one is **PARTIAL** (12) and five are **OPEN** (10, 13, 15, 19,
20).

**Issues 1 and 5 are closed.** `init()` now reads the EEPROM channel into a
`uint8_t` and range-checks it *before* casting to `int8_t`, so a corrupt byte can
no longer index `channel_attenuation[]` out of bounds. The clamp is not optional
polish — with `channel` as an `int8_t`, a stored `255` would cast to `-1` and
index `channel_attenuation[-1]`.

`channel` and `attenuation` are `int8_t` in `Instance_t`, so every ISR/main-loop
access to them is a single atomic byte access. `press` is handed off from the ISR
with a `press_pending` flag, and the main loop must never write `press` — it is
the producer's field exclusively. There are no genuinely 16-bit shared fields
left; `press` and `control` were never 2 bytes to begin with.

Nine further notes worth knowing before editing:

- **XC8 v4.00 does narrow enums to 1 byte here** (`sizeof(enum ButtonPress) == 1`).
  An earlier version of the README claimed 2 and built a whole analysis on it;
  that claim is retracted. Do not assume an enum field is 16-bit on this
  toolchain — measure with a one-object link and read the section size from the
  map if it matters. `int` is 2, `bool` is 1, `sizeof(Instance_t)` is 65, and
  XC8 does not pad structs.
- **Every function has a real prototype.** All of them take `(void)` rather than
  `()`, so the compiler type-checks every call. Issue 14 was the last holdout
  (`factory_reset`); keeping this true is what keeps the build free of
  `(1518) incomplete prototype` warnings.
- **The `.map` size columns are hexadecimal, not word counts.** `main` appears
  as `0x102` there, i.e. 258 words. Do not paste those strings into a table of
  sizes without converting.
- **Do not "fix" the `(10us)` comment** at `irq_routines.c:250`, inside
  `encoder_timer_callback()`. It looks stale — the tick is really 1 ms — but it
  is intentional: it documents the `#if 0 led_toggel()` measurement scaffolding
  that still brackets the ISR entry and exit points (`:241`, `:252`, `:260`,
  `:264`), and that harness is still in the file. This was issue 7; it is now
  recorded as NOT A BUG, not OPEN.
- **Drive the relays through `LATx`, never `PORTx`.** `TRISB = 0xD0`, so
  RB4/RB6/RB7 are inputs on the same port. A `PORTB` read-modify-write reads the
  *pin* level on those bits and latches it into the output latch, so every
  whole-register write that touches `RB0`–`RB3` must go through `LATB`. This was
  issue 8; all channel-select writes in `init()` and `process_channel()` are now
  `LATB`, including the two in the `#if 0` branch. `configure_attenuation()` was
  later moved to `LATA` as well for the same discipline. Note the difference in
  how load-bearing each case is: on `PORTB` this was a real bug, because three
  bits on that port are inputs. On `PORTA` it is only consistency —
  `TRISA = 0x0` makes all eight RA pins outputs, so pin level equals latch level
  and `PORTA` reads correctly. `init()` was converted as well, which mattered
  slightly more there: `~ROTARY_MAX_ATTENUATION` is `0xC0`, so that line
  *preserves* RA6/RA7 rather than forcing them low — the spare relays only end up
  de-energised because `pins.c` clears `LATA = 0x0` first. Reading the latch
  states the intent instead of relying on startup order. The only `PORTA` use left
  is the whole-register write in `process_channel()`. Either way `PORTx` and `LATx` share a write path, so a `LATx`
  conversion is always size-neutral — only the read side differs.
- **Never cast `volatile` away to satisfy a signature — make the signature
  honest instead.** `instance` is a `volatile Instance_t`, so
  `&instance.encoder[…].button` is a `volatile Button_t *` and passes to a
  `volatile Button_t *` parameter implicitly. The three `(Button_t *)` casts at
  the `button_fsm()` call sites existed only because the parameter was plain
  (issue 18). Adding a qualifier is a valid implicit conversion in C, so taking
  the volatile pointer is usually free; on this part it cost 4 words.
- **Only sleep after you actually switch a relay.** `RELAIS_MAX_SETUP_TIME` is the
  G6K-2F settling time, so it belongs *inside* the branch that drives the pin.
  `configure_attenuation()` used to sleep for every bit that differed even in the
  make-before-break phase that deliberately does nothing to it — half of all
  relay delays were no-ops. Worst case is now 18 ms for a sweep and 24 ms for a
  channel change (was 36/42). If you add a relay step, put the delay in the
  acting branch, not around it.
- `irq_routines.c` is the 1ms tick, so anything added there runs in an ISR —
  no `__delay_ms()`, no blocking calls. The relay delays in
  `control_routines.c` do block: up to 18 ms for an attenuation sweep and 24 ms
  for a channel change, which is issue 12 and still PARTIAL.
- `rotary_encoder.c` emits 2 events per detent (half-step table), which is why
  `ROTARY_MULTI_CHANNEL` is 3 and the channel selector feels non-linear. The
  fix is in issue 13.
