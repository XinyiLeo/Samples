`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:07:41 11/25/2015 
// Design Name: 
// Module Name:    Main 
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
//(Switch, select ,stop ,clock, reset, oneOut, tenOut, hund, thou);
module Main(Switch, select, stop, clock, reset, oneOut, tenOut, hund, thou, c_clock_in, c_clock_out);
input c_clock_in;
input [4:0] select;
input reset, clock, Switch, stop;
output [4:0] oneOut, tenOut, hund, thou;
output c_clock_out;

//output [31:0] s0, s1, s2, s3, s4, s5, s6, s7, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9;

//IF_STAGE INPUT
wire PCSrc;
wire PCWrite;

//IF_STAGE OUTPUT (including final_address)

wire [31:0] Instruction_IF; 
wire [31:0] PC_Address_next;

//ID_STAGE INPUT

wire [31:0] Address_in;
wire [31:0] Instruction_ID;
wire MUXCOntrol;

//ID_STAGE OUTPUT

//nine control signals
wire MemtoReg_out, RegWrite_out, Branch, MemRead, MemWrite, RegDst, ALUSrc, jump;
wire [1:0] ALUOp;

wire [4:0] rt, rd,rs;
wire [31:0] Address_out;
wire [31:0] R_Data1, R_Data2, Extend;
wire [31:0] j_address;


//EX_STAGE INPUT

wire Branch_in_EX, MemWrite_in_EX, MemRead_in_EX, RegWrite_in_EX, MemtoReg_in_EX, jump_in_EX, RegDst_EX, ALUSrc_EX;
wire [1:0] ALUOp_EX;

wire [4:0] rt_EX, rd_EX, rs_EX;
wire [31:0] extend_EX, Read_data1_EX, Read_data2_in_EX;
wire [31:0]  address_in_EX;
wire [31:0] j_address_in_EX;
wire [1:0] ForwardA , ForwardB; 

//EX_STAGE OUTPUT

wire [31:0] address_out_EX, j_address_out_EX;
wire Branch_out_EX, MemWrite_out_EX, MemRead_out_EX, RegWrite_out_EX, MemtoReg_out_EX, jump_out_EX, Zero_EX;
wire [31:0] Read_data2_out_EX, ALUresult_EX;
wire [4:0] rtd_EX;

//MEM_STAGE INPUT

wire MemWrite_MEM, Branch_MEM, Zero_MEM, RegWrite_in_MEM, MemtoReg_in_MEM, MemRead_MEM, jump_MEM;
wire [31:0] j_address_MEM, address_MEM;
wire [31:0] Address_in_MEM, WriteData_MEM;
wire [4:0] rtd_in_MEM; 

//MEM_STAGE OUTPUT

wire RegWrite_out_MEM, MemtoReg_out_MEM;
wire [31:0] ReadData_MEM, Address_out_MEM;
wire [4:0] rtd_out_MEM;

//WB_STAGE INPUT
wire [31:0] ReadData_WB;
wire [31:0] Address_WB;
wire MemtoReg;


//WB_STAGE OUTPUT
wire [31:0] W_data_WB;
wire [31:0]  rtd_WB;

//IF_ID INPUT  
wire IF_IDWrite;
wire IF_ID_Flush;

//ID_EX
 wire ID_Flush;
//EX_MEM
 wire  EX_Flush;


wire [31:0] final_address;
wire [31:0] Data;
wire c_clock;

assign final_address = PC_Address_next - 4;
assign oneOut = (Switch) ? Data[3:0] : final_address[3:0];
assign tenOut = (Switch) ? Data[7:4] : final_address[7:4];
assign hund = (Switch) ? Data[11:8] : 16;

assign c_clock = (stop)  ? 0 : clock; 
assign thou = (Switch) ? Data[15:12] : c_clock;






IF_STAGE M1 (stop, reset, clock,PCWrite,  PCSrc, Instruction_IF,  PC_Address_next, jump_MEM, j_address_MEM, address_MEM);
ID_STAGE M2 (select, Data, ID_Flush, MUXCOntrol, RegWrite_WB,  rtd_WB, W_data_WB, clock, Address_in, Instruction_ID, MemtoReg_out, RegWrite_out, Branch, MemRead, MemWrite, RegDst, ALUSrc, jump,  ALUOp, rt, rd, rs, Address_out, j_address, R_Data1, R_Data2, Extend);
EX_STAGE M3 ( Address_WB, Address_in_MEM, ForwardA, ForwardB, Branch_in_EX, MemWrite_in_EX, MemRead_in_EX, RegWrite_in_EX, MemtoReg_in_EX, jump_in_EX, RegDst_EX, ALUSrc_EX, ALUOp_EX, rt_EX, rd_EX, extend_EX, Read_data1_EX, Read_data2_in_EX, address_in_EX, j_address_in_EX,
  address_out_EX, j_address_out_EX, Branch_out_EX, MemWrite_out_EX, MemRead_out_EX, RegWrite_out_EX, MemtoReg_out_EX, jump_out_EX, Zero_EX,  Read_data2_out_EX, ALUresult_EX,  rtd_EX);
MEM_STAGE M4 (clock, PCSrc, MemWrite_MEM, Branch_MEM, Zero_MEM, RegWrite_in_MEM, MemtoReg_in_MEM, MemRead_MEM, jump_MEM, j_address_MEM, address_MEM ,Address_in_MEM, WriteData_MEM, rtd_in_MEM, RegWrite_out_MEM, MemtoReg_out_MEM, ReadData_MEM, Address_out_MEM, rtd_out_MEM);
WB_STAGE M5 (ReadData_WB, Address_WB,  MemtoReg, W_data_WB );

//The following are stage register
 IF_ID M6 (reset, clock,IF_ID_Flush, IF_IDWrite, Instruction_IF, PC_Address_next, Address_in, Instruction_ID);
 ID_EX M7 (clock, reset, MemtoReg_out, RegWrite_out, Branch, MemRead, MemWrite, RegDst, ALUSrc, jump, ALUOp, rt, rd,rs,  Address_out, j_address, R_Data1, R_Data2, Extend,  Branch_in_EX, MemWrite_in_EX, MemRead_in_EX, RegWrite_in_EX, MemtoReg_in_EX, jump_in_EX, RegDst_EX, ALUSrc_EX,  ALUOp_EX, rt_EX, rd_EX,rs_EX, extend_EX, Read_data1_EX, Read_data2_in_EX,   address_in_EX, j_address_in_EX  );
 EX_MEM M8 (reset, clock, EX_Flush, address_out_EX, j_address_out_EX, Branch_out_EX, MemWrite_out_EX, MemRead_out_EX, RegWrite_out_EX, MemtoReg_out_EX, jump_out_EX, Zero_EX,  Read_data2_out_EX, ALUresult_EX,  rtd_EX, MemWrite_MEM, Branch_MEM, Zero_MEM, RegWrite_in_MEM, MemtoReg_in_MEM, MemRead_MEM, jump_MEM, j_address_MEM, address_MEM ,Address_in_MEM, WriteData_MEM, rtd_in_MEM  );
 MEM_WB M9 (clock, reset, RegWrite_out_MEM, MemtoReg_out_MEM, ReadData_MEM, Address_out_MEM, rtd_out_MEM, ReadData_WB, Address_WB, RegWrite_WB, MemtoReg, rtd_WB);


    // initial begin
	   //   $display("The debug process in main block");
      //   $monitor($time,, "clock = %d, Address = %h PCSrc = %h", clock, final_address, PCSrc);			
	  //end
	  
ForwardUnit M10 (rtd_in_MEM, rtd_WB ,RegWrite_WB,RegWrite_in_MEM, rt_EX   ,rs_EX, ForwardA,ForwardB);
DetectUnit M11 (PCWrite,IF_IDWrite,MUXCOntrol,    Instruction_ID[25:21],Instruction_ID[20:16],rt_EX, MemRead_in_EX); //Input at the back;
BeqCtrl M12 (PCSrc, jump_MEM, IF_ID_Flush, ID_Flush, EX_Flush);



endmodule

