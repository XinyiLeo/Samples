`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:20:54 11/25/2015 
// Design Name: 
// Module Name:    MEM_STAGE 
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
module MEM_STAGE(clock, PCSrc, MemWrite_MEM, Branch_MEM, Zero_MEM, RegWrite_in_MEM, MemtoReg_in_MEM, MemRead_MEM, jump_MEM, j_address_MEM, address_MEM ,Address_in_MEM, WriteData_MEM, rtd_in_MEM, RegWrite_out_MEM, MemtoReg_out_MEM, ReadData_MEM, Address_out_MEM, rtd_out_MEM);
//MEM_STAGE INPUT
integer K;
input MemWrite_MEM, Branch_MEM, Zero_MEM, RegWrite_in_MEM, MemtoReg_in_MEM, MemRead_MEM, jump_MEM, clock;
input [31:0] j_address_MEM, address_MEM;
input [31:0] Address_in_MEM, WriteData_MEM;
input [4:0] rtd_in_MEM; 

//MEM_STAGE OUTPUT
output RegWrite_out_MEM, MemtoReg_out_MEM;
output [31:0] ReadData_MEM, Address_out_MEM;
output [4:0] rtd_out_MEM;
output PCSrc;
//output [31:0] Address_after_funct;

reg [31:0] Data_Memory [63:0];
//reg [31:0] ReadData_MEM;

assign RegWrite_out_MEM = RegWrite_in_MEM;
assign MemtoReg_out_MEM = MemtoReg_in_MEM;
assign Address_out_MEM = Address_in_MEM;
assign rtd_out_MEM = rtd_in_MEM;
and(PCSrc, Branch_MEM, Zero_MEM);

     /*initial begin
	      $display("The debug process in ID_STAGE");
         $monitor($time,, "clock = %d Address_out = %d ReadData_MEM = %d MemRead_MEM = %b  MemtoReg_out_MEM = %b", clock, Address_out_MEM, ReadData_MEM, MemRead_MEM , MemtoReg_out_MEM);			
	    end */
		 
		/* initial begin
	      $display("The debug process in ID_STAGE");
         $monitor($time,,"PCSrc = %b jump = %b", PCSrc, jump_MEM);
	    end */
initial begin
for(K=0;K<64;K=K+1)
    begin
      Data_Memory[K] = 32'b0;
    end
end

assign ReadData_MEM = (MemRead_MEM) ? Data_Memory[Address_in_MEM[7:0]/4] : 32'bx;

always@(negedge clock) begin
     if(MemWrite_MEM) Data_Memory[Address_in_MEM[7:0]/4] = WriteData_MEM;
end


endmodule
