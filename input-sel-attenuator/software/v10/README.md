# V9 Firmware — Input Selector + Programmable Attenuator

Firmware for a PIC16F18056 based 4-channel input selector with a relay-controlled
digital attenuator. Controlled by rotary encoders (one or two) and an RC5 IR remote.

The MPLAB X project itself lives in [`input-sel-attenuator.X/`](input-sel-attenuator.X/),
which also carries a topic-by-topic reference
([`input-sel-attenuator.X/README.md`](input-sel-attenuator.X/README.md)).
This document describes **how the code is structured and how it executes**.

---

## Table of contents

1. [Feature summary](#1-feature-summary)
2. [Directory layout](#2-directory-layout)
3. [Building](#3-building)
4. [Hardware interface](#4-hardware-interface)
5. [Timing and interrupts](#5-timing-and-interrupts)
6. [Runtime state model](#6-runtime-state-model)
7. [Boot sequence](#7-boot-sequence)
8. [Main loop](#8-main-loop)
9. [Rotary encoder decoding](#9-rotary-encoder-decoding)
10. [Push button state machine](#10-push-button-state-machine)
11. [Attenuator control](#11-attenuator-control)
12. [Channel selection](#12-channel-selection)
13. [Persistence (EEPROM)](#13-persistence-eeprom)
14. [IR remote control (IRMP)](#14-ir-remote-control-irmp)
15. [Encoder modes](#15-encoder-modes)
16. [Configuration reference](#16-configuration-reference)
17. [Known issues and caveats](#17-known-issues-and-caveats)
18. [Possible next steps](#18-possible-next-steps)

---

## 1. Feature summary

| Feature | Detail |
|---|---|
| Channel selection | 4 channels, one-hot relay outputs on RB0–RB3 |
| Attenuation | 6-bit (0–63) relay ladder on RA0–RA5, 1.5 dB/step, 0–94.5 dB |
| Pop-free attenuation | Make-before-break relay sequencing (default) |
| Pop-free channel change | Mute (max attenuation) → switch relays → restore attenuation |
| Per-channel volume | Each channel remembers its own attenuation; default stored in EEPROM |
| Encoders | 1 or 2 rotary encoders with push button, quadrature decoded in software |
| Button gestures | Single press, double press, long press (1 s), all non-blocking |
| IR remote | RC5, One For All Contour 8 / Hitachi 2676 code set |
| Persistence | EEPROM with 1 s debounce and read-before-write wear protection |
| Factory reset | Hold the channel encoder button during power-up |

### Version history (from `main.c` header)

```
V2.6  2026.09.25  Various corrections and optimizations
V2.5  2025.09.12  Shiny new push button and saving handling
                  Use volume when doing channel switch.
V2.4  2025.03.30  Fix missing __EEPROM_DATA
V2.3  2025.03.29  Implement make before break algorithm to control the attenuator relay
V2.2  2025.03.26  Improve detection of attenuation inc/dec for relay control
V2.1  2025.03.22  Little bit of cleanup
V2.0  2025.02.15  Add support for IR control (IRMP)
V1.5  2024.06.01  Add delay between SYSTEM_Initialize and factory reset
V1.4  2024.05.26  New MCC, factory reset
V1.3  2023.12.16  Improve usability
V1.2  2023.12.13  Set attenuator to maximum in init()
V1.1  2022.10.30  Implement default attenuation which can be set by pressing
                  encoder button for > 3 seconds
```

This is software revision **v10**, kept in step with the `V2.6` entry above. The
`main.c` header is the authoritative copy; keep the two in sync.

#### What V2.6 covers

The `main.c` entry says only "Various corrections and optimizations". The
substance is the audit in [section 17](#17-known-issues-and-caveats), which now
has **14 of 20 items fixed**, 2 confirmed not bugs, 1 partial and 3 open. The
changes that alter behaviour or resource use:

**Correctness**

- **The encoder step divider keeps its remainder and no longer resets on
  reversal** (13). Reversing the knob used to throw away up to `MULTI−1` clicks
  of travel every time — 13 111 of 20 000 randomised multi-reversal sequences
  lost travel. `ROTARY_MULTI_CHANNEL 3` and `ROTARY_MULTI_ATTENUATION 1` are
  unchanged and correct for the fitted encoder.
- **The EEPROM channel is range-checked before it indexes
  `channel_attenuation[]`**, and `channel` / `attenuation` are `int8_t`, so the
  TMR0 ISR can no longer tear them (1, 5). Worth −175 program words on its own.
- **Relay writes go through `LATB` / `LATA`, never `PORTB` / `PORTA`** (8). On
  `PORTB` this was a live bug: `TRISB = 0xD0` puts RB4/RB6/RB7 in the same port
  as the channel relays, so a read-modify-write latched the *pin* level of the
  input bits into the output latch.
- **`irmp_get_data()` is handed a non-volatile local** rather than a
  cast-stripped pointer (15). The project builds with `-maddrqual=ignore`, so
  nothing in the build would ever have caught that cast. The 6-byte `IR_t`
  member it fed turned out to be written once and never read, so it is gone.
- Smaller fixes: the `save_mode` index on channel change (3), the unreachable
  `Single`-mode channel-select path (4), `press` handed from the ISR instead of
  raced (5), button-FSM duplication and its dead `#else` copies (11, 16, 17, 18),
  the `factory_reset` prototype (14), a dead constant (6), and `process_ir()`
  keeping `volatile` (9).

**Resource use**

| | before V2.6 | after |
|---|---|---|
| Program memory | 4290 words (26.2 %) | **4157 words (25.4 %)** |
| Data memory | 181 bytes (8.8 %) | **175 bytes (8.5 %)** |
| `sizeof(Instance_t)` | 65 | **59** |

**Partly addressed:** the main loop still blocks on relay settling, but only
after a relay actually changes — worst case 42 → 24 ms (12, still PARTIAL).

**Two documentation corrections**, because both were previously wrong and both
affect how the hardware is read:

- The attenuator is **1.5 dB per step**, so the 6-bit ladder spans **0–94.5 dB**
  and the MSB relay is 48 dB — not 0.75 dB per step / 0–63 dB / 24 dB.
- The fitted PEC11R-4220F-S0012 has **24 detents at 12 pulses per revolution**,
  not 12 detents. With `ENABLE_HALF_STEP` that makes the decoder emit exactly
  **one event per detent**, so `ROTARY_MULTI_*` counts clicks directly. The
  earlier "odd multipliers land between detents" analysis, and the 6 / 2
  multipliers derived from it, were both based on the wrong detent count.

**Still open:** IR-initiated changes are never persisted (10), `Single` mode has
no gesture to store a default attenuation (19), and the volume/channel toggle has
no user-visible feedback (20).

---

## 2. Directory layout

```
software/v9/
├── README.md                       ← this file
└── input-sel-attenuator.X/         ← MPLAB X project (build here)
    ├── Makefile                    MPLAB X generated make wrapper
    ├── CLAUDE.md                   build instructions / architecture notes
    ├── README.md                   per-topic implementation reference
    ├── main.c                      entry point, global state, main loop
    ├── definitions.h               configuration constants + Instance_t
    ├── control_routines.c/.h       high-level control logic (relays, EEPROM, IR)
    ├── irq_routines.c/.h           TMR0/TMR2 interrupt handlers
    ├── rotary_encoder.c/.h         quadrature decoder (state table)
    ├── irmp/                       vendored IRMP IR decoder library
    │   ├── irmp.c/.h
    │   ├── irmpconfig.h            protocol selection, IR pin, F_INTERRUPTS
    │   ├── irmpprotocols.h         protocol IDs and timing constants
    │   ├── irmpsystem.h
    │   └── irmpextlog.c/.h
    ├── mcc_generated_files/        Microchip Code Configurator output
    │   ├── system/                 clock, config bits, pins, interrupts
    │   └── timer/                  tmr0.c, tmr2.c
    ├── input-sel-attenuator.mc3    MCC project (pin/timer configuration)
    ├── nbproject/                  MPLAB X build metadata
    ├── build/, dist/, _build/      build artifacts (not source)
    └── cmake/                      MPLAB X generated
```

### File responsibilities at a glance

| File | Responsibility |
|---|---|
| `main.c` | `__EEPROM_DATA` defaults, global `instance`, `main()`, 1 ms super-loop |
| `definitions.h` | All tunables, enums, and the single shared state struct |
| `control_routines.c` | Relay sequencing, channel/attenuation state machine, EEPROM save policy, button event handling, IR command decode |
| `irq_routines.c` | 1 ms TMR0 tick: encoder detent counting, button FSM; 66 µs TMR2 tick: `irmp_ISR()` |
| `rotary_encoder.c` | Half-step quadrature state table and per-encoder read functions |
| `irmp/` | Third-party multi-protocol IR decoder (RC5 enabled) |

---

## 3. Building

Requires MPLAB X IDE v6.30+ and XC8 compiler v3.10+ plus the PIC16F1xxxx DFP.
The project is currently configured for **MPLAB X v6.35 / XC8 v4.00** (see
`nbproject/private/configurations.xml`); the code sizes below are from that
toolchain and will shift if you change compiler version.

```bash
cd input-sel-attenuator.X
make build CONF=default        # production build
make clean CONF=default        # remove objects
make clobber CONF=default && make build CONF=default   # full rebuild
```

Artifacts:

- `dist/default/production/input-sel-attenuator.X.production.hex` — firmware image
- `dist/default/production/input-sel-attenuator.X.production.map` — memory map

Per-function code sizes and memory usage, from a production build with
**XC8 v4.00** (PIC16F18056, `-O2`). Figures are the `Size` column of
`input-sel-attenuator.X.production.map`, in **decimal words**, and have been
cross-checked against the `_function` / `__end_of_function` address pairs in the
listing.

| Module / function | Words | Source |
|---|---|---|
| `irmp/irmp.c` (whole module) | 1532 | `irmp/irmp.c` |
| `control_routines.c` (whole module) | 1207 | — |
| `irq_routines.c` (whole module) | 639 | — |
| `eeprom_save_status` | 205 | `control_routines.c:241` |
| `process_ir` | 166 | `control_routines.c:336` |
| `process_channel` | 197 | `control_routines.c:200` |
| `process_encoder_button` | 189 | `control_routines.c:275` |
| `button_fsm` | 174 | `irq_routines.c:37` |
| `timer_callback_process_single` | 181 | `irq_routines.c:173` |
| `init` | 172 | `control_routines.c:48` |
| `timer_callback_process_dual` | 172 | `irq_routines.c:105` |
| `configure_attenuation` | 140 | `control_routines.c:106` |
| `main` | 102 | `main.c:123` |
| `encoder_steps` | 100 | `irq_routines.c:88` |
| `factory_reset` | 95 | `control_routines.c:85` |
| `process_attenuation` | 34 | `control_routines.c:189` |
| `encoder_timer_callback` | 9 | `irq_routines.c:228` |
| `led_callback` | 9 | `control_routines.c:39` |
| `ir_timer_callback` | 3 | `irq_routines.c:247` |
| **Program memory** | **4157 / 16384 (25.4 %)** | |
| **Data memory** | **175 / 2048 (8.5 %)** | |

Summing every project translation unit in the map (the 16 rows above are the
largest; there are 37 functions in all) gives 3791 of the 4157 words. The
remaining 366 are not project logic:

| Component | Words |
|---|---|
| Project code, all 37 functions | 3791 |
| XC8 library: `__eeread.c`, `__eewrite.c`, `memcpy.c` | 84 |
| `shared`: `__initialization` + the IRMP `STRCODE` protocol tables | 199 |
| Residual, by subtraction — reset/interrupt vectors, psect alignment padding, and C-runtime helpers the map does not list | 83 |
| **Program memory** | **4157** |

The library and `shared` rows are stable at 84 and 199 across builds; the
project and residual rows move with the code. Both are derived from the map's
per-module `estimated size` lines, which sum per translation unit and so do not
double-count the way a mix of module rows and function rows would.

`led_toggel` is absent because the linker discarded it; it is never called, which
is the deliberate issue 7 scaffolding.

The `Cost` figures inside the individual issue entries further down are
point-in-time measurements taken when that fix was made. They are meaningful as
deltas, but several were taken before the accounting method above was settled, so
their absolute values lag the current build. Where an entry contradicts this
table, this table wins.

An earlier revision of this table published much larger per-function figures
(`process_ir` 530, `button_fsm` 372, `main` 258, and so on) that do not match any
current build, and described the map's size column as hexadecimal. It is decimal
words; the figures above are what the current map actually reports.

Flash and RAM headroom is ample — neither is a design constraint on this part.

**Reading the map file.** The `Link` and `Load` columns in the `.map` are
hexadecimal word addresses, but the per-function `Size` column is **decimal
words** — `main` reads `Size 102` at address `0x0AA2`, and 102 is also the
`main.c estimated size:` the linker prints for that file. `estimated size` is a
per-file sum of its functions and does not include the C runtime, startup code,
or `STRCODE` data, which is why the file totals do not add up to the program
total.

---

## 4. Hardware interface

Pin directions come from the MCC output (`mcc_generated_files/system/src/pins.c:51`):

```c
TRISA = 0x00;   // RA0..RA7 all outputs
TRISB = 0xD0;   // RB0..RB4 outputs, RB5..RB7 inputs
TRISC = 0xFF;   // all encoder / switch inputs
```

| Function | Pins | Direction | Notes |
|---|---|---|---|
| Attenuator relays (binary weighted) | RA0–RA5 | out | `1` = relay closed = ladder branch inserted |
| Channel select relays (one-hot) | RB0–RB3 | out | exactly one of the four is high |
| Status LED | RB5 | out | active **low** (`LED_SetHigh()` = off) |
| IR receiver input | RB4 | in | `IRMP_PIN` for XC8, internal pull-up enabled |
| Encoder 1 A / B / SW | RC0 / RC1 / RC2 | in | pull-ups enabled |
| Encoder 2 A / B / SW | RC5 / RC6 / RC7 | in | pull-ups enabled |

`ANSELB = 0xC0` disables analog on RB6/RB7 (unused). `WPUB = 0x10` enables the
pull-up on the IR input; `WPUC = 0xE7` enables pull-ups on all encoder pins, so
`ENC*SWITCH_GetValue()` reads `1` when the button is open and `0` when pressed —
this is what makes `factory_reset()` safe to call with no board attached.

Clocking (`mcc_generated_files/system/src/config_bits.c`): internal HFINTOSC,
**FOSC = 2 MHz**, WDT off, BOR on (1.9 V), PWRT 64 ms, LVP on.

---

## 5. Timing and interrupts

Two timer interrupts, both registered in `main()` via the MCC callback API:

| Timer | Period | Callback | Job |
|---|---|---|---|
| TMR0 | **1 ms** (`TMR0H = 0xF9`, HFINTOSC/128, 8-bit, count 250) | `encoder_timer_callback()` | encoder detent counting, button FSM, `ms_counter++` |
| TMR2 | **66 µs** (`T2PR = 0x20`, FOSC/4/16 = 31.25 kHz, ÷33) | `ir_timer_callback()` | `irmp_ISR()` — IRMP requires exactly 15 151 Hz |

`F_INTERRUPTS 15151` in `irmp/irmpconfig.h` matches the TMR2 rate; the library
must be sampled in a fixed 10–20 kHz window or decoding fails.

The main loop adds `__delay_ms(MAIN_LOOP_WAIT)` = 1 ms per iteration, so the
super-loop period is nominally 1 ms, **plus** whatever blocking time the relay
sequencing costs (see [Attenuator control](#11-attenuator-control)).

Design note: the only shared state between ISR and main loop is the single
`volatile Instance_t instance` global (`main.c:91`). No locking, no critical
sections — see [Known issues](#17-known-issues-and-caveats) for the races this
implies.

---

## 6. Runtime state model

All runtime state lives in one struct (`definitions.h:129`):

```c
typedef struct {
  enum Mode   mode;                      /* Single or Dual encoder            */
  enum SaveMode save_mode[2];            /* [0]=Volume, [1]=Channel           */
  uint8_t     save_action;               /* bitmask: SaveVolume|SaveChannel   */
  int         save_countdown_counter;    /* 1 s debounce, -1 = armed          */
  int8_t      channel;                   /* requested channel 0..3            */
  int8_t      last_channel;              /* applied channel, -1 = none yet    */
  int8_t      attenuation;               /* requested attenuation 0..63       */
  int8_t      last_attenuation;          /* applied attenuation, -1 = none    */
  ChannelVolume_t channel_attenuation[4];/* per-channel default + current     */
  volatile enum Control control;         /* which role the single encoder has */
  uint16_t    ms_counter;                /* free-running 1 ms tick            */
  RotaryEncoder_t encoder[2];            /* [0]=Volume/Combined, [1]=Channel  */
} Instance_t;
```

`channel` and `attenuation` are `int8_t` — single-byte, so the ISR's access to
them is one atomic access and cannot tear. They are *signed* because `-1` is the
"not set yet" sentinel. See issue 5. `save_countdown_counter` stays 16-bit
because it counts down from 1000.

Supporting types:

```c
typedef struct {                          /* rotary_encoder.c / definitions.h  */
  uint8_t direction;                      /* DIR_NONE | DIR_CW | DIR_CCW       */
  int     encoder_count[2];               /* per-role detent accumulator      */
  uint8_t rotary_encoder_state;           /* quadrature decoder state         */
  Button_t button;                        /* press FSM state                  */
} RotaryEncoder_t;

typedef struct {
  int default_attenuation;                /* EEPROM-persisted, applied on recall */
  int attenuation;                        /* current runtime value               */
} ChannelVolume_t;
```

The **requested vs. applied** split (`x` / `last_x`) is the core idiom: the ISR
and IR handler only ever mutate the *requested* value; the main loop compares the
pair and performs the actual, timed relay operation. This decouples fast input
events from slow, blocking hardware settling.

Enums (`definitions.h:82`):

```c
enum Control  { Combined = 0, Volume = 0, Channel = 1 };   /* Combined aliases Volume */
enum Mode     { Single = 0, Dual = 1 };
enum SaveMode { SaveNever = 0, SaveOnChange = 1, SaveOnLongPress = 2 };
enum ButtonPress { NoPress = 0, SinglePress = 1, DoublePress = 2, LongPress = 3 };
enum SaveAction   { NoSaveAction = 0, SaveVolume = 0x1, SaveChannel = 0x2 };
```

`Combined == Volume == 0` is intentional: single-encoder mode reuses
`encoder[0]` for both roles and switches roles via `instance.control`.

---

## 7. Boot sequence

`main()` (`main.c:123`) executes strictly in this order:

1. **`SYSTEM_Initialize()`** — MCC sets TRIS/ANSEL/LAT/WPU, config bits, TMR0, TMR2.
2. **`__delay_ms(STARTUP_WAIT)`** (250 ms) — let the supply and the
   reset-vector-defined pull-ups settle before probing the reset button.
3. **`factory_reset()`** (`control_routines.c:76`) — if `ENC2SWITCH` reads 0
   (button held at power-up), block until release, blink the LED 10×, then write
   factory defaults to EEPROM 0x00–0x04.
4. **Register ISR callbacks** — `TMR0_PeriodMatchCallbackRegister(encoder_timer_callback)`
   and `TMR2_PeriodMatchCallbackRegister(ir_timer_callback)`.
5. **`INTERRUPT_GlobalInterruptEnable()` / `INTERRUPT_PeripheralInterruptEnable()`**.
6. **`init(&instance)`** (`control_routines.c:48`):
   - LED off,
   - clear `CHAN_SEL_MASK` on PORTB, wait `RELAIS_MAX_SETUP_TIME` (3 ms),
   - force RA0–RA5 to `0x3F` (maximum attenuation),
   - **power-on relay self-test**: energise each channel relay in turn for 500 ms
     while muted, so a stuck relay is audible at startup,
   - read the last-used channel from EEPROM 0x04 into `instance->channel`,
   - read per-channel default attenuation from EEPROM 0x00–0x03 into both
     `default_attenuation` and `attenuation`.
7. **`irmp_init()`** and **`irmp_set_callback_ptr(led_callback)`** — the callback
   drives the LED for a visible blink on IR reception.
8. **Enter the super-loop.**

Because `last_channel` and `last_attenuation` are initialised to `-1`
(`main.c:96`), the first pass of `process_channel()` performs a full
mute → switch → restore cycle, and the `last_channel != -1` guards suppress any
EEPROM write on the first pass (nothing has changed yet, so nothing should be
saved).

---

## 8. Main loop

```c
while (1) {
  process_ir(&instance);             /* remote commands    */
  process_channel(&instance);        /* channel relays     */
  process_attenuation(&instance);    /* attenuation relays */
  process_encoder_button(&instance); /* button events      */
  eeprom_save_status(&instance);     /* deferred EEPROM    */
  __delay_ms(MAIN_LOOP_WAIT);        /* 1 ms               */
}
```

Order matters:

- `process_ir()` runs first so a remote command is folded into the same cycle's
  relay update.
- `process_channel()` before `process_attenuation()` because a channel change
  drives `instance->attenuation` itself; `process_attenuation()` then sees
  `attenuation == last_attenuation` and does nothing redundant.
- `process_encoder_button()` last among the consumers so button events are
  consumed and cleared after any state change they might cause has settled.
- `eeprom_save_status()` last: it consumes pending save flags armed earlier in
  the same cycle.

---

## 9. Rotary encoder decoding

`rotary_encoder.c` implements a table-driven **half-step** quadrature decoder
(`ENABLE_HALF_STEP` branch, `rotary_encoder.c:45`). The table is indexed by
`[current_state][pinstate]` and stores the next state in bits 0–2 plus an event
code in bits 4–5:

```c
#define R_START        0x0
#define R_CCW_BEGIN    0x1
#define R_CW_BEGIN     0x2
#define R_START_M      0x3      /* both lines high  */
#define R_CW_BEGIN_M   0x4
#define R_CCW_BEGIN_M  0x5

const unsigned char ttable[][4] = {
  /*            00           01           10           11          */
  {R_START_M,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},          /* R_START      */
  {R_START_M|DIR_CCW, R_START, R_CCW_BEGIN, R_START},          /* R_CCW_BEGIN  */
  {R_START_M|DIR_CW,  R_CW_BEGIN, R_START,    R_START},        /* R_CW_BEGIN   */
  {R_START_M,    R_CCW_BEGIN_M, R_CW_BEGIN_M, R_START},        /* R_START_M    */
  {R_START_M,    R_START_M,  R_CW_BEGIN_M, R_START|DIR_CW},    /* R_CW_BEGIN_M */
  {R_START_M,    R_CCW_BEGIN_M, R_START_M, R_START|DIR_CCW}    /* R_CCW_BEGIN_M*/
};
```

Reading an encoder is three lines (`rotary_encoder.c:97`):

```c
uint8_t encoder1_read(volatile uint8_t* rotary_encoder_state) {
  uint8_t pinstate = (ENC1CHANA_GetValue() << 1) | ENC1CHANB_GetValue();
  *rotary_encoder_state = ttable[*rotary_encoder_state & 0xf][pinstate];
  return (*rotary_encoder_state & 0x30);        /* DIR_NONE / DIR_CW / DIR_CCW */
}
```

The fitted encoders are **PEC11R-4220F-S0012**: 12 pulses (full quadrature
cycles) but **24 detents** per 360°, so 48 Gray edges and 24 detents per rev,
i.e. 2 edges per detent. The half-step variant emits on `00` and `11`, one event
every 2 edges, so it emits **exactly one event per detent** — and an event is
one mechanical click. Events, detents and clicks are the same unit on this part,
so the multipliers read directly as click counts:

```c
#define ROTARY_MULTI_CHANNEL       3   /* 1 channel change every 3 clicks */
#define ROTARY_MULTI_ATTENUATION   1   /* 1 attenuation step every click   */
```

That is 24 events/rev: 8 channel steps per revolution, and 24 attenuation steps
per revolution, i.e. 36 dB/rev and 2.6 revs across the full 0–94.5 dB range. The
full-step table would
emit 12 events/rev, one per 2 detents, and so would only step on every 2nd
click — half the requested resolution. See
[issue 13](#17-known-issues-and-caveats).

`encoder2_read()` (`rotary_encoder.c:110`) is identical apart from the pins. Both
are called from the 1 ms TMR0 callback. Sampling at 1 kHz is fast enough here:
the decoder consumes one edge per call, so at 48 edges/rev the first dropped
edge would need roughly **21 rev/s** (≈5 rev/s with a 4× safety margin) — an
order of magnitude beyond a hand-driven knob. The blocking `__delay_ms()` relay
delays are main-loop code and do not stop the TMR0 ISR, so they cost no encoder
events either.

**Detent accumulation** (`irq_routines.c:127`, `:156`, `:192`, `:206`, all via
`encoder_steps()` at `irq_routines.c:88`): CW/CCW increments/decrements the
accumulator, and `encoder_steps()` drains whole `ROTARY_MULTI_*` steps out of it
and leaves the remainder behind:

```c
static int8_t encoder_steps(volatile int *count, int8_t multi) {
  int8_t steps = 0;
  if (multi < 1) { return 0; }        /* 0 would spin the while forever */
  while (*count >=  multi) { *count -= multi; steps++; }
  while (*count <= -multi) { *count += multi; steps--; }
  return steps;
}
```

The accumulator is deliberately **not** zeroed, neither after a step nor on a
direction change. Zeroing it after a step discarded the remainder, and zeroing
it on a reversal threw away up to `MULTI−1` clicks of travel every time the knob
changed direction. The remainder is now carried, so travel is conserved across
reversals. See [issue 13](#17-known-issues-and-caveats).

Attenuation is deliberately **inverted** with respect to a volume control: CW
means *louder*, i.e. a smaller attenuation number. The value is then clamped —
attenuation saturates at 0/63, whereas channel wraps around 0↔3.

---

## 10. Push button state machine

Runs inside the 1 ms TMR0 callback; fully non-blocking, no `__delay_ms` in the
ISR. State per encoder (`definitions.h:109`–`:116`):

```c
typedef struct {
  bool   button_pressed;      /* level, valid while pressed            */
  bool   waiting_for_double;  /* short-click window open               */
  uint8_t click_count;        /* short clicks seen so far              */
  uint16_t press_time;        /* ms stamp at press edge                */
  uint16_t release_time;      /* ms stamp at release edge              */
  uint8_t press;              /* enum ButtonPress payload, set by ISR  */
  bool press_pending;         /* ISR -> main-loop hand-off flag        */
} Button_t;
```

`press` and `click_count` are explicit `uint8_t`, and `press_pending` is the
hand-off flag: the ISR writes `press` first and then sets the flag, and the main
loop clears the flag first and then reads `press`. The main loop must never write
`press` — it is the producer's field exclusively. See issue 5.

Thresholds (`definitions.h:61`):

```c
#define ROTARY_PUSH_DEBOUNCE_TIME       20    /* ms, minimum valid press  */
#define ROTARY_PUSH_LONG_PRESS_TIME   1000    /* ms, >= 1 s is a long press */
#define ROTARY_PUSH_DOUBLE_CLICK_TIME   500    /* ms, window for 2nd click  */
```

Algorithm — extracted into a single helper,
`button_fsm(uint16_t ms_counter, Button_t *button, uint_fast8_t pressed)` at
`irq_routines.c:37`, called once per encoder with the tick passed in as an
argument:

```
1. level 0 (pressed) and !button_pressed  → press_time = ms_counter, button_pressed = 1
2. level 1 (released) and button_pressed  → duration = ms_counter - press_time
                                            button_pressed = 0
     duration  <  20 ms                       → bounce, ignore
     duration  >= 1 s                          → press = LongPress, cancel window
     otherwise                                 → click_count++, release_time = now,
                                                waiting_for_double = 1
3. waiting_for_double && (ms_counter - release_time) > 500 ms
     click_count == 1 → press = SinglePress
     click_count == 2 → press = DoublePress
     reset click_count, close window
```

All three call sites use the helper, and the old inline copies have been deleted —
`irq_routines.c` contains no `#else` block any more:

| Call site | Encoder | Mode |
|---|---|---|
| `irq_routines.c:141` | 1 | Dual |
| `irq_routines.c:170` | 2 | Dual |
| `irq_routines.c:224` | 1 | Single |

Each call site reads the pin once into a local and casts the button pointer to a
non-volatile `Button_t *` — see issues 11, 16 and 17.

Consequences of this design:

- **Long press wins immediately** on release — no 1 s wait after the fact.
- **Single vs. double** is only decided 500 ms after the first release, so a
  single press has an inherent 500 ms response latency.
- `ms_counter` is a free-running `uint16_t` at 1 kHz (wraps every 65.5 s). All
  duration arithmetic is unsigned *subtraction* (`now - then`), which is
  wrap-around safe.
- `press` is the ISR→main-loop hand-off: `process_encoder_button()` reads it,
  acts, and writes it back to `NoPress`.

In dual mode only `LongPress` does anything (`control_routines.c:286`):
long-press on the volume encoder stores the current attenuation as the active
channel's default; long-press on the channel encoder stores the current channel
as the power-on channel. `SinglePress` and `DoublePress` are parsed and discarded.

In **single** mode the combined encoder uses `DoublePress` to switch the active
control (`control_routines.c:320`–`:325`): `control` flips between `Volume` and
`Channel`, and `timer_callback_process_single()` then applies the accumulated
detents to `encoder_count[control]`. `SinglePress` and `LongPress` are still
discarded — so in single mode there is no way to store a default at all (issue
19). The toggle has no LED or display feedback, so which function the knob is
currently driving is not visible to the user.

---

## 11. Attenuator control

The attenuator is a **binary-weighted relay ladder**: RA0 is the LSB (1.5 dB)
and each higher bit doubles, so RA1 = 3 dB, RA2 = 6 dB, RA3 = 12 dB, RA4 = 24 dB
and RA5 the MSB (48 dB), giving 0–**94.5 dB** (63 steps × 1.5 dB) in 1.5 dB
steps. The ladder code is a plain binary attenuation count, so code *n* is
*n* × 1.5 dB.

```c
#define ROTARY_ATTENUATION_BITS    6
#define ROTARY_MIN_ATTENUATION     0
#define ROTARY_MAX_ATTENUATION     ((1 << ROTARY_ATTENUATION_BITS) - 1)   /* 0x3F */
#define RELAIS_MAX_SETUP_TIME      3   /* ms, G6K-2F DC5 relay settling time */
```

The difficulty: changing N of 6 bits at once passes through intermediate
codes. `100000 → 011111` briefly becomes `000000` (a 48 dB jump) if the bits are
cleared before they are set — an audible pop. Two algorithms are implemented,
selected at compile time (`definitions.h:39`):

```c
#define ATT_CTRL_DIRECTION          1
#define ATT_CTRL_MAKE_BEFORE_BREAK  2
#define ATT_CTRL                    ATT_CTRL_MAKE_BEFORE_BREAK
```

### `ATT_CTRL_MAKE_BEFORE_BREAK` (active)

`configure_attenuation()` (`control_routines.c:152`) runs two passes:

```
Pass 1 — MAKE:  for each bit that must go 0 → 1, close the relay, 3 ms settle
Pass 2 — BREAK: for each bit that must go 1 → 0, open the relay,  3 ms settle
```

The transient code therefore always has a **bit count ≥ the larger of the two
codes**, i.e. attenuation is monotonically non-decreasing during the change and
never becomes *louder* than either endpoint. This is the correct invariant for an
attenuator: brief extra attenuation is inaudible, brief extra gain is not.

Worked example, `0b011111` → `0b100000` (quiet → loud):

```
pass 1: set RA5                      → 0b111111  (94.5 dB, no louder than target)
pass 2: clear RA0..RA4               → 0b100000  (48 dB, the requested value)
```

`0b100000` → `0b011111` (loud → quiet) is the mirror case: pass 1 sets RA0–RA4
first, reaching `0b111111` = 94.5 dB, and pass 2 then clears RA5 to land on
`0b011111` = 46.5 dB. It is quiet throughout the change and never louder than
either endpoint — same invariant, opposite direction of travel. (An earlier
version of this paragraph claimed the transient "never exceeds 48 dB"; that was
wrong, since the MAKE pass goes *up* to `0b111111` in both directions.)

### `ATT_CTRL_DIRECTION` (alternative, `control_routines.c:100`)

Walks the bits LSB→MSB when getting louder and MSB→LSB when getting quieter,
chosen from `instance->attenuation` vs. `instance->last_attenuation`. This
avoids the single worst intermediate code but not every intermediate value, so
it is noisier than make-before-break. It is retained for reference/comparison.

### Callers

- `process_attenuation()` (`control_routines.c:189`) — the normal path. Fires
  only when `attenuation != last_attenuation`, masks to 6 bits, calls
  `configure_attenuation()`, then latches `last_attenuation`.
- `process_channel()` (`control_routines.c:219, 227`) — calls it twice per
  channel change: once with `ROTARY_MAX_ATTENUATION` to mute, once with the new
  channel's stored attenuation to restore.
- `init()` — does not call it; it writes `LATA` directly to park the whole
  6-bit field at `ROTARY_MAX_ATTENUATION`. `~ROTARY_MAX_ATTENUATION` is `0xC0`,
  so this *preserves* whatever the spare `ATT6`/`ATT7` lines hold rather than
  forcing them low — they are low only because `PIN_MANAGER_Initialize()` cleared
  `LATA = 0x0` just before. Reading `LATA` rather than `PORTA` makes that
  dependency explicit: it preserves the commanded latch state, not the pin level.
  Not a mask bug — see the retracted
  [issue 2](#17-known-issues-and-caveats).

**Cost:** each relay that is actually switched costs 3 ms of blocking delay in
the main loop. Worst case (63 → 0 or 0 → 63) is 6 relays per pass and only one
pass does any work, so **6 delays = 18 ms** of stalled super-loop. This used to be
12 delays ≈ 36 ms: the delay was placed around the "does this bit differ" test
rather than inside the branch that switches the pin, so each pass also slept for
the bits it deliberately left alone. See [issue 12](#17-known-issues-and-caveats).

A channel change is worse than a sweep, because `process_channel()` mutes through
one and then waits again for the channel relay: 3 ms + 18 ms + 3 ms = **24 ms**.
The IR decoder (TMR2 IRQ) and the encoder tick (TMR0 IRQ) both keep running
throughout, so nothing is dropped — no other `process_*` step executes until the
window closes, which is added latency, not lost input.

---

## 12. Channel selection

RB0–RB3 drive four mutually exclusive channel relays; the code maintains a
one-hot pattern using `CHAN_SEL_MASK 0x0f`.

`process_channel()` (`control_routines.c:189`):

```
if (channel != last_channel):
    1. if last_channel != -1:  channel_attenuation[last_channel].attenuation = attenuation
                                (remember what the channel we are leaving was set to)
    2. configure_attenuation(0x3F)                       ← mute
    3. PORTB = (PORTB & ~0x0f) | (1 << channel)          ← switch relays
       __delay_ms(3)                                      ← relay settling
    4. attenuation = last_attenuation = channel_attenuation[channel].attenuation
    5. configure_attenuation(attenuation)                ← restore volume
    6. if last_channel != -1 and save_mode[Volume] == SaveOnChange:
           save_action |= SaveChannel; countdown = 1000
    7. last_channel = channel
```

Muting before the switch (rather than opening the relays) means the audio path is
never momentarily disconnected — only briefly attenuated, which the make-before-break
ramp makes a smooth 94.5 dB sweep rather than a click.

A `#if 0` block (`control_routines.c:206`) preserves the older strategy (break
the channel relays, restore attenuation, then re-select) for reference.

Because step 1 runs *before* the switch, the attenuation a channel is left at is
the live `instance->attenuation`, so per-channel volume is automatic: turn the
volume encoder while on channel 1, switch to channel 2, switch back, and channel 1
still has its setting. Only a **long press** writes it to EEPROM as the new
default for that channel.

Channel value wraps 0 → 3 → 0 (continuous rotary); attenuation clamps at 0/63.

---

## 13. Persistence (EEPROM)

`eeprom_read()` / `eeprom_write()` are XC8 built-ins declared by the PIC16F18056
device header. Factory contents come from the `__EEPROM_DATA` initializer in
`main.c:84`:

```c
__EEPROM_DATA(ROTARY_MAX_ATTENUATION,   /* 0x00 channel 0 attenuation */
              ROTARY_MAX_ATTENUATION,   /* 0x01 channel 1 attenuation */
              ROTARY_MAX_ATTENUATION,   /* 0x02 channel 2 attenuation */
              ROTARY_MAX_ATTENUATION,   /* 0x03 channel 3 attenuation */
              ROTARY_MIN_CHANNEL,       /* 0x04 last used channel     */
              0xff, 0xff, 0xff);
```

| Address | Content | Range |
|---|---|---|
| 0x00–0x03 | Per-channel default attenuation | 0–63 |
| 0x04 | Last used channel (`EEPROM_ADDR_CHANNEL`) | 0–3 |
| 0x05–0x07 | Unused padding | — |

### Save policy

`save_action` is a bitmask of pending writes, `save_countdown_counter` a 1 s
delay (`DEFAULT_SAVE_COUNTDOWN 1000` × 1 ms). `eeprom_save_status()`
(`control_routines.c:232`) implements three protections:

1. **Debounce** — while `save_countdown_counter > 0` it just decrements and
   returns, so a burst of adjustments collapses into a single write ~1 s after
   the last one.
2. **Read-compare** — each write is guarded by `if (eeprom_read(addr) != value)`,
   so an unchanged value is never rewritten. This is the main EEPROM wear
   defence (rated ~100 k cycles).
3. **Clear-then-write** — the action bit is cleared *before* the write, so a
   failed or long write cannot cause a retry storm.

Triggers:

| Trigger | Action | Condition |
|---|---|---|
| Long press, volume encoder | `SaveVolume` | `save_mode[Volume] == SaveOnLongPress` |
| Long press, channel encoder | `SaveChannel` | `save_mode[Channel] == SaveOnLongPress` |
| Channel change | `SaveChannel` | `save_mode[Volume] == SaveOnChange` ← see issue #3 |
| IR remote | *(none)* | IR volume changes are never persisted |

Both save modes default to `SaveOnLongPress` (`main.c:93`), i.e. volume/channel
memory is opt-in per gesture. The `mode == Single` branch of
`eeprom_save_status()` is empty.

---

## 14. IR remote control (IRMP)

The vendored **IRMP** library decodes IR frames on a fixed 15 151 Hz sample
interrupt. Configuration highlights (`irmp/irmpconfig.h`):

```c
#define F_INTERRUPTS        15151    /* required sample rate for XC8/C18 */
#define IRMP_USE_CALLBACK    1       /* drives led_callback()             */
#define IRMP_HIGH_ACTIVE     0       /* IR module output is low-active    */
#define IRMP_PIN             PORTBbits.RB4   /* XC8 branch, line 140       */
```

Enabled protocols: SIRCS, NEC, Samsung, Kaseikyo, **RC5**, RC6, Ruwido. Only
RC5 frames are *acted* on, but the others still cost flash.

Flow:

```
IR receiver (RB4)
   → TMR2 IRQ every 66 µs → irmp_ISR()      [irq_routines.c:252]
        measures pulse/space edges, matches RC5 Manchester timing (1.778 ms bit)
   → 1 ms main loop → process_ir()          [control_routines.c:336]
        irmp_get_data() → filter protocol + address → map command → clamp → store
   → process_channel() / process_attenuation() apply the new value
```

`process_ir()` only accepts `protocol == IRMP_RC5_PROTOCOL` and
`address == IR_REMOTE_ADDRESS (0x0001)`. Key codes are those of a One For All
Contour 8 (Hitachi 2676) remote (`definitions.h:68`):

| Key | Code | Action |
|---|---|---|
| `IR_KEY_1` … `IR_KEY_4` | 1–4 | direct channel select |
| `IR_KEY_CH_UP` / `CH_DOWN` | 32 / 33 | next / previous channel (wraps) |
| `IR_KEY_VOL_UP` | 16 | attenuation−1 (louder) |
| `IR_KEY_VOL_DOWN` | 17 | attenuation+1 (quieter) |
| `IR_KEY_OK` | 53 | reserved — no-op |
| `IR_KEY_MUTE` | 13 | reserved — no-op |

RC5 sets the **toggle bit** on every second press of the same key. The code
handles that by keying behaviour off `data.flags`: when `flags == 0x00` (a
normal press) the full key set is honoured; when the toggle bit is set only
volume up/down are accepted, which is what makes holding VOL+/VOL− repeat
smoothly. Channel keys are ignored on repeat so holding `1` cannot oscillate
between channel 1 and channel 2.

Channel wraps, attenuation clamps — the same rules as the encoders.

---

## 15. Encoder modes

`instance.mode` selects the TMR0 callback body
(`irq_routines.c:233`):

### `Dual` (default) — `timer_callback_process_dual()`

```
encoder 1 → attenuation  (button: long press = store default volume)
encoder 2 → channel      (button: long press = store default channel)
```

`instance.encoder[0]` and `[1]` are used independently; both `encoder_count[2]`
slots exist but only slot `[0]` of each encoder is used in this mode.

### `Single` — `timer_callback_process_single()`

One encoder drives both roles, selected by `instance.control`
(`enum Control`, which aliases `encoder[Combined] == encoder[Volume] == 0`):

```
instance.control == Volume  → encoder[0].encoder_count[0], adjusts attenuation
instance.control == Channel → encoder[0].encoder_count[1], adjusts channel
```

The `encoder_count[2]` array exists precisely so the two roles keep independent
detent accumulators while sharing one physical encoder. **Nothing in the current
code ever assigns `instance.control`** (see issue #4), so as shipped `Single`
mode only adjusts attenuation; the channel branch is unreachable.

---

## 16. Configuration reference

All in `definitions.h`:

| Constant | Value | Meaning |
|---|---|---|
| `ATT_CTRL` | `ATT_CTRL_MAKE_BEFORE_BREAK` | relay sequencing algorithm |
| `STARTUP_WAIT` | 250 | ms between `SYSTEM_Initialize()` and factory-reset probe |
| `CHAN_SEL_MASK` | `0x0f` | RB0–RB3 channel relay mask |
| `EEPROM_ADDR_CHANNEL` | `0x04` | EEPROM address of the last used channel |
| `ROTARY_MIN_CHANNEL` / `MAX_CHANNEL` | 0 / 3 | 4 channels |
| `ROTARY_MULTI_CHANNEL` | 3 | encoder events per channel step (chosen by feel) |
| `ROTARY_ATTENUATION_BITS` | 6 | ladder resolution |
| `ROTARY_MIN/MAX_ATTENUATION` | 0 / 63 | attenuation range |
| `ROTARY_MULTI_ATTENUATION` | 1 | encoder events per 1.5 dB step (chosen by feel) |
| `MAIN_LOOP_WAIT` | 1 | ms super-loop delay |
| `EEPROM_SAVE_STATUS_VALUE` | 1000 | *unused* (see issue #6) |
| `RELAIS_MAX_SETUP_TIME` | 3 | ms relay settling (G6K-2F DC5) |
| `ROTARY_PUSH_DEBOUNCE_TIME` | 20 | ms minimum press |
| `ROTARY_PUSH_LONG_PRESS_TIME` | 1000 | ms long press |
| `ROTARY_PUSH_DOUBLE_CLICK_TIME` | 500 | ms double-click window |
| `DEFAULT_SAVE_COUNTDOWN` | 1000 | 1 s EEPROM save debounce |
| `IR_PROTOCOL` | `IRMP_RC5_PROTOCOL` | accepted IR protocol |
| `IR_REMOTE_ADDRESS` | `0x0001` | accepted RC5 device address |

---

## 17. Known issues and caveats

Re-audited after the latest round of fixes. Each item is **OPEN**, **PARTIAL**
or **FIXED**. Of the twenty tracked items, fourteen are **FIXED** (1, 3, 4, 5, 6, 8,
9, 11, 13, 14, 15, 16, 17, 18), two are **NOT A BUG** (2 and 7), one is **PARTIAL**
(12) and three are **OPEN** (10, 19, 20).
Fixing 1 and 5 also forced a correction to the original analysis of issue 5: its
load-bearing `sizeof` measurement was wrong. See the retraction below and the
rewritten entry.

| # | Issue | Status |
|---|---|---|
| 1 | Unvalidated EEPROM channel → out-of-bounds `channel_attenuation[]` index | **FIXED** *(clamp added in `init()` — also required by the `int8_t channel` change, see below)* |
| 2 | ~~`init()` clears RA6/RA7~~ — **not a bug; verified** | **NOT A BUG** |
| 3 | Wrong `save_mode` index on channel change | **FIXED** |
| 4 | `Single` mode cannot select a channel | **FIXED** *(logic exists but is unreachable — see below)* |
| 5 | ISR → main-loop race on `press`; 16-bit shared fields | **FIXED** *(`press` hand-off added, then `attenuation` / `channel` narrowed to `int8_t`; program memory −175 words — see below)* |
| 6 | Dead constant `EEPROM_SAVE_STATUS_VALUE` | **FIXED** |
| 7 | ~~`"10 us"` comment on the 1 ms encoder callback~~ — **intentional; left as-is** | **NOT A BUG** |
| 8 | `PORTB` read-modify-write instead of `LATB` | **FIXED** *(four live writes, plus two in the `#if 0` branch, converted to `LATB`)* |
| 9 | `process_ir()` dropped `volatile` | **FIXED** |
| 10 | IR-initiated changes are never persisted | OPEN |
| 11 | Button FSM code duplication | **FIXED** *(dead copies deleted too — issue 17)* |
| 12 | Long blocking delays in the main loop | **PARTIAL** *(half the delays were no-ops and are gone; worst case 42 → 24 ms; loop still blocks)* |
| 13 | Non-linear channel selector on the encoder | **FIXED** *(cause was lost travel on reversal, not the multiplier: remainder now preserved and the direction-change reset removed; 3 / 1 unchanged and correct for this 12 PPR / 24 detent part)* |
| 14 | Incomplete prototype for `factory_reset()` | **FIXED** *(prototype now takes `(void)`)* |
| 15 | `irmp_get_data()` called through a cast that strips `volatile` | **FIXED** *(non-volatile local handed to the library, cast gone, and the dead 6-byte `IR_t` member deleted — 133 words and 6 bytes smaller overall)* |
| 16 | `button_fsm()` forces every field access through memory | **FIXED** |
| 17 | Dead `#else` button code in `irq_routines.c` | **FIXED** *(dead blocks and their `encN_pressed` temporaries are gone — see below)* |
| 18 | Call sites cast away `volatile` on the button pointer | **FIXED** *(helper takes `volatile Button_t *`, casts deleted)* |
| 19 | `Single` mode still has no way to store a default attenuation | OPEN |
| 20 | New control-toggle has no user-visible feedback | OPEN |

### Retracted claims

Four earlier statements in this document were wrong and are corrected here:

- **XC8 *does* narrow enums, and my `sizeof(enum …) == 2` measurement was
  wrong.** This was the load-bearing premise of the original issue 5 entry, and
  it does not hold for the current toolchain (XC8 v4.00). Measured by linking a
  one-object translation unit per type and reading the section size out of the
  link map:

  | Type | `sizeof` |
  |---|---|
  | `enum ButtonPress` | **1** |
  | `enum Control` | **1** |
  | `int` | 2 |
  | `bool` | 1 |
  | `Button_t` | 9 |
  | `RotaryEncoder_t` | 15 |
  | `ChannelVolume_t` | 4 |
  | `Instance_t` | 69 *(65 after the issue 5 fix, 59 after the issue 15 fix)* |

  The `Instance_t` figure cross-checks against the real build: `_instance` sits
  at `0xA0` in `dataBANK1` and the next object, `_xor_check`, started at `0xE5` —
  69 bytes, as measured before the fix. After the `int8_t` change `_xor_check`
  moved to `0xE1`, i.e. 65 bytes, which is exactly the four bytes saved on the
  four narrowed fields. It is now at `0xDB`, i.e. 59 bytes, after the issue 15 fix
  removed the dead 6-byte `IR_t` member. So `button.press` and `instance.control` were **always**
  single-byte objects, and every load and store of them was always one
  instruction. My claim
  that "XC8 does not narrow enums and the project does not pass `-fshort-enums`"
  described XC8 2.x behaviour; v4.00 is clang-based and does narrow, because all
  the enumerators here fit in one byte. `-fshort-enums` is neither needed nor
  present.

  Consequences, all of which are corrected in the rewritten issue 5 entry: the
  "torn read of `press`" defect could never occur; neither could the "torn index"
  on `control`; and the predicted RAM savings (`Button_t` 10 → 9, `Instance_t` −8)
  were wrong, because `Button_t` was *already* 9 bytes and `Instance_t` is
  **unchanged at 69**. XC8 also does not pad structs here — `Button_t`'s two
  `uint16_t` members are deliberately unaligned at offsets 3 and 5.
- **`save_countdown_counter` is NOT racy.** It was listed under issue 5. Its only
  writers are `control_routines.c:233`, `:288` and `:306` — all main-loop
  context. The TMR0 ISR never touches it, so there is no race to fix.
- **Issue 13 was never about the sample rate.** See the rewritten entry below.
- **Issue 16 was fixed by the same change that fixed issue 15's class of
  problem, but in the opposite direction.** Passing `ms_counter` in and dropping
  `volatile` from the helper's pointer is the right call, yet the call sites then
  cast the volatile object back to a plain one — that was split out as its own
  item (18) and has since been closed by making the helper's parameter
  `volatile`, which costs 4 words and removes the casts.
- **Issue 2 is not a bug at all.** RA6/RA7 are not "unused" — they are
  `ATT6`/`ATT7`, the spare relay lines of an 8-bit attenuator this firmware does
  not implement, and `init()` parks them low deliberately. I also wrongly claimed
  `configure_attenuation()` disagreed with `init()`; it preserves RA6/RA7 and so
  agrees with it. The line needs a comment, not a change.
- **Issue 8 misidentified the code, twice.** There is no `PORTBbits.RB4 = …`
  anywhere; the IR path uses the `LATB`-based `LED_*` macros. The real
  observation is narrower — whole-register `PORTB` RMWs on a port that also
  carries input pins — and the channel-cycling loop is in `init()`, not
  `factory_reset()` as first written. Both errors are corrected in the rewritten
  entry, which is now in **FIXED**.

### Detail

#### OPEN

**10. IR-initiated changes are not persisted.** No `save_action` is armed from
`process_ir()`, so a volume change made with the remote is lost on power cycle.
Channel changes *are* saved, now correctly gated on `save_mode[Channel]` since
issue 3 was fixed. If "remote changes are temporary" is intentional it deserves a
comment; if not, `process_ir()` is missing a `save_action |= SaveVolume`.

**12. Long blocking delays in the main loop.** *PARTIAL: the worst case is
roughly halved, the blocking itself remains.* A pending IR command or button
event still waits for the relay sweep to finish, because unlike the encoder those
events are only consumed in the main loop. Two separate things were wrong here and
only one of them is fixed.

**Fixed: half the delays were pure waste.** In `configure_attenuation()`, both
phases of the make-before-break algorithm had `__delay_ms(RELAIS_MAX_SETUP_TIME)`
placed *outside* the `if` that actually switches the relay but *inside* the
"does this bit differ" test. So each mismatched bit slept 3 ms even in the phase
that deliberately does nothing to it — the make phase sleeps for bits that have to
go to 0, the break phase sleeps for bits that have to go to 1. The delay exists to
let a switched G6K-2F relay settle; when no relay was switched there is nothing to
settle. Simulating all 4096 possible transitions, **exactly 50 % of all relay
delays did nothing.**

| | before | after |
|---|---|---|
| attenuation change, worst case | 36 ms (12 delays) | **18 ms (6 delays)** |
| attenuation change, mean | 18 ms | **9 ms** |
| channel change, worst case | 42 ms | **24 ms** |

The delay is now inside the branch that drives the pin. The pin order and the 3 ms
spacing after each *actual* switch are unchanged, so the electrical behaviour is
identical — this only removes sleeping. It is size-neutral (4279 words before and
after, `control_routines.c` still 1253). Worth noting the sibling
`ATT_CTRL_DIRECTION` branch never had the bug: it sets and clears within the same
iteration, so its delay already followed a real switch.

**Corrected: the figure in the original entry was too low.** It quoted "~36 ms
during a 6-bit attenuation change" as the worst case, but a *channel* change is
worse, because `process_channel()` mutes through the same sweep and then waits
again for the channel relay: 3 ms mute + 36 ms sweep + 3 ms select = **42 ms**,
now 24 ms. And a third blocking source was missing from the entry entirely:
`eeprom_save_status()` calls `eeprom_write()` up to twice
(`control_routines.c:258`, `:267`), and a PIC16F18056 EEPROM write is several
milliseconds, so an EEPROM save can block the loop for roughly 6–10 ms on top of
whatever else is pending.

**Still open: the loop is blocked, and no events are lost because of it.** Worth
being precise about what the cost actually is. During the sweep the TMR0 1 ms ISR
and the TMR2 66 µs ISR both keep running, so encoder detents are still counted and
IR codes are still received into the IRMP buffers; the main loop just does not
*look* at them until the sweep ends. So this is added latency, not dropped input,
and a fast knob spin loses nothing — the ISR keeps counting and the latest
`attenuation` wins when the loop resumes. For a volume control, ~18–24 ms is
plausibly below the perceptual threshold, which is why this is not fixed outright.

The remaining fix is to pace the relay steps off the 1 ms tick instead of
sleeping: `instance.ms_counter` is already a free-running 1 ms counter incremented
by the TMR0 ISR, so `configure_attenuation()` can become a small state machine that
switches at most one relay per tick and returns immediately. That needs no ISR
changes at all, drops main-loop occupancy to microseconds and IR/button latency to
~1 ms, and would give the relay pins a single writer. It would **not** make the
transition itself faster — the relays still need their 18 ms of settling, because
that is physics, not code. It is also a rewrite of the sequencing on hardware
there is no bench to verify against, which is why it has not been done here
alongside a change that is provably behaviour-preserving.

It is worth doing separately, because it is also what would let `channel` and
`attenuation` widen back to 16 bit and retire the last-writer-wins caveat that the
issue 5 fix could not remove on its own.

**13. Non-linear channel selector — fixed. The cause was lost travel, not the
multiplier and not the sample rate.** *(This entry has been revised twice. The
first revision blamed the 1 ms polling interval; that was wrong. The second
blamed the multiplier for landing "between detents", on the assumption that the
encoder has 12 detents; that was also wrong — the fitted PEC11R-4220F-S0012 is
12 pulses but **24 detents** per 360°. With `ENABLE_HALF_STEP` the table already
emits exactly one event per detent, so the shipped multipliers 3 and 1 are the
requested feel and were always correct. The genuine defect is below.)*

The encoder produces 48 Gray edges and 24 detents per revolution, and the
half-step table emits 24 events/rev — one per detent, one per click. Sampling at
1 kHz does not drop any of them until roughly **21 rev/s** (≈5 rev/s with a 4×
safety margin), because the decoder consumes one edge per call and there are
only 48 edges/rev. The blocking relay delays are main-loop code that does not
stop the TMR0 ISR, so the sample rate was never the problem and has not been
changed.

The defect was *lost travel*, in two places, both fixed:

- `encoder_count[0] = 0` after each step discarded the remainder.
- `encoder_count[0] = 0` on direction change threw away up to `MULTI−1` clicks
  of travel every time the knob reversed. This was the larger of the two: a
  randomised harness of 20 000 multi-reversal sequences (multiplier drawn from
  1..6, 4..43 moves per sequence, a direction flip on roughly one move in four)
  loses travel in **13 111** of them, by up to `MULTI-1` = **5** clicks at
  `MULTI` = 6. The same harness against the new logic reports **0** violations:
  the conservation law `travel == steps*ROTARY_MULTI_* + remainder` holds
  exactly, with `|remainder| < MULTI`, in all 20 000 sequences.

An earlier claim in this entry that the `if`/`while` choice mattered was also
**wrong**. The decoder returns a single event per call, so the accumulator can
only move by one per 1 ms sample and can never exceed one threshold — a
randomised run never drove the accumulator past `MULTI`. The `while` is retained
as defensive coding, not because it fixed anything.

Changes, all in `irq_routines.c` and `rotary_encoder.c`:

- `rotary_encoder.c:45` — `ENABLE_HALF_STEP` stays `#if 1`. The comment now
  records the 12 PPR / 24 detent geometry, that this makes the table emit
  exactly 1 event per detent, and that events, detents and clicks are therefore
  the same unit for `ROTARY_MULTI_*`.
- `definitions.h` — the multipliers are **unchanged** at
  `ROTARY_MULTI_CHANNEL 3` and `ROTARY_MULTI_ATTENUATION 1`, which give a
  channel change every 3 clicks and an attenuation step on every click. An
  intermediate revision doubled both to 6 and 2 on the theory that odd
  multipliers cannot land on a detent boundary; that theory came from the wrong
  detent count, and the user also preferred 3 and 1 on the bench. Because one
  event is exactly one click here, the "odd multipliers land between detents"
  problem simply does not exist. The source comment and `CLAUDE.md` now state
  the geometry so the same wrong "correction" is not made again.
- New `encoder_steps()` helper (`irq_routines.c:88`) replaces the four
  duplicated threshold blocks. It returns whole steps, keeps the remainder, and
  guards `multi < 1` so a misconfigured `ROTARY_MULTI_*` of 0 cannot make the
  `while` spin forever inside the 1 ms ISR. The four call sites are otherwise
  unchanged in behaviour, and the clamp/wrap logic that follows them is untouched.
- The three direction-change resets are gone. `RotaryEncoder_t.direction` is now
  written but never read; it is kept because it is part of the public struct and
  is initialised in `main.c`, but it is informational only now.

Cost: program 4279 → **4290** words, data 180 → **181** bytes. No new compiler
warnings; the warnings are identical to the pre-fix baseline.

Verified by simulation over one full revolution of the real geometry
(24 detents, 12 quadrature cycles, 48 edges) with the `encoder_steps()` helper
copied verbatim from the ISR, at the multipliers the firmware ships with:

| `ROTARY_MULTI_*` | Clicks/step | Steps/rev | Detents/step | Edge spacing |
|---|---|---|---|---|
| **1** (attenuation, in use) | 1 | 23–24 | **1** | uniform 2 |
| **3** (channel, in use) | 3 | 7–8 | **3** | uniform 6 |
| 2 | 2 | 11–12 | 2 | uniform 4 |
| 6 | 6 | 3–4 | 6 | uniform 12 |

Event spacing is exactly uniform at every multiplier, including the shipped odd
ones: 2 edges per click, so 2 edges per attenuation step and 6 per channel step,
with no long-or-short gap. Steps therefore land **on** detent centres, one step
every 1 click and one every 3 clicks. The 23-vs-24 in the step counts is the
expected one-event offset at the wrap: a revolution from `R_START` needs the
decoder to see the `00`/`11` state before it emits, so the boundary event falls
on the next revolution. It is a startup-phase artifact, not per-click jitter.

**Feel, as verified on the real encoder.** The attenuator steps once per click
and the channel selector once every three clicks. `ROTARY_MAX_CHANNEL` is 3, so
the channel knob passes all four channels about twice per revolution;
`ROTARY_MAX_ATTENUATION` is 63, so the attenuator needs 2.6 revolutions to sweep
its full range. The half-step table is what makes those two ratios feel the way
they do — the full-step table would halve both. See
[Rotary encoder decoding](#9-rotary-encoder-decoding).

**15. `irmp_get_data()` called through a cast that strips `volatile`. — FIXED.**
`process_ir()` is correctly declared `void process_ir(volatile Instance_t *instance)`
(`control_routines.c:336`), and the cast it used was

```c
if (irmp_get_data((IRMP_DATA *)&instance->ir.data)) {
```

`irmp_get_data()` takes a plain `IRMP_DATA *` (`irmp/irmp.h:305`), so handing it a
`volatile IRMP_DATA *` needs a cast, and that cast discarded the qualifier and
let the compiler cache `ir.data` across the call. It only compiles because the
project passes `-maddrqual=ignore` — present on both the production and the
debug compile line in `nbproject/Makefile-default.mk`. So the build will never
warn about this class of bug on its own.

Two things were wrong, not one. The cast, and the fact that the frame was being
stored in `Instance_t` at all.

**The cast.** The library now gets a non-volatile local, and the fields are read
from it so the compiler keeps them in registers instead of reloading memory:

```c
IRMP_DATA ir;

if (irmp_get_data(&ir)) {
  if (ir.protocol == IR_PROTOCOL && ir.address == IR_REMOTE_ADDRESS) {
    ...
    if (ir.flags == 0x00) { switch (ir.command) { ... } }
```

This is safe because `irmp_get_data()` assigns `protocol`, `address`, `command`
and `flags` together and only on the `TRUE` path (`irmp/irmp.c:2774`–`:2777`),
so `ir` is always fully initialised whenever it is read. No cast remains in the
file.

**The dead member.** `Instance_t` carried an `IR_t ir;` field whose only content
was that one `IRMP_DATA`, and the *only* thing the firmware ever did with it was
write it — `process_ir()` read the fields back out of the same non-volatile copy
it had just written, and nothing anywhere else in the project referenced it. It
was dead state costing 6 bytes of RAM, so the `IR_t` typedef and the member are
both gone. The last thing keeping it alive was a comment calling it a "last
decoded IRMP_DATA" record, which is a debugging nicety, not a requirement; if
frame-level IR debugging is ever wanted, a breakpoint in `process_ir()` shows
the same thing without permanent state.

Cost, measured as three separate builds of the same tree:

| Build | Program | Data |
|---|---|---|
| A — original (cast, member present) | 4290 | 181 |
| B — cast removed, member kept | 4257 | 181 |
| C — cast removed, member removed (shipped) | **4157** | **175** |

So the cast alone is −33 words, and dropping the dead member is a further
−100 words and −6 bytes. The member removal is worth far more than the copy
it eliminated, and the reason is *not* the copy: shrinking `Instance_t` by 6
bytes re-encodes every field offset in every function that touches the struct, so
functions this change never went near got smaller too — `process_channel` 215
→ 197, `button_fsm` 192 → 174, `eeprom_save_status` 222 → 205,
`process_encoder_button` 199 → 189, `init` 176 → 172. `sizeof(Instance_t)`
goes 65 → 59. Anyone reading the per-function table should expect that kind of
churn from a struct-layout change and not attribute it to the logic that changed.

An earlier draft of this entry credited the fix with 3 words saved in
`irmp/irmp.c` and quoted `irmp_get_data` at 329 → 326. That was wrong: the
function was never edited, and its size moves with code layout — it reads 329
in build A, 326 in B and 329 again in C. Per-symbol sizes for code that sits near
a bank boundary are not a reliable measure of a source change; only the A/B/C
totals above are.

No compiler warnings changed, and every per-function figure in section 3 is from
the same build as the totals.
**19. `Single` mode still has no way to store a default attenuation.** In the
combined (single) branch of `process_encoder_button()` (`control_routines.c:315`),
`LongPress` falls straight through to `break` at `:328`, so no `save_action` is
ever armed. The corresponding branch in `eeprom_save_status()` (`:239`–`:263`)
performs no save for `mode != Dual` either. So the two mechanisms are consistent
with each other, but the user has no gesture that writes EEPROM in single mode.
If the point of `Single` mode is "one knob, everything on it", long-press to
store the current value is the obvious missing gesture.

**20. New control-toggle has no user-visible feedback.** The `DoublePress` handler
added at `control_routines.c:320`–`:325` flips `instance->control` between
`Volume` and `Channel`, which changes what the single encoder does. There is no
LED blink, no display and no beep — and the decision is only made 500 ms after the
second release, by which time the user has usually turned the knob already. A
brief LED indication on toggle would make the mode discoverable; without one the
knob appears to randomly control volume or channel. (Note that `IR_KEY_MUTE` is
already defined and unused, so a status LED is clearly intended at some point.)

#### RETRACTED

**2. ~~`init()` clears RA6/RA7.~~ — retracted, this is correct behaviour.**
I previously listed this as a bug and the reasoning was wrong in two ways.

`LATA = ((LATA & ~ROTARY_MAX_ATTENUATION) | ROTARY_MAX_ATTENUATION)`
(`control_routines.c:59`) masks with `~0x3F`, which drives RA6 and RA7 low. My
claim that this is "harmless only while RA6/RA7 are unused outputs" understated
it: RA6 and RA7 **are** allocated in the pin manager, as `ATT6` and `ATT7`
(`input-sel-attenuator.mc3`; `mcc_generated_files/system/pins.h:166`–`:197` generates the matching
`ATT6_*`/`ATT7_*` macros). They are digital outputs — `TRISA = 0x0` in
`mcc_generated_files/system/src/pins.c:51` makes all of PORTA an output — and
their initial level in MCC is LOW.

The firmware implements a **6-bit** attenuator: `ROTARY_ATTENUATION_BITS 6`
(`definitions.h:59`) gives `ROTARY_MAX_ATTENUATION = 0x3F` (`definitions.h:61`).
ATT6 and ATT7 are therefore spare relay lines for an 8-bit attenuator that this
firmware does not implement, and forcing them low in `init()` is the intended
behaviour: the two unused relays end up de-energised at power-up instead of
inheriting an indeterminate value. So the line is right.

Worth being precise about *why*, because it is easy to get backwards:
`~ROTARY_MAX_ATTENUATION` is `0xC0`, which **preserves** RA6/RA7 — it does not
force them low. They are low at power-up only because `PIN_MANAGER_Initialize()`
(`pins.c:43`) clears `LATA = 0x0` and `TRISA = 0x0` before `init()` runs
(`main.c:123`, then `main.c:143`). The outcome was right; the mechanism was an
accident of startup order. The line now reads `LATA`, so it preserves the
*commanded* latch state directly instead of depending on the pin level happening
to agree.

My second error was calling `configure_attenuation()` "correct" and therefore the
two paths "inconsistent". `configure_attenuation()` only ever sets or clears
single bits (`LATA |= bit` at `control_routines.c:122`/`:143`/`:160` and
`LATA &= ~bit` at `:124`/`:145`/`:176`), so it *preserves* whatever RA6/RA7
hold. The two paths agree: `init()` parks them low, everything downstream leaves
them low.

The only thing actually worth doing is a one-line comment on `:57`, because
`~ROTARY_MAX_ATTENUATION` reads like a mask bug at a glance when it is
deliberate. No behaviour change.

**7. ~~The "10 us" comment on `encoder_timer_callback()` is stale.~~ — retracted,
it is intentional.** I previously listed this as an open cosmetic issue and
recommended deleting or rewriting the comment. That recommendation is withdrawn:
the comment is deliberate and stays as it is.

`/* use for measure irq execution time (10us) */` at `irq_routines.c:240` refers
to the measurement scaffolding that still surrounds the callbacks — the four
`#if 0 led_toggel();` blocks at `:241`, `:252`, `:260` and `:264` exist purely so
the ISR entry and exit points can be bracketed with a GPIO toggle and timed with
a scope. The comment documents that harness, and the harness is still in the
file, so the comment is still pointing at something real. It is a note about the
measurement setup, not a claim about the configured timer period.

For the avoidance of doubt, the configured period genuinely is 1 ms, not 10 µs:
`mcc_generated_files/timer/src/tmr0.c:47` sets `TMR0H = 0xF9` with HFINTOSC at
1:128 in 8-bit mode, and its own comment says "Period 1ms; Frequency 250000 Hz;
Count 249". So the comment and the timer configuration do not agree numerically.
That is not being tracked as a defect, and the comment is not to be "corrected" —
but section 5 and this entry are the places to look if the tick period ever
matters. The genuinely ~10 µs-scale callback is the IR one, which runs at 66 µs.

#### FIXED

**1. Unvalidated EEPROM channel can index out of bounds.** `init()` used to read
`instance->channel = eeprom_read(0x04)` straight into the field, so a corrupt or
erased value (> 3) indexed `channel_attenuation[channel]` — a 4-element array —
on the very next `process_channel()` call. A factory-fresh part was safe
(`__EEPROM_DATA` seeds 0x04 with 0), but bit rot or a partial write was not.

The clamp was added in the same edit that narrowed `channel` to `int8_t`, because
the narrowing turned this from a latent bug into a *prerequisite*: a stored `255`
would cast to `-1` and index `channel_attenuation[-1]`. It reads into a `uint8_t`
and range-checks **before** the signed cast, since a `> ROTARY_MAX_CHANNEL` test
on the already-narrowed value could never fire (`control_routines.c:70`–`:77`):

```c
uint8_t stored_channel = eeprom_read(EEPROM_ADDR_CHANNEL);
if (stored_channel > ROTARY_MAX_CHANNEL) {
  instance->channel = ROTARY_MIN_CHANNEL;
} else {
  instance->channel = (int8_t)stored_channel;
}
```

**3. Wrong `save_mode` index on channel change.** `process_channel()` tested
`instance->save_mode[Volume]` before arming `SaveChannel`. It now correctly reads
`instance->save_mode[Channel]` (`control_routines.c:231`), so
`save_mode[Channel] = SaveOnChange` now takes effect.

**4. `Single` mode cannot select a channel.** *Logic fixed, but see the caveat.*
The `DoublePress` case in the combined-encoder branch used to be an empty
`break`, so `instance->control` could never leave its initial value and a single
encoder could only ever drive attenuation. It now toggles between `Volume` and
`Channel` (`control_routines.c:320`–`:325`).

**The caveat: the new code is unreachable in the shipped build.** `instance.mode`
is written exactly once, at `main.c:92` (`.mode = Dual`), and is never reassigned
anywhere in the firmware. All three readers
(`irq_routines.c:233`, `control_routines.c:244`, `control_routines.c:288`)
therefore always take the dual-mode path, which means both
`timer_callback_process_single()` and the new `DoublePress` handler only ever run
if something sets `instance.mode = Single`. The fix is correct but inert; it needs
a way to enter single mode — a build-time `#define`, a hardware strap, or a
gesture — before it changes any behaviour. (The toggle itself is index-safe:
`enum Control` is `{ Combined = 0, Volume = 0, Channel = 1 }`, so `control` is
always 0 or 1 and `encoder_count[control]` stays in bounds.)


**5. ISR → main-loop race on `press`, plus 16-bit shared fields.** *Fully fixed in
two steps. And the original analysis of this issue rested on a bad measurement —
see the retraction above.*

**What was actually wrong with the original entry.** It claimed that
`sizeof(enum ButtonPress)` and `sizeof(enum Control)` are 2, so `press` and
`control` were 2-byte objects whose every access was a two-instruction 16-bit
load or store. Both enums are **1 byte** on XC8 v4.00, and always were. Three
things followed from the bad number, and all three are now known to be wrong:

- The "torn read of `press`" defect — a `0x0100` phantom value assembled from
  the low byte of `NoPress` and the high byte of `SinglePress` — **could not
  occur**. `press` was already a single-byte object, so a load of it was always
  atomic.
- The `control` row's "torn index → wrong axis" failure — same reason. `control`
  is and always was one byte, so `encoder_count[instance.control]` could not be
  indexed with a half-updated value.
- The predicted RAM win (`Button_t` 10 → 9, `Instance_t` down by ~8) was
  imaginary. `Button_t` was **already** 9 bytes and `Instance_t` was
  **unchanged at 69** until the second step below.

Two of the original claims survive intact, and both were about `press` for
reasons that have nothing to do with its width: the field was read **twice**,
and the main loop **overwrote** it after acting on it.

**Step 1 — the `press` hand-off.** `press` is no longer cleared by the consumer.
A one-byte `press_pending` flag was added to `Button_t` (`definitions.h:100`) and
the producer/consumer pair was reordered:

```c
/* button_fsm() — irq_routines.c:38, :68, :69/:73 (three decision points) */
button->press = LongPress;        /* payload first */
button->press_pending = true;     /* flag second    */
```

```c
/* process_encoder_button() — control_routines.c:275–:279, :295–:299, :313–:317 */
if (instance->encoder[Volume].button.press_pending) {
  instance->encoder[Volume].button.press_pending = false;  /* clear FIRST */
  switch (instance->encoder[Volume].button.press) {         /* then act    */
    ...
  }
}
```

That closed both surviving defects:

| Defect | Cause | Status |
|---|---|---|
| ~~Torn read of `press`~~ | needed a 2-byte field | **never existed** — premise retracted |
| **Double read of `press`** | `!= NoPress` test and the `switch` were two independent loads, so the ISR could make them disagree | **FIXED** — the test is now on the flag and `press` is loaded exactly once, by the `switch` |
| **Lost press** | the main loop wrote `= NoPress` *after* acting, destroying any ISR write that landed inside the `switch` | **FIXED** — the main loop no longer writes `press` at all; that is now the producer's field exclusively |

Both orderings are load-bearing, and they are the reason the window is closed
rather than merely narrowed:

- *Producer: payload before flag.* Flag-first would let the consumer wake and
  act on the previous press.
- *Consumer: flag before payload.* If the ISR fires between the `= false` write
  and the `switch` read, the consumer acts on the **new** press, and the
  still-set flag makes it act on that same press once more next loop. Nothing is
  lost; the only cost is a possible duplicate.

At-least-once is the right trade. A duplicate is harmless: `eeprom_save_status()`
compares before writing (`:245` and `:255`), and toggling `control` twice lands
back where it started. A lost press is a lost user action.

**Step 2 — `channel` and `attenuation` narrowed to `int8_t`.** These were the only
genuinely 16-bit shared fields, and they are now single-byte objects, so every
load and store of them is a single atomic access. Four declarations in
`Instance_t` changed (`definitions.h:133`–`:136`):

```c
int8_t  channel;             /* 0..3,  or -1 — shared with the ISR */
int8_t  last_channel;        /* 0..3,  or -1 — main loop only */
int8_t  attenuation;         /* 0..63, or -1 — shared with the ISR */
int8_t  last_attenuation;    /* 0..63, or -1 — main loop only */
```

`int8_t` is signed because `-1` is the "not set yet" sentinel (`main.c:96`–`:97`),
and it is wide enough for both ranges with room to spare. The `!= -1` and
`> ROTARY_MAX_*` tests at `control_routines.c:200`, `:228`, `:382` and `:391` keep
working unchanged, because `int8_t` promotes to `int` in every expression. The four
`temporary` locals in the ISR (`irq_routines.c:125`, `:154`, `:190`, `:204`) and
the two in `process_ir()` (`control_routines.c:337`–`:338`) were narrowed to
match, so nothing takes a `volatile int` down to `int8_t` implicitly — the
project compiles with `-mwarn=-3`, and that is what surfaced the eight narrowing
diagnostics that the explicit types now silence.

`last_channel` and `last_attenuation` are main-loop-only and were narrowed purely
for a uniform, self-documenting block; the ISR never reads them.

**What deliberately did *not* change.** `ChannelVolume_t` stays `int` — it is
main-loop only. `encoder_count[]` stays `int` — it is ISR-only. And
`save_countdown_counter` must stay 16-bit regardless, because it counts down from
1000 and is initialised to `-1`.

**Cost.** Program memory **4450 → 4275 words** (−175). Per module:
`irq_routines.c` **815 → 705** (−110), `control_routines.c` **1326 → 1253** (−73),
`main.c` **105 → 102** (−3), `rotary_encoder.c` **114 → 115** (+1). The
single-byte accesses are both cheaper and smaller than the 16-bit sequences they
replaced, so the fix pays for itself in flash. RAM is flat at **180 bytes** of the
2048-byte space: `Instance_t` shrank 69 → 65, but the linker gave the four bytes
back to the stacks (`cstackBANK2` 0x12 → 0x13, `cstackCOMMON` 0x0E → 0x0D), so
there is no net RAM saving to claim. No change to timing or relay sequencing.

**The narrowing makes issue 1 mandatory rather than optional.** With
`channel` as an `int8_t`, a corrupt EEPROM byte no longer fails safe by accident:
`255` would cast to `-1` and then index `channel_attenuation[-1]`. So the clamp
that issue 1 had been asking for is now a correctness prerequisite of this change,
and it was added in the same edit (`control_routines.c:70`–`:77`):

```c
uint8_t stored_channel = eeprom_read(EEPROM_ADDR_CHANNEL);
if (stored_channel > ROTARY_MAX_CHANNEL) {
  instance->channel = ROTARY_MIN_CHANNEL;
} else {
  instance->channel = (int8_t)stored_channel;
}
```

Reading into a `uint8_t` first and range-checking *before* the signed cast is the
part that matters; a `> ROTARY_MAX_CHANNEL` test on the already-narrowed `int8_t`
would never fire, because `255` has become `-1`.

**How this should be verified.** The functional test is that a long press on
either encoder still arms its `save_action`, that a double press in single mode
still toggles `control`, and that the attenuator still sweeps to the channel's
stored value on a channel change. To actually exercise the race rather than hope
it is gone, temporarily raise `RELAIS_MAX_SETUP_TIME` so the main loop blocks for
several tick periods, then confirm no press is dropped and no channel/attenuation
value is missed under repetition — that is the scenario the original bug lives in,
and the only way to show it is closed. Note that `make build CONF=default` cannot
run in this sandbox (it fails writing `build/default/production/main.i` with
`Operation not permitted`), so the figures above were produced by running the
project's own `Makefile` against a copy of the tree in a writable directory, and
the before/after pair was built the same way so the comparison is like-for-like.

**6. Dead constant `EEPROM_SAVE_STATUS_VALUE`.** The `#define … 1000 /* 1 second
on a 1ms loop */` had been superseded by `DEFAULT_SAVE_COUNTDOWN` /
`save_countdown_counter`. It is now deleted from `definitions.h`, and nothing
referenced it.

**8. `PORTB` read-modify-write instead of `LATB`.** *Fixed; all channel-select
writes now go through the latch.* My earlier version of this entry claimed there
was a `PORTBbits.RB4 = …` write in "the IR output path" — there is no such line,
the IR output path uses the `LATB`-based `LED_*` macros — and it also placed the
`factory_reset()` channel-cycling loop in the wrong function. The real issue is
narrower, and it is a whole-register RMW on `PORTB`, which contains **input**
pins.

`CHAN_SEL_MASK` is `0x0f` (`definitions.h:45`), covering RB0–RB3 = `INPSEL0`–`3`.
The other PORTB bits are inputs: `TRISB = 0xD0`
(`mcc_generated_files/system/src/pins.c:52`) leaves RB4 (`IRIN`), RB6 and RB7 as
inputs. A read-modify-write reads the *port*, so on those bits it latches the
**pin** level into the `PORTB` latch — RB4 captures whatever level the IR receiver
happens to be sitting at. Every whole-register `PORTB` write is now a `LATB`
write, which reads the latch instead and cannot capture a pin level:

| Site | Code | Where |
|---|---|---|
| `control_routines.c:55` | `LATB &= ~CHAN_SEL_MASK` | `init()` — mute the relays at power-on |
| `control_routines.c:64`, `:66` | `LATB \|= in` / `LATB &= ~in` | `init()` — the one-channel-after-the-others cycle (not `factory_reset()`, as previously written) |
| `control_routines.c:227` | `LATB = ((LATB & ~CHAN_SEL_MASK) \| …)` | `process_channel()` — the live branch |
| `control_routines.c:206`, `:214` | same two writes | `process_channel()` — inside `#if 0`, converted too so the two branches do not drift again |

The `#if 0` branch is dead, so it emits no code, but leaving it on `PORTB` would
have made the block a trap for whoever re-enables it. `LATB` and `PORTB` map to
the same physical bits, so the fix is behaviour-neutral for the driven outputs
and adds no new hazard; it just stops the wasted port read and removes the
input-latch side effect.

Verified in the disassembly: at `0x0DF5` the built image now executes
`movf 25,w` / `movwf 25` (SFR `0x19` = `LATB`) where it previously executed
`movf 13,w` / `movwf 13` (SFR `0x0D` = `PORTB`). Counting these two registers
across the whole image, the totals are 6 operations before and 6 after, with
`PORTB`'s 1 read + 4 writes becoming `LATB`'s 1 read + 2 writes; the three
residual `movwf 13` are bank-57 peripheral writes in `__eewrite.c` /
`__eeread.c` / `tmr2.c`, not `PORTB`, and they are present in both builds.
(The 1-and-4-to-1-and-2 split is the compiler turning the two single-bit
loop writes into direct bit writes, so the counts are an observation, not a
one-for-one correspondence with the six source sites.)

Program memory is unchanged by this fix at 4275 words and data at 180 bytes — the
swap is a substitution of the SFR operand, so it emits the same instructions.
(The current total is 4157; issue 18 added 4 words, issue 13 added 11, and issue 15
removed 133.) The
per-module size is unchanged by this fix as well, since the swap only substitutes
the SFR operand; `control_routines.c` was 1253 words at the time and is 1207 now,
the difference being issues 12 and 13.

The `PORTA` RMWs were left alone at the time, on the grounds that `TRISA = 0x0`
makes all of PORTA an output so there is no input-pin read-back. They have since
been converted to `LATA` anyway, as a consistency follow-up rather than a bug
fix. The conversion is provably a no-op here: `PORTx` and `LATx` share one write
path, so only the *read* side differs, and with `TRISA = 0x0` every RA pin is an
output whose pin level equals its latch level. The compiler confirms it — the
same five instructions (`andwf` x4, `iorwf` x1) are emitted against `LATA` in
place of `PORTA`, so the image is byte-identical at 4279 words / 180 bytes.

`init()` was converted afterwards too, and the startup hazard there was worth
removing even though the two readings coincide at that moment — `LATA` has just
been cleared to `0x00` and every RA pin is an output, so it is again a no-op.
What it removes is the reliance on the pin level matching the latch, and at
`init()` that reliance was load-bearing: `~ROTARY_MAX_ATTENUATION` is `0xC0` and
therefore *preserves* RA6/RA7 rather than forcing them low, so the spare relays
only end up de-energised because `pins.c:43` happened to clear `LATA` first. See
the retracted issue 2 for the full correction.

One `PORTA` access remains, in `process_channel()` at `control_routines.c:213`:
`PORTA = ((PORTA & ~MASK) | value)`. Its right-hand side still reads pin levels
rather than the latch. That is harmless for the same `TRISA = 0x0` reason, and it
is not a read-modify-write against a second writer — no ISR touches `PORTA` — so
there is no race to lose. It was left as `PORTA` because the conversion was
scoped to `init()` and `configure_attenuation()`.

**9. `process_ir()` dropped `volatile`.** Its signature is now
`void process_ir(volatile Instance_t *instance)` (`control_routines.c:326`),
matching every sibling function. See issue 15 for the cast that accompanied it.

**11. Button FSM code duplication.** *All three call sites converted, dead copies
deleted.*
`button_fsm()` at `irq_routines.c:37` is now used by
`timer_callback_process_dual()` for both encoders (`:126`, `:164`) **and** by
`timer_callback_process_single()` (`:232`). The three divergent copies are down
to one implementation, and the dead source has since been removed as well, so this
and issue 17 are now one clean change rather than a behavioural gap plus a
leftover cleanup.

**14. Incomplete prototype for `factory_reset()`.** `control_routines.h:38`
declared `void factory_reset();`. In C an empty parameter list means
"unspecified arguments", not "none", so every call had to be checked against an
open-ended declaration rather than a real prototype. It is now
`void factory_reset(void);`, matching the definition at
`control_routines.c:85`. The only call site, `main.c:129`, is unchanged — a call
with no arguments is already correct.

The build previously reported, at every compile:

```
main.c:129: warning: (1518) direct function call made with an incomplete prototype (factory_reset)
```

and that warning is now gone. A prototype change is a compile-time-only
correction, so the code is untouched: program memory was still 4275 words at that
point (4157 now, after the issues 18, 13 and 15 fixes), data
still 180 bytes, `control_routines.c` still 1253 words. (Both of those
per-module and RAM figures are as they stood then; the current values are in the
size table at the top, and the older per-module numbers were measured
differently. Read the historical cost figures in these entries as
change-at-the-time, not as current state.) This was the last warning
in the build that came from project code — what is left is 26 `(520) function
is never called` warnings in MCC's generated files plus 2 `-Wsign-conversion`
warnings and one `_dummy` in the bundled third-party `irmp`, all pre-existing
and none of them actionable. (`_led_toggel` in `control_routines.c:35` is also
reported as never called, but that is the issue 7 measurement scaffolding, which
is deliberately retained.)

**16. `button_fsm()` forces every field access through memory.** The helper now
takes `uint16_t ms_counter` as a parameter and a plain `Button_t *`, so XC8 can
keep the working fields in registers instead of re-reading and re-writing each
one. This is what took the program memory down by roughly a hundred words, and it
also shrank `irq_routines.c` by about the same. The predicted ISR-latency
regression did not materialise to a measurable degree. See issue 18 for the cast
that this moved to the call sites.

*Caveat on the numbers:* the absolute word counts originally recorded here
(`irq_routines.c` 925 → 817, total 4571 → 4477, and 4422 after the issue 5 hand-off)
did not reproduce. A clean rebuild of the pre-narrowing tree against the committed
`dist/` artifact gives **4450** words, and the per-module sizes in that artifact
match the rebuild exactly — so the module figures are sound but the running totals
were off by a few tens of words. The only totals in this section that have been
re-verified on a full link are the ones in the issue 5 entry: **4450 → 4275**.
The current verified total is **4157** words / **175** data bytes, re-measured
from a clean `make clobber && make build CONF=default` in a writable copy of the
tree. Quote those two figures when describing the shipped image; treat every
older total in this section as approximate. The per-function accounting in the
building section supersedes the per-module numbers recorded here.

**17. Dead `#else` button code in `irq_routines.c`.** The three superseded inline
copies of the button logic, and the `uint_fast8_t encN_pressed` temporaries that
existed only to feed them, have been deleted. `irq_routines.c` is now 256 lines
and contains no `#else` block at all; all three call sites — `irq_routines.c:141`,
`:170` and `:224` — go through the single `button_fsm()` at `:37`. The only `#if 0`
blocks left in the file are the four `led_toggel()` timing-measurement snippets
(`:230`, `:241`, `:249`, `:253`).

*Correction to an earlier version of this entry:* it described the dead blocks as
still present and listed nine `press_pending` assignments that the issue 5 fix had
to hand-copy into them. That is no longer true — the blocks were removed when
issue 11 was closed, so no duplicated `press_pending` edit was ever needed. The
general warning still stands: keeping dead variants alive in `#if 1 / #else`
blocks is how the triplication started in the first place.

**18. Call sites cast away `volatile` on the button pointer.** `button_fsm()`
took a plain `Button_t *` (correct in itself — it is the fix for issue 16), but
the three call sites had to write `(Button_t *)&instance.encoder[…].button` to
get there, which threw the `volatile` on the enclosing `Instance_t` object away
at exactly the point the helper is entered. The discipline was bypassed, just
moved to the caller.

The helper now takes `volatile Button_t *` (`irq_routines.c:37`) and all three
casts are deleted — `&instance.encoder[…].button` converts implicitly, because
adding a qualifier is a valid implicit conversion in C. So the compiler, not a
comment, is what keeps the casts honest from now on.

**Cost: +4 words** (4275 → 4279; `irq_routines.c` 705 → 709, `button_fsm` 368 →
372, and it is the only function that moved). That is cheap because on this part
a non-local `Button_t` field access is *already* a single RAM instruction, so
`volatile` has no register-caching cost to protect here — it only forces a
re-read, and there is exactly one re-read to force (the `press` / `press_pending`
hand-off, where the ISR writes and the main loop reads).

The alternative considered and rejected was the more principled one: drop the
blanket `volatile` from the global and all 15 signatures and mark only the five
genuinely shared fields (`channel`, `attenuation`, `control`, `press`,
`press_pending`) volatile individually, which would make the casts disappear by
construction. It measured identically (+4 words) but needs an exhaustive audit of
which fields cross the ISR boundary, and a field missed by that audit fails
*silently* — the opposite of what this issue is about. Worth doing as a separate
change if ever, not folded into a one-line-qualifier fix.

Note this is the mirror image of issue 16 rather than a contradiction: issue 16
deliberately stopped forcing every field access through memory, and this restores
only the *type* honesty, not the memory traffic.

## 18. Possible next steps

Cheapest first — most of these are one-liners:

- **Give `Single` mode a way to be entered** (issue #4). `instance.mode` is set to
  `Dual` once at `main.c:92` and never changed, so the new `DoublePress`
  control-toggle, all of `timer_callback_process_single()` and the whole
  `Combined` encoder path are dead code today. A single `#define SINGLE_ENCODER`
  (or a strap/gesture) is the difference between a finished feature and an
  unreachable one. Highest leverage per line of anything in this list.
- Comment the `init()` `LATA` mask (issue #2) — one line, recording that
  `~ROTARY_MAX_ATTENUATION` is `0xC0` and so *preserves* RA6/RA7 rather than
  driving them low, so nobody "fixes" the mask later.
- Add a `LongPress` save in the single-mode branch of `process_encoder_button()`
  (issue #19) — one branch, and single mode finally has a persistence story.

Then the structural work:

- Replace the remaining blocking relay sequencing with a tick-driven state
  machine (issue #12). The no-op delays are already gone and the worst case is
  down to 24 ms, so this is now purely about responsiveness and ownership: pace
  the steps off `instance.ms_counter` (already a free 1 ms counter from the TMR0
  ISR, so no ISR changes needed) and each shared field gets exactly one writer.
  `channel` and `attenuation` are single-byte and therefore tear-free, but the
  ISR still read-modify-writes `attenuation`, so a main-loop write that lands in
  the middle of that is still plain last-writer-wins. It is benign and
  self-correcting, and this is the change that would remove the caveat entirely.
  It is the one remaining item that needs hardware to validate.
- Stop casting `volatile` away in `process_ir()`: copy `IRMP_DATA` in and out
  of it so the cast at the `irmp_get_data()` call site can go (issue #15).

Features still in the `main.c` TODO block:

- Implement mute via RC (`IR_KEY_MUTE` is already mapped but unused). It would
  also give the status LED a job, which issue #20 needs.
- Implement acceleration for volume control (fewer steps per detent at speed).
- Use `IR_KEY_OK` as "store current volume as default for this channel" — a
  natural counterpart to the long-press gesture, and it would give the IR path a
  persistence story (issue #10).
- Indicate the active control when it is toggled (issue #20) — one LED blink on
  the `DoublePress` handler makes the mode discoverable.
