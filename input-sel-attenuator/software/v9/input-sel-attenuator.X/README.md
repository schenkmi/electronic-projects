# Input Selector + Attenuator Firmware

PIC16F18056 based input channel selection + attenuator with rotary encoder and IR remote control support.

## Features

- 4-channel input selector with relay switching
- 6-bit (64-step) digital attenuator (0-63dB)
- Dual rotary encoder mode (separate volume/channel) or single encoder mode
- IR remote control support (RC5 protocol)
- Per-channel default attenuation stored in EEPROM
- Make-before-break relay control to avoid audio pops

## Build

Requires MPLAB X IDE v6.30+ and XC8 compiler v3.10+:

```bash
make build CONF=default
make clean CONF=default
```

---

## Rotary Encoder Push Button Implementation

The push button detection runs inside the **Timer0 interrupt** (`encoder_timer_callback()`) at 10µs intervals and implements a **non-blocking state machine** for single, double, and long press detection.

### Button State Structure

```c
typedef struct {
  bool   button_pressed;     // Currently pressed?
  bool   waiting_for_double; // Waiting for potential double-click?
  int    click_count;        // Number of short clicks
  uint16_t press_time;       // When button was pressed (ms)
  uint16_t release_time;     // When button was released (ms)
  enum ButtonPress press;    // Result: NoPress/Single/Double/Long
} Button_t;
```

### Timing Thresholds

Defined in `definitions.h`:

```c
#define ROTARY_PUSH_DEBOUNCE_TIME        20  // 20ms debounce
#define ROTARY_PUSH_LONG_PRESS_TIME    1000  // 1s = long press
#define ROTARY_PUSH_DOUBLE_CLICK_TIME   500  // 500ms double-click window
```

### Detection Algorithm

**1. Button Press Detection:**
```c
if (ENC1SWITCH_GetValue() == 0) {  // Active-low
  if (!button_pressed) {
    press_time = ms_counter;       // Store press timestamp
    button_pressed = true;
  }
}
```

**2. Button Release Detection:**
```c
else {  // Button released
  if (button_pressed) {
    duration = ms_counter - press_time;
    button_pressed = false;

    if (duration >= 20ms) {  // Debounced
      release_time = ms_counter;

      if (duration >= 1000ms) {
        press = LongPress;     // Long press detected immediately
        click_count = 0;
        waiting_for_double = false;
      } else {
        click_count++;         // Short press, might become double
        waiting_for_double = true;
      }
    }
  }
}
```

**3. Double-Click Timeout:**
```c
if (waiting_for_double && (ms_counter - release_time > 500ms)) {
  if (click_count == 1) {
    press = SinglePress;
  } else if (click_count == 2) {
    press = DoublePress;
  }
  click_count = 0;
  waiting_for_double = false;
}
```

### State Diagram

```
         Press                          Release (<1s)
Idle ───────> Pressed ──────────────────────> Waiting (500ms)
                │                                  │
                │                                  ├─> SinglePress (1 click)
                │                                  ├─> DoublePress (2 clicks)
                │                                  └─> timeout resets
                │
                │ Release (≥1s)
                └───────────────────────────────> LongPress
```

### Event Processing

The main loop processes detected button events in `process_encoder_button()`:

```c
void process_encoder_button(volatile Instance_t* instance) {
  if (instance->encoder[Volume].button.press != NoPress) {
    switch (instance->encoder[Volume].button.press) {
      case LongPress:
        // Save attenuation on long press
        instance->save_action |= SaveVolume;
        break;
      case SinglePress:
      case DoublePress:
        // Reserved for future features
        break;
    }
    instance->encoder[Volume].button.press = NoPress;  // Acknowledge
  }
}
```

### Key Design Points

1. **Non-blocking**: No `delay()` calls - uses timestamp comparison
2. **Debounced**: 20ms minimum press time filters switch bounce noise
3. **Priority**: Long press detected immediately on release, no waiting for timeout
4. **Double-click window**: 500ms to press again, otherwise becomes single-click
5. **Two encoders**: Identical logic for both Volume and Channel encoders in dual mode
6. **Event-driven**: Main loop polls `press` field and clears after handling

### Files

| File | Description |
|------|-------------|
| `irq_routines.c` | Timer0 ISR with button state machine (lines 79-118) |
| `rotary_encoder.h` | Button_t structure and type definitions |
| `control_routines.c` | Event processing in `process_encoder_button()` |
| `definitions.h` | Timing constants and Instance_t state struct |

---

## IRMP (Infrared Multi-Protocol Decoder) Implementation

The firmware uses the **IRMP** library to decode IR remote control signals. IRMP supports 50+ IR protocols and provides a unified interface for protocol decoding.

### Configuration (`irmp/irmpconfig.h`)

Enabled protocols:

| Protocol | Description | Program Space |
|----------|-------------|---------------|
| `IRMP_SUPPORT_SIRCS_PROTOCOL` | Sony SIRCS | ~150 bytes |
| `IRMP_SUPPORT_NEC_PROTOCOL` | NEC + Apple + Onkyo | ~300 bytes |
| `IRMP_SUPPORT_SAMSUNG_PROTOCOL` | Samsung + Samsung32 | ~300 bytes |
| `IRMP_SUPPORT_KASEIKYO_PROTOCOL` | Kaseikyo (Panasonic) | ~250 bytes |
| `IRMP_SUPPORT_RC5_PROTOCOL` | **Philips RC5 (active)** | ~250 bytes |
| `IRMP_SUPPORT_RC6_PROTOCOL` | Philips RC6 + RC6A | ~250 bytes |
| `IRMP_SUPPORT_RUWIDO_PROTOCOL` | RUWIDO / T-Home | ~550 bytes |

Key settings:

```c
#define F_INTERRUPTS        15151           // 15.151 kHz sampling rate
#define IRMP_USE_CALLBACK   1               // Callbacks enabled
#define IRMP_HIGH_ACTIVE    0               // IR sensor is low-active
```

**Note:** `F_INTERRUPTS` must be between 10,000-20,000 Hz. The value 15151 is required for XC8/C18 PIC compilers.

### How IRMP Works

**1. Sampling**

The library must be called at a fixed frequency of 15,151 Hz. This is handled by Timer2 in `irq_routines.c`:

```c
void ir_timer_callback(void) {
  irmp_ISR();  // Called every 66µs (15.151 kHz)
}
```

**2. Pulse/Space Detection**

IR protocols encode bits as pulse/space pairs of specific lengths:

| Protocol | Encoding | Bit Time |
|----------|----------|----------|
| RC5 | Manchester | 1.778ms |
| NEC | Pulse-distance | 560µs pulse, 560µs/1.69ms space |
| Samsung | Pulse-distance | Similar to NEC |

**3. State Machine**

IRMP analyzes edge timing to identify the protocol and decode:
- Protocol ID
- Address (device code)
- Command (key code)
- Flags (repetition, release)

### Integration

**Initialization (`main.c`):**

```c
irmp_init();
irmp_set_callback_ptr(led_callback);  // LED feedback on IR reception
```

**Main Loop Processing (`control_routines.c:321-387`):**

```c
void process_ir(Instance_t* instance) {
  if (irmp_get_data(&instance->ir.data)) {
    // Filter by protocol and address
    if (instance->ir.data.protocol == IR_PROTOCOL &&
        instance->ir.data.address == IR_REMOTE_ADDRESS) {

      if (instance->ir.data.flags == 0x00) {
        // Normal key press - decode command
        switch (instance->ir.data.command) {
          case IR_KEY_CH_UP:   channel++; break;
          case IR_KEY_CH_DOWN: channel--; break;
          case IR_KEY_VOL_UP:  attenuation--; break;
          case IR_KEY_VOL_DOWN: attenuation++; break;
          case IR_KEY_1:       channel = 0; break;
          // ... more keys
        }
      }
    }
  }
}
```

### RC5 Remote Key Mapping (`definitions.h`)

```c
#define IR_PROTOCOL         IRMP_RC5_PROTOCOL
#define IR_REMOTE_ADDRESS   0x0001

// Key codes for "One For All TV Hitachi 2676" remote
#define IR_KEY_1            1   // Direct channel 1
#define IR_KEY_2            2   // Direct channel 2
#define IR_KEY_3            3   // Direct channel 3
#define IR_KEY_4            4   // Direct channel 4
#define IR_KEY_OK          53   // Reserved
#define IR_KEY_CH_UP       32   // Channel up
#define IR_KEY_CH_DOWN     33   // Channel down
#define IR_KEY_VOL_UP      16   // Volume up (less attenuation)
#define IR_KEY_VOL_DOWN    17   // Volume down (more attenuation)
#define IR_KEY_MUTE        13   // Reserved
```

### Data Flow

```
┌─────────────┐
│ IR Receiver │
└──────┬──────┘
       │ IR signal (38kHz carrier)
       ▼
┌─────────────────────────────┐
│ Timer2 IRQ (15.151 kHz)     │
│   irmp_ISR()                │
│   - Samples IR input pin    │
│   - Measures pulse lengths  │
│   - Runs protocol decoder   │
└──────────┬──────────────────┘
           │ Decoded frame stored
           ▼
┌─────────────────────────────┐
│ Main Loop (1ms cycle)       │
│   process_ir()              │
│   - irmp_get_data()         │
│   - Check protocol/address  │
│   - Map command to action   │
│   - Update channel/volume   │
└─────────────────────────────┘
```

### IRMP Data Structure (`irmp/irmp.h`)

```c
typedef struct {
  uint16_t protocol;   // IR protocol ID (e.g., IRMP_RC5_PROTOCOL)
  uint16_t address;    // Device address (e.g., 0x0001)
  uint16_t command;    // Key code (e.g., 16 for VOL+)
  uint8_t  flags;      // Flags: IRMP_FLAG_REPETITION, IRMP_FLAG_RELEASE
} IRMP_DATA;
```

### Key Design Points

1. **Protocol filtering**: Only RC5 frames with address `0x0001` are processed
2. **Non-blocking**: `irmp_get_data()` returns immediately, no polling delays
3. **LED feedback**: Callback toggles LED on IR reception for debugging
4. **Repetition handling**: RC5 sends toggle bit on key repeat, detected via `flags`
5. **Continuous volume**: Holding VOL+/- generates repeated commands

### Files

| File | Description |
|------|-------------|
| `irmp/irmp.h` | IRMP public API and IRMP_DATA structure |
| `irmp/irmpconfig.h` | Protocol selection and configuration |
| `irmp/irmp.c` | Core decoder implementation |
| `irmp/irmpprotocols.h` | Protocol definitions and timing constants |
| `irq_routines.c` | Timer2 ISR calling `irmp_ISR()` (line 323) |
| `control_routines.c` | IR command processing in `process_ir()` (line 321) |
| `definitions.h` | RC5 key codes and `IR_REMOTE_ADDRESS` |

---

## Attenuator Control

The attenuator uses **6 relay bits** (RA0-RA5) to control a 6-bit R-2R ladder network, providing 64 steps (0-63) of attenuation. Each step represents approximately 0.75dB, for a total range of 0-63dB.

### Attenuation Table

| Binary | Decimal | Attenuation |
|--------|---------|-------------|
| 000000 | 0 | 0dB (minimum) |
| 000001 | 1 | 0.75dB |
| 001111 | 15 | 11.25dB |
| 011111 | 31 | 23.25dB |
| 100000 | 32 | 24dB |
| 111111 | 63 | 63dB (maximum) |

### Make-Before-Break Algorithm

To prevent audio pops and clicks during attenuation changes, the firmware implements a **make-before-break** switching algorithm (`ATT_CTRL_MAKE_BEFORE_BREAK`):

```c
// 1st phase: Make operation (close contacts first)
for (int cnt = 0; cnt < ROTARY_ATTENUATION_BITS; cnt++) {
  uint8_t bit = ((1 << cnt) & 0xff);
  if ((PORTA & bit) != (attenuation & bit)) {
    if (attenuation & bit) {
      PORTA |= bit;  // Close relay contact
    }
    __delay_ms(RELAIS_MAX_SETUP_TIME);  // 3ms wait for relay settling
  }
}

// 2nd phase: Break operation (open contacts after)
for (int cnt = 0; cnt < ROTARY_ATTENUATION_BITS; cnt++) {
  uint8_t bit = ((1 << cnt) & 0xff);
  if ((PORTA & bit) != (attenuation & bit)) {
    if ((attenuation & bit) == 0) {
      PORTA &= ~bit;  // Open relay contact
    }
    __delay_ms(RELAIS_MAX_SETUP_TIME);  // 3ms wait for relay settling
  }
}
```

**Why this matters:** When changing from one attenuation value to another, some relays need to close while others open. The make-before-break approach ensures that relay contacts never create an open circuit moment during switching, which would cause audible pops.

### Alternative: Direction-Based Algorithm

The code also includes a **direction-based** algorithm (`ATT_CTRL_DIRECTION`) as an alternative:

- **Quieter → Louder** (decreasing attenuation): Switch LSB to MSB to avoid momentary 000000 state
- **Louder → Quieter** (increasing attenuation): Switch MSB to LSB to avoid momentary 000000 state

### Processing Flow (`process_attenuation()`)

```
┌─────────────────────────────────┐
│ Main Loop (1ms)                 │
│   process_attenuation()         │
│     if (attenuation changed)    │
│       → configure_attenuation() │
└─────────────────────────────────┘
                │
                ▼
┌─────────────────────────────────┐
│ configure_attenuation()         │
│   - Compare current vs target   │
│   - 1st pass: Make (close)      │
│   - 2nd pass: Break (open)      │
│   - 3ms delay per relay change  │
└─────────────────────────────────┘
                │
                ▼
┌─────────────────────────────────┐
│ Update PORTA                    │
│   - RA0-RA5 = attenuation bits  │
└─────────────────────────────────┘
```

### Key Parameters (`definitions.h`)

```c
#define ROTARY_ATTENUATION_BITS    6          // 6 relay bits
#define ROTARY_MAX_ATTENUATION     0x3F       // 63 (binary 111111)
#define RELAIS_MAX_SETUP_TIME      3          // 3ms for G6K-2F DC5 relay settling
```

---

## Channel Selection

Channel selection uses **4 relay bits** (RB0-RB3) to route one of 4 input channels to the output. Only one channel is active at a time.

### Channel Switching Sequence (`process_channel()`)

When the channel changes, the following sequence executes:

```c
if (instance->channel != instance->last_channel) {
  // 1. Store previous channel's attenuation
  if (instance->last_channel != -1) {
    instance->channel_attenuation[last_channel].attenuation = instance->attenuation;
  }

  // 2. Mute: Set attenuation to maximum (63dB)
  configure_attenuation(ROTARY_MAX_ATTENUATION);

  // 3. Switch to new channel
  PORTB = ((PORTB & ~CHAN_SEL_MASK) | ((1 << channel) & CHAN_SEL_MASK));
  __delay_ms(RELAIS_MAX_SETUP_TIME);

  // 4. Restore channel's attenuation
  instance->attenuation = channel_attenuation[channel].attenuation;
  configure_attenuation(attenuation);

  // 5. Trigger save if configured
  if (save_mode == SaveOnChange) {
    save_action |= SaveChannel;
    save_countdown_counter = DEFAULT_SAVE_COUNTDOWN;
  }
}
```

### Why Mute During Switch?

The attenuation is temporarily set to maximum (63dB) during channel switching to:
1. Prevent audio pops from relay contact bounce
2. Avoid momentary signal interruption noise
3. Ensure smooth, click-free channel transitions

### Channel → Attenuation State

Each channel maintains **two attenuation values**:

```c
typedef struct {
  int default_attenuation;  // Stored in EEPROM, restored on channel recall
  int attenuation;          // Current runtime value
} ChannelVolume_t;

ChannelVolume_t channel_attenuation[4];  // Channels 0-3
```

- **`default_attenuation`**: Persisted in EEPROM, restored when switching to this channel
- **`attenuation`**: Current runtime value, may differ from default during adjustment

---

## Factory Reset

A factory reset can be triggered by holding the **Channel encoder button** during startup.

### Reset Sequence (`factory_reset()`)

```c
void factory_reset() {
  if (ENC2SWITCH_GetValue() == 0) {  // Button held on power-up
    // Wait for release
    while(ENC2SWITCH_GetValue() == 0) {
      __delay_ms(100);
    }

    // Visual feedback: LED flashes 10 times (5 seconds)
    for (int cnt = 0; cnt < 10; cnt++) {
      LED_Toggle();
      __delay_ms(500);
    }

    // Reset EEPROM to defaults
    eeprom_write(0x00, ROTARY_MAX_ATTENUATION);  // Channel 0: max atten.
    eeprom_write(0x01, ROTARY_MAX_ATTENUATION);  // Channel 1: max atten.
    eeprom_write(0x02, ROTARY_MAX_ATTENUATION);  // Channel 2: max atten.
    eeprom_write(0x03, ROTARY_MAX_ATTENUATION);  // Channel 3: max atten.
    eeprom_write(0x04, ROTARY_MIN_CHANNEL);      // Default channel: 0
  }
}
```

### Reset Values

| EEPROM Address | Parameter | Reset Value |
|----------------|-----------|-------------|
| 0x00 | Channel 0 default attenuation | 63 (max) |
| 0x01 | Channel 1 default attenuation | 63 (max) |
| 0x02 | Channel 2 default attenuation | 63 (max) |
| 0x03 | Channel 3 default attenuation | 63 (max) |
| 0x04 | Default channel | 0 |

### Usage

1. Hold down the Channel encoder button
2. Power on the device
3. Continue holding until LED starts flashing
4. Release button - LED will flash 10 times (5 seconds)
5. Device restarts with factory defaults

---

## EEPROM Save System

The firmware uses a **delayed save mechanism** to minimize EEPROM writes and extend memory lifespan.

### Save Modes (`definitions.h`)

```c
enum SaveMode {
  SaveNever      = 0,  // Never auto-save
  SaveOnChange   = 1,  // Save immediately on change
  SaveOnLongPress = 2  // Save only on long press
};
```

### Save Actions

```c
enum SaveAction {
  NoSaveAction  = 0x00,
  SaveVolume    = 0x01,  // Save current attenuation as channel default
  SaveChannel   = 0x02   // Save current channel as power-on default
};
```

### Delayed Save Mechanism (`eeprom_save_status()`)

```c
void eeprom_save_status(volatile Instance_t* instance) {
  // Countdown timer - prevents rapid successive writes
  if (instance->save_countdown_counter > 0) {
    instance->save_countdown_counter--;
    return;  // Not yet time to save
  }

  // Save Volume (channel's default attenuation)
  if (instance->save_action & SaveVolume) {
    instance->save_action &= ~SaveVolume;

    // Update in-memory default
    instance->channel_attenuation[channel].default_attenuation = attenuation;

    // Write to EEPROM if changed
    if (eeprom_read(channel) != default_attenuation) {
      eeprom_write(channel, default_attenuation);
    }
  }

  // Save Channel (power-on default)
  if (instance->save_action & SaveChannel) {
    instance->save_action &= ~SaveChannel;

    if (eeprom_read(EEPROM_ADDR_CHANNEL) != channel) {
      eeprom_write(EEPROM_ADDR_CHANNEL, channel);
    }
  }
}
```

### Save Timing

```c
#define DEFAULT_SAVE_COUNTDOWN    1000  // 1000 × 1ms = 1 second delay
```

When a save is triggered:
1. `save_action` flag is set
2. `save_countdown_counter` = 1000
3. Each main loop iteration (1ms) decrements counter
4. After 1 second, EEPROM write occurs
5. This prevents writes if user continues adjusting

### Triggering Saves

**Long Press on Volume Encoder:**
```c
case LongPress:
  if (save_mode[Volume] == SaveOnLongPress) {
    save_countdown_counter = DEFAULT_SAVE_COUNTDOWN;
    save_action |= SaveVolume;  // Save current attenuation as default
  }
```

**Channel Change (if SaveOnChange enabled):**
```c
if (save_mode[Channel] == SaveOnChange) {
  save_action |= SaveChannel;
  save_countdown_counter = DEFAULT_SAVE_COUNTDOWN;
}
```

### EEPROM Layout

| Address | Content | Range |
|---------|---------|-------|
| 0x00 | Channel 0 default attenuation | 0-63 |
| 0x01 | Channel 1 default attenuation | 0-63 |
| 0x02 | Channel 2 default attenuation | 0-63 |
| 0x03 | Channel 3 default attenuation | 0-63 |
| 0x04 | Default channel (power-on) | 0-3 |

### Startup Initialization (`init()`)

```c
// Read last used channel
instance->channel = eeprom_read(EEPROM_ADDR_CHANNEL);

// Read default attenuation for each channel
for (uint8_t cnt = 0; cnt <= ROTARY_MAX_CHANNEL; cnt++) {
  instance->channel_attenuation[cnt].default_attenuation = eeprom_read(cnt);
  instance->channel_attenuation[cnt].attenuation = default_attenuation;
}
```

On power-up, all stored values are loaded and applied immediately.

### Files

| File | Description |
|------|-------------|
| `control_routines.c` | `configure_attenuation()`, `process_attenuation()`, `process_channel()`, `eeprom_save_status()`, `factory_reset()` |
| `definitions.h` | `ChannelVolume_t`, `SaveMode`, `SaveAction`, timing constants |
| `main.c` | `__EEPROM_DATA` initialization |
