`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:15:31 05/15/2024 
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

// program with Digilent HS3
//   openFPGALoader -c digilent_hs3 --freq 1000000 -v *.jed
// or 
//   xc3sprog -c jtaghs2 -m /opt/Xilinx/14.7/ISE_DS/ISE/xbr/data -J 1000000 -p 0 -v *.jed

// git clean -d -x -f .
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

    // Build an array type for the shift register
    reg [11:0] sr_right;
    reg [31:0] sr_left;

    always @(posedge BCK) begin
        // Shift data by one stage; data from last stage is lost
        sr_right[11:1] <= sr_right[10:0];

        // Load new data into the first stage
        sr_right[0] <= DATAIN;

        // Shift data for the left channel
        sr_left[31:1] <= sr_left[30:0];
        sr_left[0] <= sr_right[11];
    end

    // Capture the data from the last stage, before it is lost
    assign CLKOUTR = BCK;
    assign LEOUTR = LRCK;
    assign DATAOUTR = sr_right[11];

    assign CLKOUTL = BCK;
    assign LEOUTL = LRCK;
    assign DATAOUTL = sr_left[31];
	
    assign LED1 = 0; // 0 => LED on, 1 => LED off
endmodule
