`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Testbench for I2S to PCM converter
//////////////////////////////////////////////////////////////////////////////////

module i2s_to_pcm_tb;

    // Test signals
    reg clk_i2s;
    reg lrclk;
    reg data_i2s;

    // Outputs
    wire pcm_clk_r;
    wire pcm_le_r;
    wire pcm_data_r;
    wire pcm_clk_l;
    wire pcm_le_l;
    wire pcm_data_l;
    wire status_led;

    // Instantiate the Unit Under Test (UUT)
    i2s_to_pcm_improved uut (
        .clk_i2s(clk_i2s),
        .lrclk(lrclk),
        .data_i2s(data_i2s),
        .pcm_clk_r(pcm_clk_r),
        .pcm_le_r(pcm_le_r),
        .pcm_data_r(pcm_data_r),
        .pcm_clk_l(pcm_clk_l),
        .pcm_le_l(pcm_le_l),
        .pcm_data_l(pcm_data_l),
        .status_led(status_led)
    );

    // Generate 100MHz I2S clock (typical for audio applications)
    initial begin
        clk_i2s = 0;
        forever #5 clk_i2s = ~clk_i2s;  // 100MHz clock (period = 10ns)
    end

    // Generate LR clock (fs/32 for typical I2S - 48kHz sample rate with 64x BCK)
    initial begin
        lrclk = 0;
        forever begin
            #(32*10) lrclk = ~lrclk;  // Toggle every 32 BCK cycles
        end
    end

    // Generate test data pattern
    initial begin
        integer i;
        data_i2s = 0;

        // Wait for reset to complete
        #20;

        // Send a known data pattern
        for (i = 0; i < 1000; i = i + 1) begin
            // Send alternating pattern to both channels
            data_i2s = (i % 2) ? 1 : 0;
            #(10);  // One bit clock period
        end

        $finish;
    end

    // Monitor outputs
    initial begin
        $monitor("Time=%0t ns | BCK=%b LRCK=%b DIN=%b | R_CLK=%b R_LE=%b R_DATA=%b | L_CLK=%b L_LE=%b L_DATA=%b",
                 $time, clk_i2s, lrclk, data_i2s, pcm_clk_r, pcm_le_r, pcm_data_r,
                 pcm_clk_l, pcm_le_l, pcm_data_l);
    end

    // Dump waves for viewing
    initial begin
        $dumpfile("i2s_to_pcm_tb.vcd");
        $dumpvars(0, i2s_to_pcm_tb);
    end

endmodule