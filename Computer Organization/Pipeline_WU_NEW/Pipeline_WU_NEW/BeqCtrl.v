`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    03:28:27 11/27/2015 
// Design Name: 
// Module Name:    BeqCtrl 
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
module BeqCtrl(PCSrc, jump, IF_Flush, ID_Flush, EX_Flush);

	input PCSrc;
	input jump;
	
	output IF_Flush;
	output ID_Flush;
	output EX_Flush;
	
	reg IF_Flush;
	reg ID_Flush;
	reg EX_Flush;


	always @(PCSrc or jump) 
	begin
		if(jump == 1) 
		begin
			IF_Flush <= 1;
			ID_Flush <= 1;
			EX_Flush <= 1;
		end 
		if(PCSrc == 1) 
		begin
			IF_Flush <= 1;
			ID_Flush <= 1;
			EX_Flush <= 1;
		end 
		else 
		begin
			IF_Flush <= 0;
			ID_Flush <= 0;
			EX_Flush <= 0;
		end
	end
 /* initial begin
	      $display("The debug process in main block");
         $monitor($time,, "IF_ID_Flush = %b, ID_EX_Flush  = %b EX_MEM_Flush  = %b", IF_ID_Flush , ID_EX_Flush ,EX_MEM_Flush);			
	  end*/
endmodule // BeqControl
