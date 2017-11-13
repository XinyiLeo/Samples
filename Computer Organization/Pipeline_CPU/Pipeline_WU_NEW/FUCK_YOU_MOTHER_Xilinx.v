`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   01:27:17 11/27/2015
// Design Name:   Main
// Module Name:   C:/Users/wuxy3/Desktop/Pipeline_WU_NEW/FUCK_YOU_MOTHER_Xilinx.v
// Project Name:  Pipeline_WU_NEW
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Main
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module FUCK_YOU_MOTHER_Xilinx;

	
	  parameter half_period = 10;

	// Inputs
	reg reset;
	reg clock;

	// Outputs
	wire [31:0] final_address;

	// Instantiate the Unit Under Test (UUT)
	Main uut (
		.reset(reset), 
		.clock(clock), 
		.final_address(final_address)
	);

	initial begin
		// Initialize Inputs
		reset = 1;
		clock = 0;

		// Wait 100 ns for global reset to finish
		#15 reset = 0;
        
		// Add stimulus here

	end
	always #half_period clock = ~clock;
	
	initial #1000 $stop;
      
endmodule

