# I2S to PCM Verilog — Detailed Explanation
**Target:** Xilinx XC2C64A (CoolRunner-II CPLD)  
**Purpose:** I2S to PCM 24-bit conversion for PCM1704U DAC

---

## Overview

The design receives a standard **I2S serial audio stream** and produces two retimed **PCM serial output streams** — one for the right channel, one for the left — formatted for the PCM1704U DAC. 

The entire design is built from:
- Two **double-edge flip-flops** for half-cycle clock/strobe delay
- Two **shift register chains** for channel alignment delay
- Pure **wire assignments** for outputs

There is no combinational data logic, which keeps macrocell usage low and timing deterministic.

---

## The I2S Protocol (quick recap)

```
BCK:    _|‾|_|‾|_|‾|_|‾|_|‾|_|‾|_|‾|_|‾|_
LRCK:   ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|________________|‾‾  (high=left, low=right)
DATA:       [b31][b30]...[b0][b31][b30]...[b0]
```

- Data is clocked in **MSB-first** on the **BCK rising edge**
- **LRCK high** = left channel word being transmitted
- **LRCK low** = right channel word being transmitted
- There is a **1-bit framing offset** — the MSB appears one BCK cycle *after* the LRCK transition (I2S standard)

---

## Module 1: `double_edge_dff`

```verilog
module double_edge_dff (
    input  wire clock,
    input  wire reset,
    input  wire in,
    output wire out
);
    reg p, n;
    assign out = p ^ n;

    always @(posedge clock or posedge reset)
        if (reset) p <= 1'b0;
        else       p <= in ^ n;

    always @(negedge clock or posedge reset)
        if (reset) n <= 1'b0;
        else       n <= in ^ p;
endmodule
```

### What it does

Produces an output that updates on **every BCK edge** — both rising and falling — effectively delaying the input signal by exactly **half a BCK period**. Standard flip-flops only trigger on one edge, so a two-register XOR technique is used to achieve dual-edge behaviour.

### How the XOR trick works

`p` and `n` are two storage elements, each clocked on opposite edges:

| Clock edge | Register updated | Operation |
|---|---|---|
| posedge | `p` | `p <= in ^ n` |
| negedge | `n` | `n <= in ^ p` |
| Any time | — | `out = p ^ n` |

The XOR encoding ensures `out = p ^ n` always reflects the most recently written value regardless of which edge fired. This is the canonical Verilog idiom for a **DEFF (dual-edge flip-flop)**, and the CoolRunner-II has **native silicon support** for it — XST maps this pattern directly to a single macrocell rather than two.

### The two instances

```verilog
double_edge_dff deff_bck  (.clock(BCK), .reset(1'b0), .in(BCK),  .out(delay_bck));
double_edge_dff deff_lrck (.clock(BCK), .reset(1'b0), .in(LRCK), .out(delay_lrck));
```

| Instance | Input | Output | Effect |
|---|---|---|---|
| `deff_bck` | `BCK` fed back into itself | `delay_bck` | BCK delayed by **½ BCK period** |
| `deff_lrck` | `LRCK` sampled on every BCK edge | `delay_lrck` | LRCK delayed by **½ BCK period** |

The delayed signals are used as output clocks and strobes. This ensures the PCM1704U always sees **data stable before the clock edge** it uses to latch — a standard half-cycle offset for setup time compliance.

---

## Module 2: `i2s_to_pcm` — Shift Registers

### Why delays are needed

The I2S stream carries **32 bits per channel per frame**, but the PCM1704U only uses **24 bits**. The unused bits must be discarded, and the valid data must be aligned to arrive at the DAC latch at exactly the right moment.

```
Right channel delay = 32 - 24 - 1 = 7 bits
  └─ 32 : full I2S word width
  └─ 24 : PCM1704U usable data width
  └─  1 : I2S one-bit MSB offset after LRCK edge

Left channel delay  = 7 + 32 = 39 bits
  └─  7 : same framing offset as right channel
  └─ 32 : one complete I2S word separates left from right channel data
```

### Right channel shift register

```verilog
reg [7:0] sr_right;

sr_right <= {sr_right[6:0], DATAIN};
```

An **8-stage shift register** clocked on every BCK rising edge. New bits enter at position `[0]` and propagate toward `[7]`. The output tap is `sr_right[7]` — the bit that entered exactly **7 clock cycles ago**.

```
Cycle:      1    2    3    4    5    6    7    8
           [D1] [D2] [D3] [D4] [D5] [D6] [D7] [D8]
                                                 ↑
                                     DATAOUTR tapped here
                                       (7-cycle delay)
```

### Left channel shift register

```verilog
reg [31:0] sr_left;

sr_left <= {sr_left[30:0], sr_right[7]};
```

A **32-stage shift register** fed from `sr_right[7]` — the already-7-cycle-delayed signal. Total delay to `sr_left[31]` is therefore **7 + 32 = 39 BCK cycles**. The two registers are chained in series:

```
DATAIN ──► [sr_right: 8 stages] ──► tap[7] ──► [sr_left: 32 stages] ──► tap[31]
                 7-cycle delay                        +32-cycle delay
                       │                                     │
                   DATAOUTR                             DATAOUTL
               (7 cycles delayed)                  (39 cycles delayed)
```

---

## Output Assignments

```verilog
assign CLKOUTR  = delay_bck;
assign LEOUTR   = ~delay_lrck;   // inverted — latch falls after data is valid
assign DATAOUTR = sr_right[7];

assign CLKOUTL  = delay_bck;
assign LEOUTL   = ~delay_lrck;   // inverted — latch falls after data is valid
assign DATAOUTL = sr_left[31];

assign LED1 = 1'b0;              // active-low LED, always on
```

### Clock outputs (CLKOUTR / CLKOUTL)

Both are driven by `delay_bck` — BCK shifted by half a period. This ensures the data lines are stable **before** the PCM1704U samples them on the clock edge.

### Latch-enable outputs (LEOUTR / LEOUTL)

Both are driven by `~delay_lrck` — the **inverted**, half-period-delayed version of LRCK. The inversion is required because:

- The **PCM1704U latches data on the falling edge** of `/LE`
- Without inversion, the falling edge would occur at the **start** of the data window (too early)
- With inversion, the falling edge occurs at the **end** of the valid 24-bit data window (correct)

Both channels share identical LE signals since they are derived from the same LRCK source, offset only by the data delay in the shift registers.

### Data outputs (DATAOUTR / DATAOUTL)

| Signal | Source | Delay |
|---|---|---|
| `DATAOUTR` | `sr_right[7]` | 7 BCK cycles |
| `DATAOUTL` | `sr_left[31]` | 39 BCK cycles |

### Status LED

```verilog
assign LED1 = 1'b0;
```

Hardwired low. Since the LED is **active-low**, this keeps it permanently on as a power/running indicator.

---

## Full Signal Flow

```
                  ┌──────────────────────────────────────────┐
BCK ─────────────►│ deff_bck (double_edge_dff)               ├──► CLKOUTR
                  │   in=BCK → out=BCK delayed ½ period      ├──► CLKOUTL
                  └──────────────────────────────────────────┘

                  ┌──────────────────────────────────────────┐
LRCK ────────────►│ deff_lrck (double_edge_dff)              │
                  │   in=LRCK → out=LRCK delayed ½ period    │
                  └───────────────────┬──────────────────────┘
                                      │ inverted (~)
                                      ├──► LEOUTR
                                      └──► LEOUTL

                  ┌─────────────┐     ┌──────────────────────┐
DATAIN ──────────►│ sr_right[8] ├────►│ sr_left[32]          │
       posedge    │  shift reg  │     │  shift reg            │
         BCK      └──────┬──────┘     └──────────┬───────────┘
                         │ [7]                   │ [31]
                         ▼                       ▼
                     DATAOUTR               DATAOUTL
                  (7-cycle delay)        (39-cycle delay)
```

---

## PCM1704U Timing Compliance

The latch-enable falling edge lands within the last BCK cycle of the 24-bit data window:

```
BCK:      __|‾|__|‾|__|‾|__|‾|__|‾|__|‾|   <- delayed by ½ period
DATA:     ═══[b23]══[b22]══...══[b0]═══════ <- valid 24-bit window
/LE:      ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|__  <- falls AFTER last data bit
                                         ↑
                                    latch here
```

The half-period offset provided by `deff_bck` and `deff_lrck` ensures there is no clock-to-data race at the PCM1704U input pins.

---

## Macrocell Usage Estimate

| Resource | Flip-flops | Notes |
|---|---|---|
| `sr_right` | 8 | Right channel delay pipeline |
| `sr_left` | 32 | Left channel delay pipeline |
| `deff_bck` | 2 | p + n halves, maps to 1 DEFF cell |
| `deff_lrck` | 2 | p + n halves, maps to 1 DEFF cell |
| **Total** | **44** | **of 64 macrocells available** |

~20 macrocells remain spare — a comfortable margin on the XC2C64A.
