`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    07.05.2025
// Design Name: 
// Module Name:    i2s_to_pcm 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

// I2S to PCM 24Bit version for PCM1704U
// Right 7bit data delay
// Left 39bit (32bit + 7bit) data delay

// program with Digilent HS3
//   openFPGALoader -c digilent_hs3 --freq 1000000 -v *.jed
// or 
//   xc3sprog -c jtaghs2 -m /opt/Xilinx/14.7/ISE_DS/ISE/xbr/data -J 1000000 -p 0 -v *.jed

// git clean -d -x -f .


// double edge triggered flip-fop
module double_edge_flip_flop(
  input clock, reset, in,
  output out
);
  reg trig1, trig2;

  assign out = trig1^trig2;

  always @(posedge clock, posedge reset) begin
    if (reset)
      trig1 <= 0;
    else
      trig1 <= in^trig2;
  end

  always @(negedge clock, posedge reset) begin
    if (reset)
      trig2 <= 0;
    else
      trig2 <= in^trig1;
  end
endmodule


module i2s_to_pcm(
    input BCK,
    input LRCK,
    input DATAIN,
    output CLKOUTR,
    output LEOUTR,
    output DATAOUTR,
    output CLKOUTL,
    output LEOUTL,  
    output DATAOUTL,
    output LED1
);

    reg [7:0] sr_right; // 7bit shift register
    reg [31:0] sr_left; // 32bit shift register
    //reg delay_bck;
    //reg delay_lrck;	 
    wire delay_bck;
    wire delay_lrck;

    double_edge_flip_flop deff_bck (.clock(BCK), .reset(0), .in(BCK), .out(delay_bck));
    double_edge_flip_flop deff_lrck (.clock(BCK), .reset(0),.in(LRCK), .out(delay_lrck));

    always @(posedge BCK) begin
		  // shift DATAIN by 7 bit right channel
		  // 32bit - 24bit -1bit (I2S)
		  sr_right <= {sr_right[6:0], DATAIN};  
		  
		  // shift DATAIN by 39 bit (32bit + 7bit) left channel
		  // delay left channel by 32bit
		  sr_left <= {sr_left[30:0], sr_right[7]};
    end

/*	 // to maintain timing
	 // Xilinx XC2C64A supports dual edge flip flops
	 always @(posedge BCK or negedge BCK) begin
		delay_bck <= BCK;
		delay_lrck <= LRCK;
	 end
	 */
    // Capture the data from the last stage, before it is lost
    assign CLKOUTR = delay_bck;
    assign LEOUTR = delay_lrck;
    assign DATAOUTR = sr_right[7];

    assign CLKOUTL = delay_bck;
    assign LEOUTL = delay_lrck;
    assign DATAOUTL = sr_left[31];
	
    assign LED1 = 0; // 0 => LED on, 1 => LED off
endmodule
