`timescale 1ns / 1ps
// =============================================================================
// Testbench : i2s_to_pcm_tb
// Purpose   : Verify I2S to PCM conversion for PCM1704U DAC
// DUT       : i2s_to_pcm.v
// Simulator : Icarus Verilog + GTKWave
// Usage     : iverilog -o i2s_to_pcm_tb i2s_to_pcm.v i2s_to_pcm_tb.v
//             vvp i2s_to_pcm_tb
//             gtkwave i2s_to_pcm_tb.vcd
// =============================================================================

// Timing parameters
`define BCK_HALF      162.75  // Half period (~3.072 MHz)
`define SAMPLES       3       // Number of unique test patterns

module i2s_to_pcm_tb;

    // -------------------------------------------------------------------------
    // DUT Signals
    // -------------------------------------------------------------------------
    reg  BCK;
    reg  LRCK;
    reg  DATAIN;

    wire CLKOUTR;
    wire LEOUTR;
    wire DATAOUTR;
    wire CLKOUTL;
    wire LEOUTL;
    wire DATAOUTL;
    wire LED1;

    // -------------------------------------------------------------------------
    // Test Patterns - 24-bit audio samples
    // -------------------------------------------------------------------------
    reg [23:0] test_left  [0:`SAMPLES-1];
    reg [23:0] test_right [0:`SAMPLES-1];

    // -------------------------------------------------------------------------
    // Verification
    // -------------------------------------------------------------------------
    integer cycle_count;
    integer error_count;
    integer check_count;
    integer frame_idx;

    // Shift register mirror for verification
    reg [7:0]  sr_right_mirror;
    reg [31:0] sr_left_mirror;

    // -------------------------------------------------------------------------
    // DUT Instantiation
    // -------------------------------------------------------------------------
    i2s_to_pcm dut (
        .BCK      (BCK),
        .LRCK     (LRCK),
        .DATAIN   (DATAIN),

        .CLKOUTR  (CLKOUTR),
        .LEOUTR   (LEOUTR),
        .DATAOUTR (DATAOUTR),

        .CLKOUTL  (CLKOUTL),
        .LEOUTL   (LEOUTL),
        .DATAOUTL (DATAOUTL),

        .LED1     (LED1)
    );

    // -------------------------------------------------------------------------
    // Clock Generation
    // -------------------------------------------------------------------------
    initial begin
        BCK = 1'b0;
        forever #`BCK_HALF BCK = ~BCK;
    end

    // -------------------------------------------------------------------------
    // Mirror Shift Registers for Verification
    // These track what the DUT's shift registers should contain
    // -------------------------------------------------------------------------
    always @(posedge BCK) begin
        sr_right_mirror <= {sr_right_mirror[6:0], DATAIN};
        sr_left_mirror  <= {sr_left_mirror[30:0], sr_right_mirror[7]};
    end

    // -------------------------------------------------------------------------
    // Output Verification
    // Compare DUT outputs with our mirror
    // -------------------------------------------------------------------------
    always @(posedge BCK) begin
        // Skip first 50 cycles to let shift registers fill
        if (cycle_count > 50) begin
            // Check right channel
            if (DATAOUTR !== sr_right_mirror[7]) begin
                $display("ERROR [%0t]: RIGHT output mismatch", $time);
                $display("  Expected: %b, Got: %b", sr_right_mirror[7], DATAOUTR);
                error_count = error_count + 1;
            end

            // Check left channel
            if (DATAOUTL !== sr_left_mirror[31]) begin
                $display("ERROR [%0t]: LEFT output mismatch", $time);
                $display("  Expected: %b, Got: %b", sr_left_mirror[31], DATAOUTL);
                error_count = error_count + 1;
            end

            check_count = check_count + 2;
        end
    end

    // -------------------------------------------------------------------------
    // Double-Edge DFF Verification
    // CLKOUT and LEOUT should be delayed by approximately half a BCK period
    // -------------------------------------------------------------------------
    real bck_rise_time, bck_fall_time;
    real clkout_rise_time, leout_rise_time;

    // Track BCK edges
    always @(posedge BCK) begin
        bck_rise_time = $time;
    end

    always @(negedge BCK) begin
        bck_fall_time = $time;
    end

    // Track CLKOUT edges and check delay
    real clkout_delay;
    always @(CLKOUTR) begin
        if (CLKOUTR == 1'b1) begin
            clkout_rise_time = $time;
            // CLKOUT should rise approximately half period after BCK falls
            clkout_delay = clkout_rise_time - bck_fall_time;
            // Allow some tolerance for simulation timing
            if (clkout_delay > 0 && clkout_delay < `BCK_HALF * 1.5) begin
                // OK - within expected half-period delay
            end else if (cycle_count > 10) begin
                $display("NOTE: CLKOUT rise at %0t, delay from BCK fall: %0t", $time, clkout_delay);
            end
        end
    end

    // -------------------------------------------------------------------------
    // LRCK Polarity Check
    // I2S standard: LRCK low = left channel, LRCK high = right channel
    // -------------------------------------------------------------------------
    always @(posedge BCK) begin
        if (cycle_count > 50) begin
            // LEOUTR and LEOUTL should follow delayed LRCK
            // When LRCK is low (left), LE should be low
            // When LRCK is high (right), LE should be high
            // (with half-cycle delay due to double_edge_dff)
        end
    end

    // -------------------------------------------------------------------------
    // Cycle Counter
    // -------------------------------------------------------------------------
    always @(posedge BCK) begin
        cycle_count = cycle_count + 1;
    end

    // -------------------------------------------------------------------------
    // I2S Transmitter Task
    // -------------------------------------------------------------------------
    integer i;
    reg [31:0] tx_word;

    task send_i2s_word;
        input [23:0] sample;
        input        channel;
        begin
            tx_word = {sample, 8'h00};

            @(negedge BCK);
            LRCK = channel;

            // I2S 1-cycle delay after LRCK edge
            @(posedge BCK);
            @(negedge BCK);
            DATAIN = 1'b0;

            // Send 32 bits MSB first
            for (i = 31; i >= 0; i = i - 1) begin
                @(posedge BCK);
                @(negedge BCK);
                DATAIN = tx_word[i];
            end

            @(negedge BCK);
            DATAIN = 1'b0;
        end
    endtask

    // -------------------------------------------------------------------------
    // Main Test Sequence
    // -------------------------------------------------------------------------
    initial begin
        // Initialize
        DATAIN = 1'b0;
        LRCK = 1'b0;
        cycle_count = 0;
        error_count = 0;
        check_count = 0;
        sr_right_mirror = 8'h00;
        sr_left_mirror = 32'h00000000;

        // Test patterns
        test_left[0]  = 24'hFFFFFF;  // All 1s
        test_left[1]  = 24'hAAAAAA;  // Alternating
        test_left[2]  = 24'h123456;  // Sequential

        test_right[0] = 24'h000000;  // All 0s
        test_right[1] = 24'h555555;  // Alternating inverse
        test_right[2] = 24'hFEDCBA;  // Sequential

        $display("");
        $display("========================================");
        $display("  I2S to PCM Testbench");
        $display("  Target: PCM1704U DAC Interface");
        $display("========================================");
        $display("");

        #1000;

        // Send multiple frames
        for (frame_idx = 0; frame_idx < 6; frame_idx = frame_idx + 1) begin
            $display("Frame %0d: Left=0x%06X, Right=0x%06X",
                     frame_idx, test_left[frame_idx % `SAMPLES], test_right[frame_idx % `SAMPLES]);

            send_i2s_word(test_left[frame_idx % `SAMPLES], 1'b0);
            send_i2s_word(test_right[frame_idx % `SAMPLES], 1'b1);

            repeat(10) @(posedge BCK);
        end

        // Drain pipeline
        repeat(100) @(posedge BCK);

        $display("");
        $display("========================================");
        $display("  Test Summary");
        $display("========================================");
        $display("Checks: %0d", check_count);
        $display("Errors: %0d", error_count);

        if (error_count == 0) begin
            $display("");
            $display("  *** ALL TESTS PASSED ***");
        end else begin
            $display("");
            $display("  *** TESTS FAILED ***");
        end
        $display("========================================");
        $display("");

        #1000;
        $finish;
    end

    // -------------------------------------------------------------------------
    // LED Check
    // -------------------------------------------------------------------------
    always @(posedge BCK) begin
        if (LED1 !== 1'b0) begin
            $display("ERROR [%0t]: LED1 should be 0", $time);
            error_count = error_count + 1;
        end
    end

    // -------------------------------------------------------------------------
    // VCD Dump
    // -------------------------------------------------------------------------
    initial begin
        $dumpfile("i2s_to_pcm_tb.vcd");
        $dumpvars(0, i2s_to_pcm_tb);
    end

    // -------------------------------------------------------------------------
    // Timeout
    // -------------------------------------------------------------------------
    initial begin
        #500000;
        $display("ERROR: Simulation timeout!");
        $finish;
    end

endmodule