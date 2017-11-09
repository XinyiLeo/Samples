`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    02:44:32 11/27/2015 
// Design Name: 
// Module Name:    ForwardUnit 
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
module ForwardUnit(EX_MEM_Rd,MEM_WB_Rd,MEM_WB_RegWrite,EX_MEM_RegWrite,
	ID_EX_Rt, ID_EX_Rs, ForwardA,ForwardB);


	//input  [4:0] IF_ID_Rs;
	//input  [4:0] IF_ID_Rt;
	input  [4:0] ID_EX_Rs;
	input  [4:0] ID_EX_Rt;
	input  [4:0] EX_MEM_Rd;
	input  [4:0] MEM_WB_Rd;
	input  MEM_WB_RegWrite;
	input  EX_MEM_RegWrite;

	output [1:0] ForwardA;
	output [1:0] ForwardB;

	reg [1:0] ForwardA;
	reg [1:0] ForwardB;

	always @(/*IF_ID_Rs or IF_ID_Rt or */EX_MEM_Rd or MEM_WB_Rd or MEM_WB_RegWrite or EX_MEM_RegWrite) 

	begin
		//MEM Hazard
		ForwardA <= 2'b00;
		ForwardB <= 2'b00;

		if (MEM_WB_RegWrite && (MEM_WB_Rd != 0)
			&& (MEM_WB_Rd == ID_EX_Rs)
			&& ~ (EX_MEM_RegWrite && (EX_MEM_Rd != 0)
				&& (EX_MEM_Rd == ID_EX_Rs)))
			begin
			ForwardA <= 2'b01;
			end
		if (MEM_WB_RegWrite && (MEM_WB_Rd != 0)
			&& (MEM_WB_Rd == ID_EX_Rt)
			&& ~ (EX_MEM_RegWrite && (EX_MEM_Rd != 0)
				&& (EX_MEM_Rd == ID_EX_Rt)))
			begin
			ForwardB <= 2'b01;
			end
	
		//EX Hazard
		if (EX_MEM_RegWrite && (EX_MEM_Rd != 0)
			&& (EX_MEM_Rd == ID_EX_Rs))
			begin
			ForwardA <= 2'b10;
			end
	
		if (EX_MEM_RegWrite && (EX_MEM_Rd != 0)
			&& (EX_MEM_Rd == ID_EX_Rt))
			begin
			ForwardB <= 2'b10;
			end
	end

endmodule // ForwardingUnit
