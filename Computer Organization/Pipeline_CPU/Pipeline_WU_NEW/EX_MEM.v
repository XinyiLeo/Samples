`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:02:18 11/25/2015 
// Design Name: 
// Module Name:    EX_MEM 
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
module EX_MEM(reset, clock, EX_Flush, address_out_EX, j_address_out_EX, Branch_out_EX, MemWrite_out_EX, MemRead_out_EX, RegWrite_out_EX, MemtoReg_out_EX, jump_out_EX, Zero_EX,  Read_data2_out_EX, ALUresult_EX,  rtd_EX, MemWrite_MEM, Branch_MEM, Zero_MEM, RegWrite_in_MEM, MemtoReg_in_MEM, MemRead_MEM, jump_MEM, j_address_MEM, address_MEM ,Address_in_MEM, WriteData_MEM, rtd_in_MEM  );
input [31:0] address_out_EX, j_address_out_EX;
input  EX_Flush, Branch_out_EX, MemWrite_out_EX, MemRead_out_EX, RegWrite_out_EX, MemtoReg_out_EX, jump_out_EX, Zero_EX, reset, clock;
input [31:0] Read_data2_out_EX, ALUresult_EX;
input [4:0] rtd_EX;

output MemWrite_MEM, Branch_MEM, Zero_MEM, RegWrite_in_MEM, MemtoReg_in_MEM, MemRead_MEM, jump_MEM;
output [31:0] j_address_MEM, address_MEM;
output [31:0] Address_in_MEM, WriteData_MEM;
output [4:0] rtd_in_MEM; 

reg MemWrite_MEM, Branch_MEM, Zero_MEM, RegWrite_in_MEM, MemtoReg_in_MEM, MemRead_MEM, jump_MEM;
reg [31:0] j_address_MEM, address_MEM;
reg [31:0] Address_in_MEM, WriteData_MEM;
reg [4:0] rtd_in_MEM; 

/*initial begin
	      $display("************************************************************");
		   $display("The textual simulation results:");
		   $display("************************************************************");
		   $monitor( $time,, "clock =%d Address_in_MEM = %d ALUresult_EX = %d RegWrite_in_MEM = %d, RegWrite_out_EX = %d" ,clock,Address_in_MEM,ALUresult_EX, RegWrite_in_MEM , RegWrite_out_EX  ) ;			
	   end*/


always @ (posedge clock or posedge reset)
begin
if (reset == 1)
begin
MemWrite_MEM <= 0;
Branch_MEM <= 0;
Zero_MEM <= 0;
RegWrite_in_MEM <= 0;
MemtoReg_in_MEM <= 0;
MemRead_MEM <= 0;
jump_MEM <= 0;
j_address_MEM <= 0;
address_MEM <= 0;
Address_in_MEM <= 0;
WriteData_MEM <= 0;
rtd_in_MEM <= 0;
end
else if(EX_Flush)
begin
MemWrite_MEM <= 0;
Branch_MEM <= 0;
RegWrite_in_MEM <= 0;
MemtoReg_in_MEM <= 0;
MemRead_MEM <= 0;
jump_MEM <= 0;
end
else begin
MemWrite_MEM <= MemWrite_out_EX;
Branch_MEM <= Branch_out_EX;
Zero_MEM <= Zero_EX;
RegWrite_in_MEM <= RegWrite_out_EX;
MemtoReg_in_MEM <= MemtoReg_out_EX;
MemRead_MEM <= MemRead_out_EX;
jump_MEM <= jump_out_EX;
j_address_MEM <= j_address_out_EX;
address_MEM <= address_out_EX;
Address_in_MEM <= ALUresult_EX;
WriteData_MEM <= Read_data2_out_EX;
rtd_in_MEM <= rtd_EX;
end
end






endmodule
