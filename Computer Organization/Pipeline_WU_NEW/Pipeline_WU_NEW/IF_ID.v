`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:51:19 11/25/2015 
// Design Name: 
// Module Name:    IF_ID 
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
module IF_ID(reset, clock,IF_ID_Flush, IF_IDWrite, Instruction_IF, PC_Address_next, Address_in, Instruction_ID);
    input [31:0] Instruction_IF; 
    input [31:0] PC_Address_next;
	 input reset, clock;
	 input IF_IDWrite, IF_ID_Flush;
	 
	 output [31:0] Address_in;
    output [31:0] Instruction_ID;
	 
	 reg [31:0] Address_in;
    reg [31:0] Instruction_ID;
	 
	 always @ (posedge clock or posedge reset)
    begin
        if (reset)
        begin 
            Address_in <= 0;
				Instruction_ID <= 0;
		  end
		  else if(IF_ID_Flush)
		  begin
		       Address_in <= 0;
				Instruction_ID <= 0;
		  end
        else if (IF_IDWrite) 
		  begin
            Address_in <= PC_Address_next;
				Instruction_ID <= Instruction_IF;
        end
		  else;
    end
	 
	 /* initial begin
	      $display("The debug process in IF_STAGE");
         $monitor($time,, "clock = %d, IF_IDWrite = %d ", clock,  IF_IDWrite);			
	  end*/

endmodule
