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

// I2S to PCM 24Bit version for PCM1704U
// Right 7bit data delay
// Left 32bit data delay

// program with Digilent HS3
//   openFPGALoader -c digilent_hs3 --freq 1000000 -v *.jed
// or 
//   xc3sprog -c jtaghs2 -m /opt/Xilinx/14.7/ISE_DS/ISE/xbr/data -J 1000000 -p 0 -v *.jed

// git clean -d -x -f .
//module i2s_to_pcm(
//    input BCK,
//    input LRCK,
//    input DATAIN,
//    output CLKOUTR,
//    output LEOUTR,
//    output DATAOUTR,
//    output CLKOUTL,
//    output LEOUTL,  
//    output DATAOUTL,
//    output LED1
//);
//
//    // Build an array type for the shift register
//    reg [7:0] sr_right;
//    reg [31:0] sr_left;
//
//    always @(posedge BCK) begin
//        // Shift data by one stage; data from last stage is lost
//        sr_right[7:1] <= sr_right[6:0];
//
//        // Load new data into the first stage
//        sr_right[0] <= DATAIN;
//
//        // Shift data for the left channel
//        sr_left[31:1] <= sr_left[30:0];
//        sr_left[0] <= sr_right[7];
//    end
//
//    // Capture the data from the last stage, before it is lost
//    assign CLKOUTR = BCK;
//    assign LEOUTR = LRCK;
//    assign DATAOUTR = sr_right[7];
//
//    assign CLKOUTL = BCK;
//    assign LEOUTL = LRCK;
//    assign DATAOUTL = sr_left[31];
//	
//    assign LED1 = 0; // 0 => LED on, 1 => LED off
//endmodule

// good with I2S
//module i2s_to_pcm(
//    input BCK,
//    input LRCK,
//    input DATAIN,
//    output CLKOUTR,
//    output LEOUTR,
//    output DATAOUTR,
//    output CLKOUTL,
//    output LEOUTL,  
//    output DATAOUTL,
//    output LED1
//);
//
//    // Build an array type for the shift register
//    reg [6:0] sr_right;
//    reg [31:0] sr_left;
//
//    always @(posedge BCK) begin
//        // Shift data by one stage; data from last stage is lost
//        sr_right[6:1] <= sr_right[5:0];
//
//        // Load new data into the first stage
//        sr_right[0] <= DATAIN;
//
//        // Shift data for the left channel
//        sr_left[31:1] <= sr_left[30:0];
//        sr_left[0] <= sr_right[5];
//    end
//
//    // Capture the data from the last stage, before it is lost
//    assign CLKOUTR = BCK;
//    assign LEOUTR = LRCK;
//    assign DATAOUTR = sr_right[6];
//
//    //assign CLKOUTL = BCK;
//   // assign LEOUTL = LRCK;
//    //assign DATAOUTL = sr_left[31];
//	
//    assign LED1 = 0; // 0 => LED on, 1 => LED off
//endmodule

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
    reg [6:0] sr_right;
    reg [31:0] sr_left;

    always @(posedge BCK) begin
        // Shift data by one stage; data from last stage is lost
        //sr_right[6:1] <= sr_right[5:0];

        // Load new data into the first stage
        //sr_right[0] <= DATAIN;
		  
		  // shift right channel by 7 bit
		  sr_right <= {sr_right[5:0], DATAIN};  
		  

        // Shift data for the left channel
        //sr_left[31:1] <= sr_left[30:0];
       // sr_left[0] <= sr_right[5];
		  
		  // shift left channel by 39 bit (32bit + 7bit)
		  sr_left <= {sr_left[30:0], sr_right[6]};  
		  
    end

    // Capture the data from the last stage, before it is lost
    assign CLKOUTR = BCK;
    assign LEOUTR = LRCK;
    assign DATAOUTR = sr_right[6];

    assign CLKOUTL = BCK;
    assign LEOUTL = LRCK;
    assign DATAOUTL = sr_left[31];
	
    assign LED1 = 0; // 0 => LED on, 1 => LED off
endmodule

//module delay_by_7 (
//    input  wire clk,         // Clock
//    input  wire rst,         // Synchronous reset (active high)
//    input  wire data_in,     // Serial input
//    output wire data_out     // Output delayed by 7 clock cycles
//);
//
//    reg [6:0] shift_reg;
//
//    always @(posedge clk) begin
//        if (rst)
//            shift_reg <= 7'b0;
//        else
//            shift_reg <= {shift_reg[5:0], data_in};  // Shift left
//    end
//
//    assign data_out = shift_reg[6];  // Output the bit that came in 7 cycles ago
//
//endmodule


//module delay_by_7_and_32 (
//    input  wire clk,
//    input  wire rst,
//    input  wire data_in,
//    output wire data_out_7,
//    output wire data_out_32
//);
//
//    reg [6:0]  shift_7   = 7'b0;
//    reg [31:0] shift_32  = 32'b0;
//
//    always @(posedge clk) begin
//        if (rst) begin
//            shift_7  <= 7'b0;
//            shift_32 <= 32'b0;
//        end else begin
//            shift_7  <= {shift_7[5:0], data_in};
//            shift_32 <= {shift_32[30:0], data_in};
//        end
//    end
//
//    assign data_out_7  = shift_7[6];    // 7-bit delay
//    assign data_out_32 = shift_32[31];  // 32-bit delay
//
//endmodule


//module serial_delay_7_39 (
//    input  wire clk,
//    input  wire rst,
//    input  wire data_in,
//    output wire data_out_7,
//    output wire data_out_39
//);
//
//    reg [6:0]   shift_7   = 7'b0;
//    reg [38:0]  shift_39  = 39'b0;
//
//    always @(posedge clk) begin
//        if (rst) begin
//            shift_7  <= 7'b0;
//            shift_39 <= 39'b0;
//        end else begin
//            shift_7  <= {shift_7[5:0], data_in};
//            shift_39 <= {shift_39[37:0], data_in};
//        end
//    end
//
//    assign data_out_7  = shift_7[6];     // Output delayed by 7 bits
//    assign data_out_39 = shift_39[38];   // Output delayed by 39 bits
//
//endmodule


