`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   09:22:42 11/27/2015
// Design Name:   Main
// Module Name:   C:/Users/wuxy3/Desktop/Pipeline_WU_NEW/xx.v
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

module xx;
  parameter half_period = 10;
	// Inputs
	reg reset;
	reg clock;
	reg [4:0] select;

	// Outputs
	wire [3:0] faA;
	wire [3:0] faB;
	wire [3:0] faC;
	wire [3:0] faD;
	wire [3:0] SA;
	wire [3:0] SB;
	wire [3:0] SC;
	wire [3:0] SD;

	// Instantiate the Unit Under Test (UUT)
	Main uut (
		.reset(reset), 
		.clock(clock), 
		.faA(faA), 
		.faB(faB), 
		.faC(faC), 
		.faD(faD), 
		.select(select), 
		.SA(SA), 
		.SB(SB), 
		.SC(SC), 
		.SD(SD)
	);

	initial begin
		// Initialize Inputs
		reset = 1;
		clock = 0;
		select = 0;

		// Wait 100 ns for global reset to finish
		#15 reset = 0;
        
		// Add stimulus here

	end
	always #half_period clock = ~clock;
	
	initial #1000 $stop;
      
endmodule

