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

The project requires:
- MPLAB X IDE v6.30+ installed at `/Applications/microchip/mplabx/v6.30/`
- XC8 compiler v3.10+ at `/Applications/microchip/xc8/v3.10/`
- PIC16F1xxxx DFP pack

## Architecture Overview

This is embedded firmware for a 4-channel input selector with programmable attenuator controlled by rotary encoders and IR remote.

### Core Modules

- **main.c** - Application entry point, initializes system, timers, interrupts, and runs main loop (1ms cycle)
- **control_routines.c/h** - High-level control logic for channel selection, attenuation, encoder button handling, EEPROM save, and IR processing
- **irq_routines.c/h** - Interrupt service routines for rotary encoders and IR timer
- **rotary_encoder.c/h** - Quadrature encoder decoding and button press detection (single, double, long press)
- **irmp/** - IR remote control library (IRMP) supporting RC5 protocol

### Key Design Patterns

- **State machine in Instance_t** (`definitions.h`) - Single volatile struct holds all runtime state including channel/attenuation per channel, encoder states, save modes
- **Timer-based IRQ** - TMR0 for encoder polling, TMR2 for IR sampling
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
