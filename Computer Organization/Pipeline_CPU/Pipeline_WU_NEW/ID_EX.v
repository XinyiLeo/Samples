`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:55:03 11/25/2015 
// Design Name: 
// Module Name:    ID_EX 
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
module ID_EX(clock, reset,  MemtoReg_out, RegWrite_out, Branch, MemRead, MemWrite, RegDst, ALUSrc, jump, ALUOp, rt, rd, rs, Address_out, j_address, R_Data1, R_Data2, Extend,  Branch_in_EX, MemWrite_in_EX, MemRead_in_EX, RegWrite_in_EX, MemtoReg_in_EX, jump_in_EX, RegDst_EX, ALUSrc_EX,  ALUOp_EX, rt_EX, rd_EX,rs_EX, extend_EX, Read_data1_EX, Read_data2_in_EX,   address_in_EX, j_address_in_EX  );
  input MemtoReg_out, RegWrite_out, Branch, MemRead, MemWrite, RegDst, ALUSrc, jump, clock, reset;
  input [1:0] ALUOp;
  input [4:0] rt, rd, rs;
  input [31:0] Address_out, R_Data1, R_Data2, Extend;
  input [31:0] j_address;
 
  
  output Branch_in_EX, MemWrite_in_EX, MemRead_in_EX, RegWrite_in_EX, MemtoReg_in_EX, jump_in_EX, RegDst_EX, ALUSrc_EX;
  output [1:0] ALUOp_EX;
  output [4:0] rt_EX, rd_EX, rs_EX;
  output [31:0] extend_EX, Read_data1_EX, Read_data2_in_EX;
  output [31:0]  address_in_EX;
  output [31:0] j_address_in_EX;
  
  reg Branch_in_EX, MemWrite_in_EX, MemRead_in_EX, RegWrite_in_EX, MemtoReg_in_EX, jump_in_EX, RegDst_EX, ALUSrc_EX;
  reg [1:0] ALUOp_EX;
  reg [4:0] rt_EX, rd_EX, rs_EX;
  reg [31:0] extend_EX, Read_data1_EX, Read_data2_in_EX;
  reg [31:0]  address_in_EX;
  reg [31:0] j_address_in_EX;
  
  always @ (posedge clock)
begin
if (reset == 1)
begin
Branch_in_EX <= 0;
MemWrite_in_EX <= 0;
MemRead_in_EX <= 0;
RegWrite_in_EX <= 0;
MemtoReg_in_EX <= 0;
jump_in_EX <= 0;
RegDst_EX <= 0;
ALUSrc_EX <= 0;
ALUOp_EX <= 0;
address_in_EX <= 0;
j_address_in_EX <= 0;
extend_EX <= 0;
Read_data1_EX <= 0;
Read_data2_in_EX <= 0;
rt_EX <= 0;
rd_EX <= 0;
rs_EX <= 0;
end
else begin
Branch_in_EX <= Branch;
MemWrite_in_EX <= MemWrite;
MemRead_in_EX <= MemRead;
RegWrite_in_EX <= RegWrite_out;
MemtoReg_in_EX <= MemtoReg_out;
jump_in_EX <= jump;
RegDst_EX <= RegDst;
ALUSrc_EX <= ALUSrc;
ALUOp_EX <= ALUOp;
address_in_EX <= Address_out;
j_address_in_EX <= j_address;
extend_EX <= Extend;
Read_data1_EX <= R_Data1;
Read_data2_in_EX <= R_Data2;
rt_EX <= rt;
rd_EX <= rd;
rs_EX <= rs;
end
end


endmodule
