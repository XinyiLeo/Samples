`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:24:21 11/25/2015 
// Design Name: 
// Module Name:    WB_STAGE 
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
module WB_STAGE(ReadData_WB, Address_WB, MemtoReg, W_data_WB );

//WB_STAGE INPUT
input [31:0] ReadData_WB;
input [31:0] Address_WB;
input MemtoReg;


//WB_STAGE OUTPUT
output [31:0] W_data_WB;
		



assign W_data_WB = (MemtoReg) ? Address_WB :  ReadData_WB;


     /*  initial begin
	      $display("The debug process in WB_STAGE");
         $monitor($time,, "ReadData_WB = %d  Address_WB = %d MemtoReg = %d  W_data_WB = %d", ReadData_WB ,Address_WB , MemtoReg, W_data_WB );			
	    end */


endmodule
