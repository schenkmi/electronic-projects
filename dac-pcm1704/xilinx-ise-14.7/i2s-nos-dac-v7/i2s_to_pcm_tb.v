`timescale 1ns / 1ps
// =============================================================================
// Testbench : i2s_to_pcm_tb
// Purpose   : Verify I2S to PCM conversion for PCM1704U DAC
// DUT       : i2s_to_pcm.v
// =============================================================================

`define CLK_PERIOD    20      // 50 MHz BCK (20 ns period)
`define LRCK_PERIOD   1280    // 64 clocks per channel * 20 ns = 1280 ns for 48 kHz
`define NUM_CYCLES    200     // Number of BCK cycles to simulate

module i2s_to_pcm_tb;

    // -------------------------------------------------------------------------
    // Testbench signals
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
    // Test data - 24-bit patterns for verification
    // Left channel:  0x123456 (example audio data)
    // Right channel: 0xFEDCBA (example audio data)
    // -------------------------------------------------------------------------
    `define LEFT_DATA  24'h123456
    `define RIGHT_DATA 24'hFEDCBA

    // -------------------------------------------------------------------------
    // Shift register for monitoring expected output
    // -------------------------------------------------------------------------
    reg [31:0] expected_right;
    reg [31:0] expected_left;
    integer    bck_count;
    integer    frame_count;

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
    // BCK clock generation - 50 MHz
    // -------------------------------------------------------------------------
    initial begin
        BCK = 1'b0;
        forever #(`CLK_PERIOD / 2) BCK = ~BCK;
    end

    // -------------------------------------------------------------------------
    // Stimulus generator
    // -------------------------------------------------------------------------
    initial begin
        integer i;
        reg [31:0] left_shift;
        reg [31:0] right_shift;

        // Initialize
        DATAIN = 1'b0;
        LRCK   = 1'b0;  // Start with left channel

        // Wait for reset propagation
        #100;

        $display("========================================");
        $display("I2S to PCM Converter Testbench");
        $display("========================================");
        $display("Time %0t ns: Starting I2S transmission", $time);

        // Generate multiple I2S frames
        for (frame_count = 0; frame_count < 5; frame_count = frame_count + 1) begin
            // -------------------------------------------------------------
            // LEFT CHANNEL (LRCK = 0)
            // -------------------------------------------------------------
            LRCK = 1'b0;
            #(`CLK_PERIOD / 2);  // Wait half cycle before data starts

            // Shift out left channel data MSB first (32 bits, but only 24 valid)
            left_shift = {`LEFT_DATA, 8'h00};  // 24-bit data + 8 LSB zeros
            for (i = 0; i < 32; i = i + 1) begin
                #`CLK_PERIOD;
                DATAIN = left_shift[31];
                left_shift = left_shift << 1;
            end

            $display("Time %0t ns: Left channel frame %0d complete", $time, frame_count);

            // -------------------------------------------------------------
            // RIGHT CHANNEL (LRCK = 1)
            // -------------------------------------------------------------
            LRCK = 1'b1;
            #(`CLK_PERIOD / 2);  // Wait half cycle before data starts

            // Shift out right channel data MSB first (32 bits, but only 24 valid)
            right_shift = {`RIGHT_DATA, 8'h00};  // 24-bit data + 8 LSB zeros
            for (i = 0; i < 32; i = i + 1) begin
                #`CLK_PERIOD;
                DATAIN = right_shift[31];
                right_shift = right_shift << 1;
            end

            $display("Time %0t ns: Right channel frame %0d complete", $time, frame_count);
        end

        $display("Time %0t ns: Test sequence complete", $time);
        $display("========================================");

        // Run for a bit more to let data propagate through
        #500;

        // End simulation
        #100 $finish;
    end

    // -------------------------------------------------------------------------
    // Monitor: Check PCM output data
    // -------------------------------------------------------------------------
    integer capture_count;
    reg [23:0] captured_right;
    reg [23:0] captured_left;

    always @(posedge LEOUTR) begin
        // Capture 24 bits on each LEOUTR rising edge (end of right channel)
        capture_count = capture_count + 1;
        captured_right = 24'h0;  // Placeholder - DATAOUTR is 1-bit
    end

    always @(posedge LEOUTL) begin
        // Capture 24 bits on each LEOUTL rising edge (end of left channel)
        capture_count = capture_count + 1;
    end

    // -------------------------------------------------------------------------
    // Data integrity checker
    // -------------------------------------------------------------------------
    reg [39:0] bit_stream;  // Enough to cover max delay

    always @(posedge BCK) begin
        bit_stream <= {bit_stream[38:0], DATAIN};
    end

    // Check right channel data (after 7-bit delay)
    always @(posedge CLKOUTR) begin
        if (LEOUTR === 1'b0) begin  // During right channel data window
            if (bit_stream[7] !== DATAOUTR) begin
                $display("WARNING: Time %0t ns - Right channel data mismatch", $time);
                $display("  Expected: %b, Got: %b", bit_stream[7], DATAOUTR);
            end
        end
    end

    // -------------------------------------------------------------------------
    // Waveform dump for GTKWave
    // -------------------------------------------------------------------------
    initial begin
        $dumpfile("i2s_to_pcm_tb.vcd");
        $dumpvars(0, i2s_to_pcm_tb);
    end

    // -------------------------------------------------------------------------
    // Initial conditions
    // -------------------------------------------------------------------------
    initial begin
        capture_count = 0;
        bit_stream = 40'h0;
        bck_count = 0;
    end

    // -------------------------------------------------------------------------
    // Cycle counter
    // -------------------------------------------------------------------------
    always @(posedge BCK) begin
        bck_count <= bck_count + 1;
    end

    // -------------------------------------------------------------------------
    // Status display
    // -------------------------------------------------------------------------
    initial begin
        $monitor("Time %0t ns | BCK=%b | LRCK=%b | DATAIN=%b | DATAOUTR=%b | DATAOUTL=%b | LEOUTR=%b | LEOUTL=%b",
            $time, BCK, LRCK, DATAIN, DATAOUTR, DATAOUTL, LEOUTR, LEOUTL);
    end

    // -------------------------------------------------------------------------
    // LED status check (assertions not supported by Icarus Verilog)
    // -------------------------------------------------------------------------
    always @(posedge BCK) begin
        if (LED1 !== 1'b0) begin
            $display("WARNING: LED1 should be low (active-low)");
        end
    end

endmodule
