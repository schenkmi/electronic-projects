`timescale 1ns / 1ps
/*
 * Copyright (c) 2013, Stefan Kristiansson <stefan.kristiansson@saunalahti.fi>
 * All rights reserved.
 *
 * Redistribution and use in source and non-source forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in non-source form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS WORK IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * WORK, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


// https://github.com/MatejGomboc/Verilog-I2S-Transciever/tree/master
// https://github.com/skristiansson/i2s/tree/master




module i2s_rx #(
	parameter AUDIO_DW		= 32
)(
	input				sclk,
	input				rst,

	input				lrclk,
	input				sdata,

	// Parallel datastreams
	output reg [AUDIO_DW-1:0]	left_chan,
	output reg [AUDIO_DW-1:0]	right_chan,
	
	output reg clk_out,
	output reg data_left,
	output reg data_right
	
);

reg [AUDIO_DW-1:0]	left;
reg [AUDIO_DW-1:0]	right;
reg			lrclk_r;
wire			lrclk_nedge;



reg [AUDIO_DW-1:0]	dac_left; // output shift reg
reg [AUDIO_DW-1:0]	dac_right; // output shift reg

// ping/pong register 32bit

reg ping_pong;

reg [AUDIO_DW-1:0]	dac_right_dbl [0:1];

// see https://systemverilogdesign.com/tag/fall-edge-detect/
// see https://rtldigitaldesign.blogspot.com/2014/06/pos-n-neg-edge-detector.html
// https://cospandesign.github.io/fpga,fifo/2016/05/02/ppfifo.html


assign lrclk_nedge = !lrclk & lrclk_r;

always @(posedge sclk)
	lrclk_r <= lrclk;


always @(posedge sclk) 
	if (rst) begin 
		clk_out <= 1'b0;
	end else begin
		clk_out <=  ! clk_out ; 
end
 

// sdata msb is valid one clock cycle after lrclk switches
always @(posedge sclk)
	if (lrclk_r)
		right <= {right[AUDIO_DW-2:0], sdata};
	else
		left <= {left[AUDIO_DW-2:0], sdata};

always @(posedge sclk)
	if (rst) begin
		left_chan <= 0;
		right_chan <= 0;
		ping_pong <= 1'b0;
	end else if (lrclk_nedge) begin
	   
		left_chan <= left;
		right_chan <= {right[AUDIO_DW-2:0], sdata};
		
		ping_pong <= ~ping_pong;
	end





always @(posedge clk_out)
begin
   if (lrclk_nedge) begin
      dac_left <= left_chan;
		dac_right <= right_chan;
		
		dac_right_dbl[0] <= right_chan;
		dac_right_dbl[1] <= left_chan;
		
   end else
   begin
     data_left <= dac_left[0];
     dac_left <= {1'b0, dac_left[AUDIO_DW-1:1]};
	  
     data_right <= dac_right[0];
     dac_right <= {1'b0, dac_right[AUDIO_DW-1:1]};
   end
end




endmodule
