`timescale 1ns / 1ps
// =============================================================================
// Testbench : i2s_to_pcm_tb_simple
// Purpose   : Simple verification of I2S to PCM conversion
//             Outputs verification messages when data matches expected values
// =============================================================================

module i2s_to_pcm_tb_simple;

    // -------------------------------------------------------------------------
    // Testbench signals
    // -------------------------------------------------------------------------
    reg  BCK = 1'b0;
    reg  LRCK = 1'b0;
    reg  DATAIN = 1'b0;

    wire CLKOUTR;
    wire LEOUTR;
    wire DATAOUTR;
    wire CLKOUTL;
    wire LEOUTL;
    wire DATAOUTL;
    wire LED1;

    // -------------------------------------------------------------------------
    // Test parameters
    // -------------------------------------------------------------------------
    `define CLK_PERIOD  20      // 50 MHz BCK
    `define LEFT_DATA   24'h5AA55A
    `define RIGHT_DATA  24'hA55AA5

    // -------------------------------------------------------------------------
    // DUT instantiation
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
    // Clock generation
    // -------------------------------------------------------------------------
    always #(`CLK_PERIOD / 2) BCK = ~BCK;

    // -------------------------------------------------------------------------
    // Internal shift registers for expected data calculation
    // -------------------------------------------------------------------------
    reg [47:0] input_history;  // Track last 48 bits of input

    always @(posedge BCK) begin
        input_history <= {input_history[46:0], DATAIN};
    end

    // -------------------------------------------------------------------------
    // Verification logic
    // -------------------------------------------------------------------------
    reg [23:0] expected_right_data;
    reg [23:0] expected_left_data;
    reg [23:0] captured_right;
    reg [23:0] captured_left;
    integer errors = 0;
    integer right_samples = 0;
    integer left_samples = 0;

    // Build expected data by shifting in the test pattern
    reg [39:0] tx_right;
    reg [39:0] tx_left;
    integer bit_idx;

    // -------------------------------------------------------------------------
    // Main stimulus
    // -------------------------------------------------------------------------
    initial begin
        integer i;

        $display("");
        $display("================================================");
        $display("I2S to PCM Converter - Simple Verification");
        $display("================================================");
        $display("Left  data pattern: 0x%h", `LEFT_DATA);
        $display("Right data pattern: 0x%h", `RIGHT_DATA);
        $display("================================================");
        $display("");

        // Initialize
        DATAIN = 1'b0;
        LRCK = 1'b0;
        #50;

        // Transmit 3 complete I2S frames (left + right)
        for (i = 0; i < 3; i = i + 1) begin
            // ----- LEFT CHANNEL (LRCK = 0) -----
            LRCK = 1'b0;
            #(`CLK_PERIOD / 2);

            // Send 32 bits: 24-bit LEFT_DATA + 8 LSB zeros
            tx_left = {`LEFT_DATA, 8'h00};
            for (bit_idx = 0; bit_idx < 32; bit_idx = bit_idx + 1) begin
                #`CLK_PERIOD;
                DATAIN = tx_left[31];
                tx_left = tx_left << 1;
            end

            // ----- RIGHT CHANNEL (LRCK = 1) -----
            LRCK = 1'b1;
            #(`CLK_PERIOD / 2);

            // Send 32 bits: 24-bit RIGHT_DATA + 8 LSB zeros
            tx_right = {`RIGHT_DATA, 8'h00};
            for (bit_idx = 0; bit_idx < 32; bit_idx = bit_idx + 1) begin
                #`CLK_PERIOD;
                DATAIN = tx_right[31];
                tx_right = tx_right << 1;
            end
        end

        // Let data propagate through the delays
        #1000;

        $display("");
        $display("================================================");
        $display("Simulation complete");
        $display("Right samples captured: %0d", right_samples);
        $display("Left  samples captured: %0d", left_samples);
        $display("Total errors: %0d", errors);
        $display("================================================");

        if (errors == 0) begin
            $display("TEST PASSED: All data verified correctly");
        end else begin
            $display("TEST FAILED: %0d mismatches detected", errors);
        end

        $finish;
    end

    // -------------------------------------------------------------------------
    // Capture and verify right channel data on LEOUTR falling edge
    // -------------------------------------------------------------------------
    reg [5:0] right_bit_count;
    reg [23:0] right_capture;

    always @(negedge LEOUTR) begin
        if (LRCK === 1'b0) begin  // Right channel window ending
            // Capture the 24 bits that should be our right data
            right_capture = 24'h0;
            right_bit_count = 0;
        end
    end

    always @(posedge CLKOUTR) begin
        if (LEOUTR === 1'b0 && right_bit_count < 24) begin
            right_capture[right_bit_count] = DATAOUTR;
            right_bit_count = right_bit_count + 1;
        end
    end

    always @(posedge LEOUTR) begin
        if (right_samples > 0) begin  // Skip first capture (invalid data)
            // DataOUTR is MSB first, so we need to check
            // The captured data should match RIGHT_DATA
            if ({right_capture[23], right_capture[22:0]} === `RIGHT_DATA) begin
                $display("Time %0t ns [RIGHT] PASS - Captured: 0x%h", $time, right_capture);
            end else begin
                $display("Time %0t ns [RIGHT] FAIL - Expected: 0x%h, Got: 0x%h",
                    $time, `RIGHT_DATA, right_capture);
                errors = errors + 1;
            end
        end
        right_samples = right_samples + 1;
    end

    // -------------------------------------------------------------------------
    // Capture and verify left channel data on LEOUTL falling edge
    // -------------------------------------------------------------------------
    reg [5:0] left_bit_count;
    reg [23:0] left_capture;

    always @(negedge LEOUTL) begin
        if (LRCK === 1'b1) begin  // Left channel window ending
            left_capture = 24'h0;
            left_bit_count = 0;
        end
    end

    always @(posedge CLKOUTL) begin
        if (LEOUTL === 1'b0 && left_bit_count < 24) begin
            left_capture[left_bit_count] = DATAOUTL;
            left_bit_count = left_bit_count + 1;
        end
    end

    always @(posedge LEOUTL) begin
        if (left_samples > 0) begin  // Skip first capture (invalid data)
            if ({left_capture[23], left_capture[22:0]} === `LEFT_DATA) begin
                $display("Time %0t ns [LEFT]  PASS - Captured: 0x%h", $time, left_capture);
            end else begin
                $display("Time %0t ns [LEFT]  FAIL - Expected: 0x%h, Got: 0x%h",
                    $time, `LEFT_DATA, left_capture);
                errors = errors + 1;
            end
        end
        left_samples = left_samples + 1;
    end

    // -------------------------------------------------------------------------
    // Waveform dump
    // -------------------------------------------------------------------------
    initial begin
        $dumpfile("i2s_to_pcm_simple.vcd");
        $dumpvars(0, i2s_to_pcm_tb_simple);
    end

    // -------------------------------------------------------------------------
    // Monitor (optional - uncomment for detailed tracing)
    // -------------------------------------------------------------------------
    // initial begin
    //     $monitor("T=%0t | LRCK=%b | DATAIN=%b | DATAOUTR=%b | DATAOUTL=%b",
    //         $time, LRCK, DATAIN, DATAOUTR, DATAOUTL);
    // end

endmodule
