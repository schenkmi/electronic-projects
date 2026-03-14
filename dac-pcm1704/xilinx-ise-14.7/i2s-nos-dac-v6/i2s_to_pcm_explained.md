# I2S to PCM Verilog — Detailed Explanation

## Overview

The design converts an **I2S serial audio stream** into two delayed **PCM serial streams** suitable for the PCM1704U DAC. It has no combinational logic beyond wire assignments — everything is shift registers and flip-flops, which maps very efficiently onto the XC2C64A's 64 macrocells.

---

## The I2S Protocol (quick recap)

```
BCK:    _|‾|_|‾|_|‾|_|‾|_|‾|_|‾|_|‾|_|‾|_
LRCK:   ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|________________|‾‾  (high=left, low=right)
DATA:       [b31][b30]...[b0][b31][b30]...[b0]
```

- Data is clocked in MSB-first on **BCK** rising edge
- **LRCK** transitions mark the boundary between left and right channels
- There is a **1-bit offset** — the MSB appears one BCK cycle *after* the LRCK edge (I2S standard framing)

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

It produces a signal that toggles on **every** BCK edge — both rising and falling — giving a half-period delay. Standard flip-flops only trigger on one edge, so a small XOR trick is used to combine two half-registers.

### How the XOR trick works

Think of `p` and `n` as two halves of one logical register:

| Clock edge | Action |
|---|---|
| posedge | `p` captures `in`, encoded relative to `n` |
| negedge | `n` captures `in`, encoded relative to `p` |
| Any time | `out = p ^ n` decodes the current value |

The encoding `p <= in ^ n` ensures that `out = p ^ n` always equals the last value written to either half, regardless of which edge just fired. This is the standard technique for implementing a **DEFF** (dual-edge flip-flop) in Verilog, and CoolRunner-II has native silicon support for it — XST maps this pattern directly to a single macrocell.

### The two instances

```verilog
double_edge_dff deff_bck  (.clock(BCK), .reset(1'b0), .in(BCK),  .out(delay_bck));
double_edge_dff deff_lrck (.clock(BCK), .reset(1'b0), .in(LRCK), .out(delay_lrck));
```

- **`deff_bck`** feeds `BCK` into itself → output is BCK delayed by exactly **half a BCK period**
- **`deff_lrck`** samples `LRCK` on every BCK edge → output is LRCK delayed by **half a BCK period**

These delayed versions are used as the output clocks/strobes, so the PCM1704U always sees data *stable before* the clock edge it uses to latch — a classic **half-cycle data/clock offset** for setup time compliance.

---

## Module 2: `i2s_to_pcm` — Shift Registers

### Why delays are needed

The PCM1704U expects its data to arrive with specific timing relative to its clock. The I2S stream delivers 32 bits per channel per frame, but the PCM1704U only uses 24 bits. The delay values compensate for:

```
Right delay = 32 - 24 - 1 = 7 bits
  └─ 32: full I2S word width
  └─ 24: PCM1704U data width
  └─  1: I2S one-bit MSB offset after LRCK edge

Left delay  = 7 + 32 = 39 bits
  └─  7: same offset as right
  └─ 32: one full I2S word separates left from right channel data
```

### Right channel shift register

```verilog
reg [7:0] sr_right;

sr_right <= {sr_right[6:0], DATAIN};
```

This is an **8-bit shift register** clocked on every BCK rising edge. New bits enter at `[0]` and fall out at `[7]` after 8 cycles. The output tap is `sr_right[7]` — the bit that entered 7 cycles ago.

```
Cycle:      0    1    2    3    4    5    6    7
sr_right:  [D0] [D1] [D2] [D3] [D4] [D5] [D6] [D7]
                                                 ↑
                                         DATAOUTR tapped here (7-cycle delay)
```

### Left channel shift register

```verilog
reg [31:0] sr_left;

sr_left <= {sr_left[30:0], sr_right[7]};
```

This is a **32-bit shift register** fed from `sr_right[7]` — the already-7-cycle-delayed signal. So the total delay to `sr_left[31]` is **7 + 32 = 39 cycles**. The two registers are chained:

```
DATAIN → [sr_right: 8 stages] → tap at [7] → [sr_left: 32 stages] → tap at [31]
              7-cycle delay                        +32-cycle delay
                    ↓                                      ↓
                DATAOUTR                               DATAOUTL
```

---

## Output Assignments

```verilog
assign CLKOUTR  = delay_bck;     // half-cycle delayed BCK
assign LEOUTR   = delay_lrck;    // half-cycle delayed LRCK
assign DATAOUTR = sr_right[7];   // right channel data, 7 cycles delayed

assign CLKOUTL  = delay_bck;     // same delayed clock
assign LEOUTL   = delay_lrck;    // same delayed strobe
assign DATAOUTL = sr_left[31];   // left channel data, 39 cycles delayed

assign LED1 = 1'b0;              // active-low LED, always on
```

Both channels share the same `delay_bck` and `delay_lrck` — the clock and latch-enable are identical for left and right; only the data lines differ.

---

## Full Signal Flow Diagram

```
                     ┌─────────────────────────────────────────┐
BCK ────────────────►│ deff_bck (double_edge_dff)              ├──► CLKOUTR
                     │   in=BCK → out=BCK delayed ½ period     ├──► CLKOUTL
                     └─────────────────────────────────────────┘

                     ┌─────────────────────────────────────────┐
LRCK ───────────────►│ deff_lrck (double_edge_dff)             ├──► LEOUTR
                     │   in=LRCK → out=LRCK delayed ½ period   ├──► LEOUTL
                     └─────────────────────────────────────────┘

                     ┌──────────────┐    ┌──────────────────────┐
DATAIN ─────────────►│ sr_right [8] ├───►│ sr_left [32]         │
          posedge    │  shift reg   │    │  shift reg            │
            BCK      └──────┬───────┘    └──────────┬───────────┘
                            │ [7]                   │ [31]
                            ▼                       ▼
                        DATAOUTR               DATAOUTL
                     (7-cycle delay)        (39-cycle delay)
```

---

## Macrocell Usage Estimate

| Resource | Count |
|---|---|
| `sr_right` flip-flops | 8 |
| `sr_left` flip-flops | 32 |
| `deff_bck` (p + n) | 2 |
| `deff_lrck` (p + n) | 2 |
| **Total** | **44 / 64 macrocells** |

This leaves ~20 macrocells spare — a comfortable margin on the XC2C64A.
