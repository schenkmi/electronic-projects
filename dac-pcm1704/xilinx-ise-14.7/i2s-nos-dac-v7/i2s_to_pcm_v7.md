# `i2s_to_pcm.v` — Detailed Design Documentation

**Project:** i2s-nos-dac v7 (I2S → NOS DAC, PCM1704U)
**File:** `i2s_to_pcm.v` (top module `i2s_to_pcm`, helper module `double_edge_dff`)
**Target device:** Xilinx **XC2C64A** CoolRunner-II CPLD, VQ44 package, speed grade **−7**
**Toolchain:** ISE 14.7 Project Navigator (XST + CPLD fitter), project file `i2s-nos-dac-v7.xise`
**Companion files:**

| File | Role |
|---|---|
| `i2s_to_pcm.ucf` | Pin constraints and I/O standard |
| `i2s_to_pcm.jed` | Compiled Jedec bitstream (ready to program) |
| `i2s_to_pcm_tb.v` | Icarus Verilog testbench |
| `Makefile` | Simulation workflow (`make full`, `make wave-full`) |
| `measurements/` | Saleae Logic captures of the working hardware |

---

## 1. Purpose

`i2s_to_pcm` converts a standard **I2S** serial audio stream (32-bit frames, MSB-first,
one-bit framing offset) into **two independent PCM serial streams** — one per channel —
in the format required by the **PCM1704U** DACs on the board:

```
   I2S source (ASRC)                     CPLD (XC2C64A)                      DAC stage
 ┌──────────────────────┐        ┌─────────────────────────────┐      ┌───────────────┐
 │ BCK   ───────────────┼───────►│                             │      │               │
 │ LRCK  ───────────────┼───────►│        i2s_to_pcm           ├─────►│  PCM1704U     │
 │ DATAIN ──────────────┼───────►│                             │ LE   │  (right ch)   │
 └──────────────────────┘        │                             │ CLK  │               │
                                 │                             │ DATA └───────────────┘
                                 │                             ├─────►┌───────────────┐
                                 │                             │ LE   │  PCM1704U     │
                                 │                             │ CLK  │  (left ch)    │
                                 │                             │ DATA └───────────────┘
                                 └─────────────────────────────┘
```

The PCM1704 is a 3-channel, 24-bit (or 20-bit) current-output DAC with a **serial input**:
data is shifted in MSB-first on the rising edge of its BCLK, and the last 24 bits shifted
into its serial register are transferred to the parallel DAC register on the **falling edge
of its WCLK (latch-enable) pin** (TI PCM1704 datasheet, "Audio Data Interface").

The board uses two channels of one PCM1704U (left and right); the third channel is unused.

### System operating point

Per the board schematic annotation (KiCad, `dac-df1706-pcm1704-v2`):

> Input from ASRC is 384 kHz. PCM1704 supports x8 oversampling at 96 kHz ⇒ 768 kHz.
> CLKOUTR/CLKOUTL are 24.576 MHz. 2 channels × 32 bits × 384 kHz = 24.576 MHz.

| Parameter | Value |
|---|---|
| LRCK (word clock) | **384 kHz** |
| BCK (bit clock) | **24.576 MHz** (24.576 MHz < 25 MHz spec max ✓) |
| BCK period `P` | 40.68 ns |
| BCK half period `P/2` | 20.34 ns |
| I2S sub-frame (one channel word) | 32 BCK = 1.3018 µs |
| Frame (L + R) | 64 BCK = 2.6035 µs |

The design is **rate-agnostic**: it works for any LRCK/BCK ratio where the I2S source
uses 32-bit frames and the BCK rate stays within the PCM1704 limits (≤ 25 MHz).

---

## 2. Port Reference

```verilog
module i2s_to_pcm (
    input  wire BCK,        // I2S bit clock  (~3 MHz at 44.1 kHz/32-bit frames)
    input  wire LRCK,       // I2S word-select (low = left, high = right)
    input  wire DATAIN,     // I2S serial data (MSB first, 1 BCK after LRCK edge)

    output wire CLKOUTR,    // PCM bit clock    - right channel
    output wire LEOUTR,     // PCM latch-enable - right channel
    output wire DATAOUTR,   // PCM serial data  - right channel

    output wire CLKOUTL,    // PCM bit clock    - left channel
    output wire LEOUTL,     // PCM latch-enable - left channel
    output wire DATAOUTL,   // PCM serial data  - left channel

    output wire LED1        // Status LED (active-low)
);
```

| Port | Direction | Pin (UCF) | Description |
|---|---|---|---|
| `BCK` | in | 43 | I2S bit clock, Schmitt-triggered |
| `LRCK` | in | 41 | I2S word select. **Low = left, high = right** (I2S standard) |
| `DATAIN` | in | 39 | I2S serial data, MSB-first, Schmitt-triggered |
| `CLKOUTR` | out | 21 | Right-channel PCM BCLK (= BCK delayed ½ BCK period) |
| `LEOUTR` | out | 20 | Right-channel WCLK/LE (= LRCK delayed ½ BCK period) |
| `DATAOUTR` | out | 22 | Right-channel serial data (24 valid bits per window, MSB first) |
| `CLKOUTL` | out | 13 | Left-channel PCM BCLK (same net as `CLKOUTR`) |
| `LEOUTL` | out | 12 | Left-channel WCLK/LE (same net as `LEOUTR`) |
| `DATAOUTL` | out | 14 | Left-channel serial data (24 valid bits per window, MSB first) |
| `LED1` | out | 38 | Status LED, active-low, hardwired on |

All I/O is **LVCMOS33** (`NET "*" IOSTANDARD = LVCMOS33` in the UCF).

---

## 3. Architectural Overview

The design is deliberately **combinational-free**: it consists of exactly four building
blocks and wire assignments. There is no state machine, no multiplexers in the data path,
and no comparators.

```
                 ┌────────────────────────────────────────────────────────────┐
 BCK ───────────►│  double_edge_dff "deff_bck"                                │
                 │   in = BCK  →  out = BCK delayed by exactly ½ BCK period   ├────► delay_bck ──► CLKOUTR / CLKOUTL
                 └────────────────────────────────────────────────────────────┘

                 ┌────────────────────────────────────────────────────────────┐
 LRCK ──────────►│  double_edge_dff "deff_lrck"                               │
                 │   in = LRCK →  out = LRCK delayed by exactly ½ BCK period  ├────► delay_lrck ──► LEOUTR / LEOUTL
                 └────────────────────────────────────────────────────────────┘

                 ┌──────────────────────┐    ┌──────────────────────────────────────────┐
 DATAIN ────────►│ sr_right             ├───►│ sr_left                                  │
   (posedge BCK) │ 8-stage shift reg    │    │ 32-stage shift reg, fed from sr_right[7] │
                 │ tap sr_right[7]      │    │ tap sr_left[31]                          │
                 └──────────┬───────────┘    └───────────────────────┬──────────────────┘
                            ▼                                        ▼
                        DATAOUTR                                DATAOUTL
                   (DATAIN − 7 BCK cycles)                 (DATAIN − 39 BCK cycles)
```

| Building block | Implementation | Delay provided |
|---|---|---|
| `deff_bck` | dual-edge flip-flop idiom | ½ BCK period |
| `deff_lrck` | dual-edge flip-flop idiom | ½ BCK period |
| `sr_right` | 8-stage shift register (posedge BCK) | 7 BCK cycles to tap `[7]` |
| `sr_left`  | 32-stage shift register (posedge BCK), chained after `sr_right` | +32 BCK cycles to tap `[31]` (39 total) |

The two delay types solve two different problems:

1. **Cycle alignment** (shift registers): I2S carries 32 bits per channel but the DAC
   only wants 24, and each channel's 24-bit window must line up with *its own* LE
   falling edge.
2. **Sub-cycle phase** (DEFFs): the DAC samples data on the rising edge of its clock, so
   data must be stable well before that edge. Delaying the output clocks by half a BCK
   period places every clock edge *in the middle* of a data-stable window, converting a
   zero-margin situation into a full half-period of setup and hold.

---

## 4. Module `double_edge_dff`

### 4.1 Source

```verilog
module double_edge_dff (
    input  wire clock,
    input  wire reset,
    input  wire in,
    output wire out
);
    reg p, n;           // posedge / negedge halves

    assign out = p ^ n;

    initial begin       // simulation only; GSR controls hardware power-on state
        p = 1'b0;
        n = 1'b0;
    end

    always @(posedge clock or posedge reset)
        if (reset) p <= 1'b0;
        else       p <= in ^ n;

    always @(negedge clock or posedge reset)
        if (reset) n <= 1'b0;
        else       n <= in ^ p;

endmodule
```

### 4.2 Function

`out` follows `in` on **every edge** of `clock` (both rising and falling). In steady
state with no input glitches, the output is a replica of the input delayed by **exactly
half a clock period**, independent of the input duty cycle.

### 4.3 How the XOR encoding works

`p` and `n` are two storage elements clocked on opposite edges; each is updated with the
XOR of the input and the *other* storage element. `out = p ^ n` always holds the value of
`in` that was sampled most recently, whichever edge fired last:

| Event | Update | Resulting `out = p ^ n` |
|---|---|---|
| posedge, `in = x` | `p <= x ^ n` | `(x ^ n) ^ n = x` |
| negedge, `in = y` | `n <= y ^ p` | `p ^ (y ^ p) = y` |

So the register pair behaves as a single dual-edge flip-flop whose output toggles on
every clock edge. When `in` is the clock itself (`in = clock`), the output is a 50%-duty
copy of the clock phase-inverted by half a period — i.e. a **½-period delay for any
signal**.

### 4.4 Reset behaviour

Asserting `reset` clears **both** `p` and `n`, so `out = 0 ^ 0 = 0` deterministically.
Both `always` blocks must clear on reset: clearing only one would leave the XOR output in
a state that depends on the uncleared half. (In this design `reset` is tied to `1'b0` on
both instances; the reset path exists for testability and correctness of the idiom.)

### 4.5 Why not a plain negedge flip-flop?

A register clocked on the negedge of BCK would give a ½-period delay only while BCK has
exactly 50% duty cycle, and would break if the duty cycle drifted (the PCM1704 requires
BCK high/low pulse widths ≥ 14 ns on a 40 ns cycle). The XOR/DEFF construction updates on
*whichever edge actually occurs*, so the half-period delay is exact for any duty cycle,
and — critically for this device — XST maps the pattern directly onto the CoolRunner-II
**native DEFF macrocell**, costing one macrocell instead of a multi-LUT construction.
The source header explicitly warns: *do not replace with a plain negedge DFF*.

### 4.6 Instantiation

```verilog
wire delay_bck;
wire delay_lrck;

double_edge_dff deff_bck  (.clock(BCK),  .reset(1'b0), .in(BCK),  .out(delay_bck));
double_edge_dff deff_lrck (.clock(BCK),  .reset(1'b0), .in(LRCK), .out(delay_lrck));
```

| Instance | Input | Output | Effect |
|---|---|---|---|
| `deff_bck` | BCK fed into itself | `delay_bck` | BCK delayed ½ period → drives `CLKOUTR`/`CLKOUTL` |
| `deff_lrck` | LRCK sampled on every BCK edge | `delay_lrck` | LRCK delayed ½ period → drives `LEOUTR`/`LEOUTL` |

---

## 5. I2S Input Framing (reference)

Standard I2S, 32-bit frames, MSB-first, 1-bit framing offset:

```
BCK:    _|‾|_|‾|_|‾|_|‾|_|‾|_|‾|_|‾|_|‾|_|‾|_|‾|_|‾| ...
LRCK:   ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|____________________________|‾‾‾‾  (high = right, low = left)
DATA:          [L b31][L b30] ... [L b0] [R b31][R b30] ... [R b0]
```

- Data is valid on BCK **rising** edges (the transmitter changes data on falling edges).
- The **MSB appears 1 BCK cycle after the LRCK edge** (I2S one-bit framing offset).
- LRCK low ⇒ left channel word is on the bus; LRCK high ⇒ right channel word.
- Each sub-frame is 32 BCK cycles; only the first 24 bits carry audio (the low 8 bits of
  the 32-bit I2S word are padding zeros).

Let `t = 0` be a LRCK **rising** edge (left→right boundary). With BCK rising edges at
`t = 0, P, 2P, ...` (P = BCK period):

| Signal event | Time |
|---|---|
| Right word MSB `R b31` sampled on `DATAIN` | `t = P` |
| Right word `R b_i` sampled | `t = (32 − i) · P` |
| Right word LSB `R b0` sampled | `t = 32 P` |
| LRCK falling edge (right→left boundary) | `t = 32 P` |
| Left word MSB `L b31` sampled on `DATAIN` | `t = 33 P` |
| Left word `L b_i` sampled | `t = (64 − i) · P` |
| Left word LSB `L b0` sampled | `t = 64 P` |
| LRCK rising edge (next frame) | `t = 64 P` |

---

## 6. Shift-Register Data Path

### 6.1 Parameters

```verilog
`define DATA_WIDTH  24          // PCM word width
`define SR_DEPTH_R  7           // Right-ch delay: 32 - DATA_WIDTH - 1
`define SR_DEPTH_L  32          // Left-ch extra delay: one I2S sub-frame
```

**Delay arithmetic:**

```
Right channel delay = 32 − 24 − 1 = 7 BCK cycles
   32 : full I2S sub-frame width
   24 : PCM1704 usable data width (20BIT pin low = 24-bit mode, the default)
    1 : I2S one-bit MSB offset after the LRCK edge

Left channel delay  = 7 + 32 = 39 BCK cycles
    7 : same framing offset as the right channel
   32 : one full I2S sub-frame separates left from right channel data
```

`SR_DEPTH_L` is always exactly one sub-frame (32) regardless of `DATA_WIDTH`; only
`SR_DEPTH_R` changes if the PCM word width changes (e.g. 20-bit mode ⇒ `SR_DEPTH_R = 11`).

### 6.2 Register implementation

```verilog
reg [`SR_DEPTH_R-1:0] sr_right;   // 8 stages
reg [`SR_DEPTH_L-1:0] sr_left;    // 32 stages

always @(posedge BCK) begin
    sr_right <= {sr_right[`SR_DEPTH_R-2:0], DATAIN};
    sr_left  <= {sr_left [`SR_DEPTH_L-2:0], sr_right[`SR_DEPTH_R-1]};
end
```

Both registers advance on the BCK **rising** edge and are chained in series:

```
DATAIN ─► [sr_right: 8 stages] ──tap [7]──► [sr_left: 32 stages] ──tap [31]
              7-cycle delay                      +32-cycle delay
                    │                                  │
                DATAOUTR                            DATAOUTL
```

- `DATAOUTR = sr_right[7]` — the bit that entered the pipeline **7 BCK rising edges ago**.
- `DATAOUTL = sr_left[31]` — the same stream delayed a further 32 edges: a total of
  **39 BCK rising edges** after entry.

Because the taps are register outputs, the data is stable for an entire BCK period after
each rising edge — i.e. stable across the DAC's clock edge, which (being delayed by ½
period) lands exactly mid-window (see §7).

### 6.3 Where each channel's 24-bit window lands

A bit sampled on `DATAIN` at `t = m·P` appears on `DATAOUTR` during `[m·P + 7P, m·P + 8P)`
and on `DATAOUTL` during `[m·P + 39P, m·P + 40P)`.

**Right channel** (valid bits `R b31 … R b8`, sampled at `m = 1 … 24`):

| Bit | Sampled at | On `DATAOUTR` during | Latched by DAC at (rising edge of CLKOUT) |
|---|---|---|---|
| `R b31` (MSB) | `P`   | `[8 P, 9 P)`   | `8.5 P` |
| `R b24` | `16 P`  | `[23 P, 24 P)` | `23.5 P` |
| `R b8` (24th) | `24 P`  | `[31 P, 32 P)` | `31.5 P` |

After `t = 31.5 P` the right DAC's serial register holds the complete 24-bit word.
The 8 I2S padding zeros then pass through `DATAOUTR` during `[32 P, 40 P)` — harmless,
because the word was already captured by the LE falling edge and the register is simply
refilled before the next load.

**Left channel** (valid bits `L b31 … L b8`, sampled at `m = 33 … 56`):

| Bit | Sampled at | On `DATAOUTL` during | Latched by DAC at |
|---|---|---|---|
| `L b31` (MSB) | `33 P` | `[72 P, 73 P)`  | `72.5 P` |
| `L b8` (24th) | `56 P` | `[95 P, 96 P)`  | `95.5 P` |

After `t = 95.5 P` the left DAC's serial register holds the complete left word.

### 6.4 Why these exact delays

The requirement per channel is: **the full 24-bit word must be in the DAC serial
register before the LE falling edge that belongs to that channel, and no word of the
other channel may leak into the window.**

- The right word's LE falling edge is at `t = 32.5 P` (see §7). The last right bit is
  latched at `31.5 P` ⇒ **1.0 full BCK cycle of margin** before the load.
- The left word's LE falling edge is at `t = 96.5 P`. The last left bit is latched at
  `95.5 P` ⇒ **1.0 full BCK cycle of margin** before the load.
- Symmetry: the 32-stage `sr_left` extension means each channel is treated identically —
  every word is loaded 1 BCK after its 24th bit, in the middle of its own sub-frame's
  tail, with the next channel's data not starting to appear until 8 BCK later.

---

## 7. Output Timing vs. the PCM1704U

### 7.1 How the PCM1704 serial interface works (datasheet summary)

From the PCM1704 datasheet ("Audio Data Interface"):

- Data format: binary two's complement, **MSB first**; the last 24 bits shifted in are
  loaded (20-bit mode selectable via pin 9, which defaults to 24-bit; the INVERT pin
  defaults to non-inverted).
- **All serial input bits are latched into the serial input register on the rising edge
  of BCLK.**
- **The serial-to-parallel transfer occurs on the falling edge of WCLK** (the LE pin,
  pin 7). The DAC output changes at the rising edge of the 2nd BCLK after that falling
  edge.
- Any number of bits may precede the 24-bit word.

### 7.2 Edge placement in this design

`LEOUT = delay_lrck` = LRCK delayed by ½ BCK period:

| LE event | Time (frame of §5/§6) | Meaning |
|---|---|---|
| LE rising edge | `0.5 P` | Delayed left→right boundary |
| **LE falling edge** | **`32.5 P`** | **Delayed right→left boundary ⇒ right word loaded** |
| LE rising edge | `64.5 P` | Delayed right→left boundary (next frame) |
| **LE falling edge** | **`96.5 P`** | **Delayed left→right boundary ⇒ left word loaded** |

`CLKOUT = delay_bck` = BCK delayed by ½ BCK period; its rising edges are at
`t = 0.5 P, 1.5 P, 2.5 P, …` — always exactly in the middle of a BCK period.

### 7.3 Datasheet timing-specification compliance

At the system operating point (BCK = 24.576 MHz, `P = 40.68 ns`, `P/2 = 20.34 ns`):

| Spec (datasheet Figure 2) | Requirement | This design | Margin |
|---|---|---|---|
| `tBCY` BCLK cycle time | ≥ 40 ns (max 25 MHz) | 40.68 ns | ✓ (BCK is 24.576 MHz) |
| `tBCH` / `tBCL` BCLK pulse width | ≥ 14 ns | 20.34 ns | +6.34 ns |
| `tWH` BCLK rising edge → WCLK falling edge | ≥ 10 ns | 20.34 ns | +10.34 ns |
| `tWS` WCLK falling edge → BCLK rising edge | ≥ 10 ns | 20.34 ns | +10.34 ns |
| `tWCH` WCLK pulse width HIGH | > `tBCY` | 32 P = 1.30 µs | ✓ |
| `tWCL` WCLK pulse width LOW | > `tBCY` | 32 P = 1.30 µs | ✓ |
| `tDS` DATA setup to BCLK rising edge | ≥ 10 ns | 20.34 ns (before CPLD output delay) | ✓ |
| `tDH` DATA hold after BCLK rising edge | ≥ 10 ns | 20.34 ns (before CPLD output delay) | ✓ |

Notes:

- The WCLK falling edge (`32.5 P`) sits exactly midway between the BCLK rising edges at
  `32 P` and `33 P` — which is precisely where `tWH`/`tWS` require it, and precisely when
  the 24-bit word is fully in the serial register (last bit at `31.5 P`).
- DATA changes on BCK rising edges (CPLD register outputs update on posedge BCK); the
  DAC samples on the *delayed* BCK rising edge, half a period later, so setup and hold
  are each a full half BCK period, before subtracting CPLD output propagation (tens of
  ps on a −7 part) and PCB skew.
- The datasheet's "WCLK must remain LOW until after the first BCLK cycle of the next
  data word" guidance (from the Stopped-Clock section) is satisfied in continuous
  operation: each WCLK LOW window spans 32 BCK cycles.

### 7.4 Per-frame word-load sequence (complete picture)

```
t:        0        32P        64P        96P
          │          │          │          │
LRCK      ‾‾‾‾‾‾‾‾‾‾|____________|‾‾‾‾‾‾‾‾‾|__________   (high = right)
          │  R word  │  L word  │  R word  │  L word
delay_lrck‾‾‾|__________|‾‾‾‾‾‾‾‾‾‾‾‾‾|__________     (LE, ½-BCK delayed)
              ^        ^              ^        ^
            rise   FALL 32.5P      rise   FALL 96.5P
                     │                      │
                     ▼                      ▼
            right word loaded        left word loaded
            (serial→parallel        (serial→parallel
             on falling edge)        on falling edge)

DATAOUTR:  … [R b31 … R b8 (24b, 8P–32P)] [8×'0' (32P–40P)] … then next frame's R word at 72P
DATAOUTL:  … (previous L word tail) … [L b31 … L b8 (24b, 72P–96P)] [8×'0' (96P–104P)] …
```

### 7.5 Why both channels share CLK and LE

- **CLK sharing is required**: both DAC channels are clocked from the same bit clock;
  `CLKOUTR` and `CLKOUTL` are the same net (`delay_bck`).
- **LE sharing is intentional, not a shortcut**: the PCM1704's WCLK is a word-load strobe
  for *that channel's own* serial register. Each chip receives only one channel's
  `DATAOUT`, and the falling edge of the shared `delay_lrck` lands inside each channel's
  own 24-bit window tail — one falling edge per sub-frame loads the word that just
  completed for that channel. Asserting LE simultaneously on both channels is therefore
  correct: at `32.5 P` the right register holds the right word while the left register
  holds stale/previous data that is simply not the word being loaded this cycle (the left
  word is loaded at `96.5 P`), and vice versa. WCLK is **not** a channel-select gate.

  *(Implementation note: the file header comment in `i2s_to_pcm.v` describes the load as
  "triggered by the rising edge of LE". The PCM1704 datasheet specifies the
  serial-to-parallel transfer on the **falling** edge of WCLK, and the falling edge is
  also the one that lands in the correct position per §7.3. The two descriptions agree on
  what the circuit does (one delayed-LRCK edge per sub-frame loads the word); this
  document follows the datasheet.)*

---

## 8. Output Assignments

```verilog
assign CLKOUTR  = delay_bck;
assign LEOUTR   = delay_lrck;
assign DATAOUTR = sr_right[`SR_DEPTH_R-1];

assign CLKOUTL  = delay_bck;
assign LEOUTL   = delay_lrck;      // same LE signal - see §7.5
assign DATAOUTL = sr_left[`SR_DEPTH_L-1];

assign LED1 = 1'b0;                // active-low LED, always on
```

| Output | Source | Net delay from `DATAIN`/`BCK`/`LRCK` |
|---|---|---|
| `CLKOUTR` / `CLKOUTL` | `delay_bck` | BCK − ½ period |
| `LEOUTR` / `LEOUTL`   | `delay_lrck` | LRCK − ½ period |
| `DATAOUTR`            | `sr_right[7]`  | 7 BCK rising edges |
| `DATAOUTL`            | `sr_left[31]`  | 39 BCK rising edges |
| `LED1`                | constant `0`   | n/a — active-low indicator, always on |

---

## 9. Device-Specific Implementation Notes

1. **`initial` blocks are ignored by synthesis.** On the CoolRunner-II the power-on state
   is defined by the device **GSR (Global Set/Reset)** and the project setting
   "Default Powerup Value of Registers = Low" (see `.xise`). The `initial` blocks in
   `double_edge_dff` and the top level exist purely for simulation determinism.

2. **Native DEFF primitive.** The `double_edge_dff` XOR construction is the canonical
   idiom XST recognises on CoolRunner-II; it synthesises to the device's dual-edge
   macrocell (the XOR is absorbed into the macrocell LUT). Do **not** "simplify" it to a
   negedge-triggered register: that loses both the exact half-period delay under duty
   drift and the single-macrocell mapping.

3. **No combinational data path.** The only combinational logic in the whole design is
   the two XOR gates of the DEFF idiom (absorbed into macrocells). Every output is a
   register output or a constant, which keeps timing deterministic and trivially
   sign-off-able at any BCK rate within the device rating.

4. **Resource estimate** (XC2C64A: 64 macrocells, 1024 logic cells):

   | Resource | Flip-flops | Notes |
   |---|---|---|
   | `sr_right` | 8 | right-channel pipeline |
   | `sr_left` | 32 | left-channel pipeline |
   | `deff_bck` | 1 | native DEFF macrocell |
   | `deff_lrck` | 1 | native DEFF macrocell |
   | **Total** | **≈ 42** | comfortable margin on the 64-macrocell device |

5. **I/O standards.** All 10 ports are LVCMOS33 per the UCF; the three I2S inputs carry
   `SCHMITT_TRIGGER` for clean edge detection on long traces.

6. **Pin map** (from `i2s_to_pcm.ucf`, XC2C64A VQ44):

   | Pin | Net | | Pin | Net |
   |---|---|---|---|---|
   | 43 | BCK | | 20 | LEOUTR |
   | 41 | LRCK | | 21 | CLKOUTR |
   | 39 | DATAIN | | 22 | DATAOUTR |
   | 38 | LED1 | | 12 | LEOUTL |
   |   |   | | 13 | CLKOUTL |
   |   |   | | 14 | DATAOUTL |

---

## 10. Configuration Parameters

The only knobs are three defines at the top of the file:

```verilog
`define DATA_WIDTH  24   // PCM word width
`define SR_DEPTH_R   7   // = 32 - DATA_WIDTH - 1
`define SR_DEPTH_L  32   // always one I2S sub-frame
```

To switch the DACs to **20-bit mode** (PCM1704 pin 9 low): set `DATA_WIDTH 20` and
`SR_DEPTH_R 11` (`32 − 20 − 1`). `SR_DEPTH_L` never changes. No other edit is needed —
the DEFFs, outputs, and timing all adapt automatically because every delay is derived
from the sub-frame width and `DATA_WIDTH`.

---

## 11. Build, Simulation, and Programming

### 11.1 Hardware implementation (ISE 14.7)

Open `i2s-nos-dac-v7.xise` in ISE Project Navigator. The project is pre-configured:
device `xc2c64a`, package VQ44, speed −7, top module `i2s_to_pcm`, UCF
`i2s_to_pcm.ucf`, Verilog/XST. Run *Generate Post-MAP Bitfile* → produces a Jedec file
(check `i2s_to_pcm.jed` is the committed artifact of the finalized v7 build).

### 11.2 Programming the CPLD

```bash
openFPGALoader -c digilent_hs3 --freq 1000000 -v i2s_to_pcm.jed
# or, with Xilinx tools:
xc3sprog -c jtaghs2 -p 0 -J 1000000 -v i2s_to_pcm.jed
```

### 11.3 Simulation (Icarus Verilog)

```bash
make full          # compile i2s_to_pcm.v + i2s_to_pcm_tb.v with iverilog, run vvp
make wave-full     # open the resulting i2s_to_pcm_tb.vcd in GTKWave
make clean         # remove i2s_to_pcm_full, *.vcd
```

The testbench (`i2s_to_pcm_tb.v`) generates 5 I2S frames of 32-bit words
(left `0x00123456`, right `0x00FEDCBA`, i.e. 24-bit patterns padded to 32) at
50 MHz BCK / 48 kHz LRCK (64 BCK per channel), dumps a VCD, checks `DATAOUTR` against
the 7-cycle-delayed `DATAIN` stream, verifies `LED1` stays low, and reports any mismatch
on stdout.

### 11.4 Hardware verification evidence

`measurements/` contains Saleae Logic captures of the final v7 board
(`DSLogic-I2S-to-PCM1704-i2s-nos-dac-v7-1.dsl` + two screenshots) showing the I2S inputs
and the retimed PCM outputs (CLK/LE/DATA per channel) in correct alignment.

---

## 12. Timing Summary (one picture)

At 384 kHz / 24.576 MHz (`P = 40.68 ns`), for the right channel of a frame whose LRCK
rises at `t = 0`:

```
             ┌── 7 BCK shift delay ──┐   ┌── 32 BCK (1 sub-frame) ──┐
DATAIN ──────┤ R b31 … R b0 @ P..32P ├─► DATAOUTR: R b31…b8 @ 8P..32P ─┤ (left taps here)
                                                                    │
DAC (rising edge of CLKOUT = m·P + 0.5P) latches:
    R b31 @ 8.5P … R b8 @ 31.5P  ──►  serial register complete @ 31.5P
    WCLK (LE) falling edge @ 32.5P  ──►  serial → parallel transfer (word loaded)
    WCLK next falling edge @ 96.5P ──►  loads the LEFT word (its last bit @ 95.5P)
```

Everything is register-to-register, every margin is a half BCK period or more, and the
design is correct for any 32-bit-frame I2S source with BCK ≤ 25 MHz.
