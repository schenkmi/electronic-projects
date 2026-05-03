`timescale 1ns / 1ps

module tb_i2s_to_pcm;

    // ------------------------------------------------------------
    // DUT signals
    // ------------------------------------------------------------
    reg BCK   = 0;
    reg LRCK  = 0;
    reg DATAIN = 0;

    wire CLKOUTR, LEOUTR, DATAOUTR;
    wire CLKOUTL, LEOUTL, DATAOUTL;
    wire LED1;

    // ------------------------------------------------------------
    // Instantiate DUT
    // ------------------------------------------------------------
    i2s_to_pcm dut (
        .BCK(BCK),
        .LRCK(LRCK),
        .DATAIN(DATAIN),

        .CLKOUTR(CLKOUTR),
        .LEOUTR(LEOUTR),
        .DATAOUTR(DATAOUTR),

        .CLKOUTL(CLKOUTL),
        .LEOUTL(LEOUTL),
        .DATAOUTL(DATAOUTL),

        .LED1(LED1)
    );

    // ------------------------------------------------------------
    // Clock generation (BCK)
    // ------------------------------------------------------------
    // 10 MHz → 100 ns period (easy to inspect)
    always #50 BCK = ~BCK;

    // slower clock
    //always #200 BCK = ~BCK;

    // ------------------------------------------------------------
    // I2S stimulus
    // ------------------------------------------------------------
    reg [31:0] sample_l = 32'hA5A5A5A5;
    reg [31:0] sample_r = 32'h5A5A5A5A;

    integer bit_cnt = 0;

    always @(posedge BCK) begin
        bit_cnt <= bit_cnt + 1;

        // Toggle LRCK every 32 bits
        if (bit_cnt == 31) begin
            LRCK <= ~LRCK;
            bit_cnt <= 0;
        end

        // I2S: MSB appears 1 clock after LRCK edge
        if (LRCK == 0) begin
            // LEFT channel
            DATAIN <= sample_l[31 - bit_cnt];
        end else begin
            // RIGHT channel
            DATAIN <= sample_r[31 - bit_cnt];
        end
    end

    // ------------------------------------------------------------
    // VCD dump for GTKWave
    // ------------------------------------------------------------
    initial begin
        $dumpfile("i2s_pcm.vcd");
        $dumpvars(0, tb_i2s_to_pcm);
    end

    // ------------------------------------------------------------
    // Simulation runtime
    // ------------------------------------------------------------
    initial begin
        #20000;  // run long enough for several frames
        $finish;
    end

endmodule

