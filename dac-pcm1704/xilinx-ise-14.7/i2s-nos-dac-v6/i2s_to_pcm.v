`timescale 1ns / 1ps
// =============================================================================
// Module : i2s_to_pcm
// Target : Xilinx XC2C64A (CoolRunner-II CPLD)
// Purpose: I2S to PCM 24-bit conversion for PCM1704U DAC
//
// Channel delays
//   Right : 7 bits  (32 - 24 - 1 I2S offset)
//   Left  : 39 bits (7 + 32)
//
// Programming
//   openFPGALoader -c digilent_hs3 --freq 1000000 -v *.jed
//   xc3sprog -c jtaghs2 -p 0 -J 1000000 -v *.jed
// =============================================================================

// git clean -d -x -f .

// -----------------------------------------------------------------------------
// Double-edge-triggered flip-flop
// Exploits the native VHDL/Verilog DEFF primitive in CoolRunner-II fabric.
// The XOR trick synthesises directly to a BUFGDLL/DEFF cell pair.
// -----------------------------------------------------------------------------
module double_edge_dff (
    input  wire clock,
    input  wire reset,
    input  wire in,
    output wire out
);
    reg p, n;           // posedge / negedge halves
 
    assign out = p ^ n;
 
    always @(posedge clock or posedge reset)
        if (reset) p <= 1'b0;
        else       p <= in ^ n;
 
    always @(negedge clock or posedge reset)
        if (reset) n <= 1'b0;
        else       n <= in ^ p;
 
endmodule
 
// -----------------------------------------------------------------------------
// Top-level: I2S receiver + dual-channel PCM serialiser
// -----------------------------------------------------------------------------
module i2s_to_pcm (
    input  wire BCK,        // I2S bit clock
    input  wire LRCK,       // I2S word-select (left/right)
    input  wire DATAIN,     // I2S serial data
 
    output wire CLKOUTR,    // PCM bit clock  - right channel
    output wire LEOUTR,     // PCM latch-enable - right channel
    output wire DATAOUTR,   // PCM serial data  - right channel
 
    output wire CLKOUTL,    // PCM bit clock  - left channel
    output wire LEOUTL,     // PCM latch-enable - left channel
    output wire DATAOUTL,   // PCM serial data  - left channel
 
    output wire LED1        // Status LED (active-low)
);
 
    // -------------------------------------------------------------------------
    // Delay lines
    //   delay_bck  : BCK delayed by half a BCK period  (double-edge FF)
    //   delay_lrck : LRCK sampled and delayed likewise
    // Both signals are used to re-time the output strobes so data is stable
    // at the PCM1704U inputs when the clock edge arrives.
    // -------------------------------------------------------------------------
    wire delay_bck;
    wire delay_lrck;
 
    double_edge_dff deff_bck  (.clock(BCK), .reset(1'b0), .in(BCK),  .out(delay_bck));
    double_edge_dff deff_lrck (.clock(BCK), .reset(1'b0), .in(LRCK), .out(delay_lrck));
 
    // -------------------------------------------------------------------------
    // Shift registers
    //   sr_right [7:0]  - 8-stage pipeline; bit[7] is the 7-cycle-delayed
    //                     copy of DATAIN that feeds the right-channel output
    //                     AND the left-channel shift register.
    //   sr_left  [31:0] - additional 32-stage pipeline for left channel.
    // -------------------------------------------------------------------------
    reg [7:0]  sr_right;
    reg [31:0] sr_left;
 
    always @(posedge BCK) begin
        // Right channel: delay DATAIN by 7 clocks
        // (accounts for 32 - 24 - 1 bit I2S framing offset)
        sr_right <= {sr_right[6:0], DATAIN};
 
        // Left channel: further delay by 32 clocks
        sr_left  <= {sr_left[30:0], sr_right[7]};
    end
 
    // -------------------------------------------------------------------------
    // Output assignments
    //   CLKOUT* and LEOUT* are the half-cycle-delayed versions of BCK / LRCK,
    //   ensuring the PCM1704U sees data valid before the active clock edge.
    // -------------------------------------------------------------------------
    assign CLKOUTR  = delay_bck;
    assign LEOUTR   = ~delay_lrck; // inverted - latch falls after data is valid
    assign DATAOUTR = sr_right[7];
 
    assign CLKOUTL  = delay_bck;
    assign LEOUTL   = ~delay_lrck; // inverted - latch falls after data is valid
    assign DATAOUTL = sr_left[31];
 
    // LED on = logic 0 (active-low)
    assign LED1 = 1'b0;
 
endmodule