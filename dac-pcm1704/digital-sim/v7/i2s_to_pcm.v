`timescale 1ns / 1ps
// =============================================================================
// Module : i2s_to_pcm
// Target : Xilinx XC2C64A (CoolRunner-II CPLD)
// Purpose: I2S to PCM 24-bit conversion for PCM1704U DAC
//
// I2S framing (standard, MSB-first):
//   LRCK low  = LEFT  channel
//   LRCK high = RIGHT channel
//   Data MSB appears 1 BCK cycle after the LRCK edge.
//
// Delay arithmetic:
//   I2S sub-frame = 32 BCK cycles.
//   PCM word width = 24 bits.
//   Right-channel pipeline depth = 32 - 24 - 1 = 7  (SR_DEPTH_R)
//   Left-channel  pipeline depth = SR_DEPTH_R + 32  = 39 total, implemented
//   as a further 32-stage shift off the right-channel output (SR_DEPTH_L).
//
// Output timing:
//   CLKOUT* and LEOUT* are half-BCK-period-delayed copies of BCK and LRCK,
//   produced by the double_edge_dff modules.  This ensures data on DATAOUT*
//   is stable at the PCM1704U inputs before the active clock edge arrives.
//
//   Both LEOUTR and LEOUTL carry the same delayed-LRCK signal.  This is
//   intentional: the PCM1704U uses LE as a word-load strobe triggered by the
//   rising edge of LE (= rising edge of LRCK delayed half a BCK).  It is NOT
//   a channel-select gate.  Each DAC chip receives only one channel's DATAOUT,
//   so asserting LE simultaneously on both is correct.
//
// CoolRunner-II notes:
//   - `initial` blocks are ignored by synthesis; power-on state is controlled
//     by the device GSR (Global Set/Reset).  They are kept for simulation.
//   - double_edge_dff exploits the native DEFF (dual-edge flip-flop) primitive
//     present in CoolRunner-II fabric.  The XOR construction synthesises to a
//     BUFGDLL/DEFF cell pair, giving a true half-period delay on every BCK
//     edge regardless of duty cycle.  Do not replace with a plain negedge DFF.
//
// Programming:
//   openFPGALoader -c digilent_hs3 --freq 1000000 -v *.jed
//   xc3sprog -c jtaghs2 -p 0 -J 1000000 -v *.jed
// =============================================================================

// -----------------------------------------------------------------------------
// Delay parameters
//   Changing DATA_WIDTH from 24 to 16 or 20 only requires updating SR_DEPTH_R.
//   SR_DEPTH_L should always equal one full I2S sub-frame (32 cycles).
// -----------------------------------------------------------------------------
`define DATA_WIDTH  24          // PCM word width
`define SR_DEPTH_R  7           // Right-ch delay: 32 - DATA_WIDTH - 1
`define SR_DEPTH_L  32          // Left-ch extra delay: one I2S sub-frame

// -----------------------------------------------------------------------------
// double_edge_dff
//   Produces a half-BCK-period delayed version of `in` by registering
//   complementary halves on posedge and negedge, then XOR-ing them.
//   On CoolRunner-II this maps directly to the native DEFF primitive.
//
//   Reset note: asserting reset drives both p and n to 0, so out = 0^0 = 0.
//   The two always-blocks must both clear on reset to guarantee out=0;
//   clearing only one leaves the XOR in an indeterminate state.
// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
// i2s_to_pcm  –  top level
// -----------------------------------------------------------------------------
module i2s_to_pcm (
    input  wire BCK,        // I2S bit clock  (~3 MHz at 44.1 kHz/32-bit frames)
    input  wire LRCK,       // I2S word-select (low = left, high = right)
    input  wire DATAIN,     // I2S serial data (MSB first, 1 BCK after LRCK edge)

    output wire CLKOUTR,    // PCM bit clock    – right channel
    output wire LEOUTR,     // PCM latch-enable – right channel
    output wire DATAOUTR,   // PCM serial data  – right channel

    output wire CLKOUTL,    // PCM bit clock    – left channel
    output wire LEOUTL,     // PCM latch-enable – left channel
    output wire DATAOUTL,   // PCM serial data  – left channel

    output wire LED1        // Status LED (active-low)
);

    // -------------------------------------------------------------------------
    // Half-BCK-period delay for clock and latch-enable outputs
    //   delay_bck  : BCK  delayed ~half BCK period → output clock to PCM1704U
    //   delay_lrck : LRCK delayed ~half BCK period → output LE  to PCM1704U
    //
    //   Both outputs are driven to all channels; see file header for why
    //   sharing delay_lrck between LEOUTR and LEOUTL is correct.
    // -------------------------------------------------------------------------
    wire delay_bck;
    wire delay_lrck;

    double_edge_dff deff_bck  (.clock(BCK), .reset(1'b0), .in(BCK),  .out(delay_bck));
    double_edge_dff deff_lrck (.clock(BCK), .reset(1'b0), .in(LRCK), .out(delay_lrck));

    // -------------------------------------------------------------------------
    // Shift registers
    //   sr_right : SR_DEPTH_R-stage pipeline aligning the I2S stream so that
    //              the 24-bit right-channel MSB appears at sr_right[SR_DEPTH_R-1]
    //              on the BCK cycle where the PCM1704U starts clocking in data.
    //
    //   sr_left  : SR_DEPTH_L-stage extension fed from sr_right[SR_DEPTH_R-1],
    //              adding one full 32-bit I2S sub-frame of delay so the left-
    //              channel word is available in the correct half-frame.
    //
    //   Both advance on posedge BCK; output data is therefore stable well
    //   before the delayed (half-period-later) clock edge reaches the DAC.
    // -------------------------------------------------------------------------
    reg [`SR_DEPTH_R-1:0] sr_right;
    reg [`SR_DEPTH_L-1:0] sr_left;

    initial begin       // simulation only
        sr_right = {`SR_DEPTH_R{1'b0}};
        sr_left  = {`SR_DEPTH_L{1'b0}};
    end

    always @(posedge BCK) begin
        sr_right <= {sr_right[`SR_DEPTH_R-2:0], DATAIN};
        sr_left  <= {sr_left [`SR_DEPTH_L-2:0], sr_right[`SR_DEPTH_R-1]};
    end

    // -------------------------------------------------------------------------
    // Output assignments
    // -------------------------------------------------------------------------
    assign CLKOUTR  = delay_bck;
    assign LEOUTR   = delay_lrck;
    assign DATAOUTR = sr_right[`SR_DEPTH_R-1];

    assign CLKOUTL  = delay_bck;
    assign LEOUTL   = delay_lrck;      // same LE signal – see file header
    assign DATAOUTL = sr_left[`SR_DEPTH_L-1];

    assign LED1 = 1'b0;                // active-low, always on

endmodule