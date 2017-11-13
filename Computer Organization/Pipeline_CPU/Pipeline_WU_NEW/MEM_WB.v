`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:10:55 11/25/2015 
// Design Name: 
// Module Name:    MEM_WB 
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
module MEM_WB(clock, reset, RegWrite_out_MEM, MemtoReg_out_MEM, ReadData_MEM, Address_out_MEM, rtd_out_MEM, ReadData_WB, Address_WB, RegWrite_WB, MemtoReg, rtd_WB);
input RegWrite_out_MEM, MemtoReg_out_MEM, clock, reset;
input [31:0] ReadData_MEM, Address_out_MEM;
input [4:0] rtd_out_MEM;

output [31:0] ReadData_WB;
output [31:0] Address_WB;
output RegWrite_WB, MemtoReg;
output [4:0] rtd_WB;

reg [31:0] ReadData_WB;
reg [31:0] Address_WB;
reg RegWrite_WB, MemtoReg;
reg [4:0] rtd_WB;

/*initial begin
	   $display("************************************************************");
		$display("The textual simulation results in MEM :");
		$display("************************************************************");
		$monitor($time,, "clock = %d RegWrite_WB = %b  Address_WB = %b rtd_WB = %d ReadData_WB = %d", clock, RegWrite_WB, Address_WB, rtd_WB , ReadData_WB);
	   end
*/

/*initial begin
	   $display("************************************************************");
		$display("The textual simulation results in MEM :");
		$display("************************************************************");
		$monitor($time,, "RegWrite = %d" ,  RegWrite_WB);
end*/

/*initial begin
	   $display("************************************************************");
		$display("The textual simulation results in MEM :");
		$display("************************************************************");
		$monitor($time,, "Rtd_WB = %d  Rtd_MEM = %d" ,  rtd_WB, rtd_out_MEM);
end*/

always @ (posedge clock or posedge reset)
begin
if (reset == 1)
begin
    RegWrite_WB <= 0;
	 MemtoReg <=  0;
	 Address_WB <= 0;
	 ReadData_WB <= 0;
	 rtd_WB <= 0;
end
else begin
    RegWrite_WB <= RegWrite_out_MEM;
	 MemtoReg <=  MemtoReg_out_MEM;
	 Address_WB <= Address_out_MEM;
	 ReadData_WB <= ReadData_MEM;
	 rtd_WB <= rtd_out_MEM;
end
end



endmodule
