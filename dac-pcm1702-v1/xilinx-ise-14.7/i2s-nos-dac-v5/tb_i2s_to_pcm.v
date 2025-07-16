`timescale 1ns / 1ps

// iverilog -o sim.vvp i2s_to_pcm.v tb_i2s_to_pcm.v
// vvp sim.vvp
// gtkwave i2s_to_pcm.vcd

module tb_i2s_to_pcm;

    reg clk = 0;
    always #10 clk = ~clk;  // BCLK = 50 MHz

    reg lrck = 0;
    reg sdata = 0;


    wire dac_bck_l, dac_bck_r;
    wire dac_data_l, dac_data_r;
    wire dac_le_l, dac_le_r;
	 wire led1;
	 
	 

    i2s_to_pcm uut (
        .BCK(clk),
        .LRCK(lrck),
        .DATAIN(sdata),
        .CLKOUTR(dac_bck_r),
		  .LEOUTR(dac_le_r),
		  .DATAOUTR(dac_data_r),
        .CLKOUTL(dac_bck_l),
		  .LEOUTL(dac_le_l),
		  .DATAOUTL(dac_data_l),
		  .LED1(led1)
    );

    // Sample generator
    reg [23:0] test_sample_l = 24'hA5A5A5;
    reg [23:0] test_sample_r = 24'h5A5A5A;

    integer i;

    task send_i2s_frame(input [23:0] left, input [23:0] right);
        begin
            // Left channel
            lrck = 0;
            for (i = 23; i >= 0; i = i - 1) begin
                @(negedge clk);
                sdata = left[i];
            end

            // Right channel
            lrck = 1;
            for (i = 23; i >= 0; i = i - 1) begin
                @(negedge clk);
                sdata = right[i];
            end
        end
    endtask

    initial begin
        $dumpfile("i2s_to_pcm.vcd");
        $dumpvars(0, tb_i2s_to_pcm);


        // Send a few samples
        repeat (4) begin
            send_i2s_frame(test_sample_l, test_sample_r);
            test_sample_l = test_sample_l + 24'h010101;
            test_sample_r = test_sample_r - 24'h010101;
        end

        #1000 $finish;
    end

endmodule


