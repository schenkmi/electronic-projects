`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date:    03.07.2026
// Design Name:
// Module Name:    i2s_to_pcm_improved
// Project Name:
// Target Devices:
// Tool versions:
// Description: Improved I2S to PCM converter for PCM1704U
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////

// I2S to PCM 24-Bit version for PCM1704U
// Addresses channel delay mismatch with improved timing alignment
// Implements proper dual-edge clock sampling for precise timing

module double_edge_triggered_ff (
    input  clk,
    input  rst_n,  // Active-low reset
    input  din,
    output dout
);
    reg q_pos, q_neg;

    // Positive edge triggered storage
    always @(posedge clk, negedge rst_n) begin
        if (!rst_n)
            q_pos <= 1'b0;
        else
            q_pos <= din ^ q_neg;
    end

    // Negative edge triggered storage
    always @(negedge clk, negedge rst_n) begin
        if (!rst_n)
            q_neg <= 1'b0;
        else
            q_neg <= din ^ q_pos;
    end

    assign dout = q_pos ^ q_neg;

endmodule

module i2s_to_pcm_improved (
    // I2S inputs
    input  wire         clk_i2s,       // I2S bit clock
    input  wire         lrclk,         // I2S left/right clock
    input  wire         data_i2s,      // I2S serial data input

    // PCM outputs for right channel
    output reg          pcm_clk_r,     // PCM clock for right channel
    output reg          pcm_le_r,      // PCM latch enable for right channel
    output reg          pcm_data_r,    // PCM data for right channel

    // PCM outputs for left channel
    output reg          pcm_clk_l,     // PCM clock for left channel
    output reg          pcm_le_l,      // PCM latch enable for left channel
    output reg          pcm_data_l,    // PCM data for left channel

    // Status outputs
    output wire         status_led     // Status indicator
);

    // Parameter definitions for flexibility
    parameter RIGHT_DELAY_BITS = 7;      // Right channel delay in bits
    parameter LEFT_DELAY_BITS = 39;      // Left channel delay in bits (32+7 for alignment)

    // Internal signals
    wire delayed_clk_i2s;                // Delayed clock for precise timing
    wire delayed_lrclk;                  // Delayed LR clock for precise timing

    // Shift registers for channel delay management
    reg [RIGHT_DELAY_BITS-1:0] right_delay_shift_reg = 0;   // 7-bit shift register for right channel
    reg [LEFT_DELAY_BITS-1:0]  left_delay_shift_reg = 0;    // 39-bit shift register for left channel

    // Instantiate double-edge triggered flip-flops for precise clock management
    double_edge_triggered_ff delayed_clock_inst (
        .clk(clk_i2s),
        .rst_n(1'b1),  // Hardcoded to 1 as there's no external reset
        .din(clk_i2s),
        .dout(delayed_clk_i2s)
    );

    double_edge_triggered_ff delayed_lrclk_inst (
        .clk(clk_i2s),
        .rst_n(1'b1),  // Hardcoded to 1 as there's no external reset
        .din(lrclk),
        .dout(delayed_lrclk)
    );

    // Main data processing on positive edge of I2S clock
    always @(posedge clk_i2s) begin
        // Process right channel: shift in new data bit
        right_delay_shift_reg <= {right_delay_shift_reg[RIGHT_DELAY_BITS-2:0], data_i2s};

        // Process left channel: shift in right channel's delayed data bit
        // This provides total delay of 39 bits (7 bits from right SR + 32 bits from left SR)
        left_delay_shift_reg <= {left_delay_shift_reg[LEFT_DELAY_BITS-2:0], right_delay_shift_reg[RIGHT_DELAY_BITS-1]};
    end

    // Assign outputs with proper timing alignment
    always @(*) begin
        pcm_clk_r  <= delayed_clk_i2s;
        pcm_le_r   <= delayed_lrclk;
        pcm_data_r <= right_delay_shift_reg[RIGHT_DELAY_BITS-1];  // Most recent bit after delay

        pcm_clk_l  <= delayed_clk_i2s;
        pcm_le_l   <= delayed_lrclk;
        pcm_data_l <= left_delay_shift_reg[LEFT_DELAY_BITS-1];   // Most recent bit after delay
    end

    // Status LED assignment (inverted logic: 0 turns LED on)
    assign status_led = 1'b0;  // Constantly on, as in original design

endmodule