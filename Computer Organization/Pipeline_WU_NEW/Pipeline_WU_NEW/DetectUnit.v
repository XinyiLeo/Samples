`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    02:49:29 11/27/2015 
// Design Name: 
// Module Name:    DetectUnit 
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
module DetectUnit(PCWrite,IF_IDWrite,MUXCOntrol,IF_ID_Rs,IF_ID_Rt,ID_EX_Rt,ID_EX_MemRead);

	output PCWrite,IF_IDWrite,MUXCOntrol;
	input  [4:0] IF_ID_Rs;
	input  [4:0] IF_ID_Rt;
	input  [4:0] ID_EX_Rt;
   input  ID_EX_MemRead;
	
	reg PCWrite,IF_IDWrite,MUXCOntrol;
	
	
	/*initial begin
	      $display("The debug process in IF_STAGE");
         $monitor($time,, "IF_ID_Rs = %b, IF_ID_Rt  = %b,ID_EX_Rt  = %b,ID_EX_MemRead  = %b", IF_ID_Rs,IF_ID_Rt,ID_EX_Rt,ID_EX_MemRead);			
	  end*/
	  
	always @(ID_EX_MemRead or IF_ID_Rs or IF_ID_Rt or ID_EX_Rt)
	
	begin
	
	if(ID_EX_MemRead && 
		((ID_EX_Rt == IF_ID_Rs)||ID_EX_Rt == IF_ID_Rt)) 
	begin
		PCWrite=0;
		IF_IDWrite=0;
		MUXCOntrol=1;
	end
	else 
	begin
		PCWrite=1;
		IF_IDWrite=1;
		MUXCOntrol=0;
	end
	
	end

endmodule // DetectingUnit

