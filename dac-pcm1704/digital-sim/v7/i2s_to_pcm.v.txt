`timescale 1ns / 1ps
// =============================================================================
// Module : i2s_to_pcm (XC2C64A final optimized)
// Purpose: I2S → PCM1704 (24-bit DAC)
// Notes  :
//   - No counters
//   - Fits in XC2C64A
//   - LE aligned to data (compressed marker method)
//   - Works with 32-bit I2S frames
// =============================================================================

module i2s_to_pcm (
    input  wire BCK,
    input  wire LRCK,
    input  wire DATAIN,

    output wire CLKOUTR,
    output wire LEOUTR,
    output wire DATAOUTR,

    output wire CLKOUTL,
    output wire LEOUTL,
    output wire DATAOUTL,

    output wire LED1
);

    // ============================================================
    // 1) LRCK EDGE DETECT (frame reference)
    // ============================================================
    reg lrck_d1;
    always @(posedge BCK)
        lrck_d1 <= LRCK;

    wire lrck_edge = lrck_d1 ^ LRCK;

    // I2S: MSB occurs 1 BCK after LRCK edge
    reg msb;
    always @(posedge BCK)
        msb <= lrck_edge;

    // ============================================================
    // 2) DATA PIPELINE (7 / 39 delay structure)
    // ============================================================
    reg [7:0]  sr_r;   // right delay
    reg [31:0] sr_l;   // left delay

    always @(posedge BCK) begin
        sr_r <= {sr_r[6:0], DATAIN};
        sr_l <= {sr_l[30:0], sr_r[7]};
    end

    assign DATAOUTR = sr_r[7];     // 7-cycle delay
    assign DATAOUTL = sr_l[31];    // 39-cycle delay

    // ============================================================
    // 3) COMPRESSED MARKER (12-stage)
    // Tracks MSB position (~24 cycles effectively)
    // ============================================================
    reg [11:0] mk;

    always @(posedge BCK) begin
        mk <= {mk[10:0], msb};
    end

    // Approximate 24-bit position
    wire bit24 = mk[11];

    // ============================================================
    // 4) CLOCK OUTPUT (direct)
    // ============================================================
    assign CLKOUTR = BCK;
    assign CLKOUTL = BCK;

    // ============================================================
    // 5) LE GENERATION (data-aligned, CPLD-safe)
    // ============================================================

    // Raw LE windows
    wire le_r_raw = bit24 & ~LRCK;
    wire le_l_raw = bit24 &  LRCK;

    // Edge shaping → 1-cycle pulse
    reg le_r_d, le_l_d;

    always @(posedge BCK) begin
        le_r_d <= le_r_raw;
        le_l_d <= le_l_raw;
    end

    wire le_r_pulse = le_r_raw & ~le_r_d;
    wire le_l_pulse = le_l_raw & ~le_l_d;

    // PCM1704 latches on FALLING edge
    assign LEOUTR = ~le_r_pulse;
    assign LEOUTL = ~le_l_pulse;

    // ============================================================
    // 6) LED (optional)
    // ============================================================
    assign LED1 = 1'b0;

endmodule
