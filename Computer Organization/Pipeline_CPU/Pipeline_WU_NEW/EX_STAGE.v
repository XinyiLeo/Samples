`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:15:14 11/25/2015 
// Design Name: 
// Module Name:    EX_STAGE 
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
module EX_STAGE( Address_WB, Address_in_MEM ,ForwardA, ForwardB, Branch_in_EX, MemWrite_in_EX, MemRead_in_EX, RegWrite_in_EX, MemtoReg_in_EX, jump_in_EX, RegDst_EX, ALUSrc_EX, ALUOp_EX, rt_EX, rd_EX, extend_EX, Read_data1_EX, Read_data2_in_EX, address_in_EX, j_address_in_EX,
  address_out_EX, j_address_out_EX, Branch_out_EX, MemWrite_out_EX, MemRead_out_EX, RegWrite_out_EX, MemtoReg_out_EX, jump_out_EX, Zero_EX,  Read_data2_out_EX, ALUresult_EX,  rtd_EX);
  //EX_STAGE INPUT

input  Branch_in_EX, MemWrite_in_EX, MemRead_in_EX, RegWrite_in_EX, MemtoReg_in_EX, jump_in_EX, RegDst_EX, ALUSrc_EX;
input [1:0] ALUOp_EX;

input [1:0] ForwardA, ForwardB;
input [31:0] Address_WB, Address_in_MEM;

input [4:0] rt_EX, rd_EX;
input [31:0] extend_EX, Read_data1_EX, Read_data2_in_EX;
input [31:0]  address_in_EX;
input [31:0] j_address_in_EX;

//EX_STAGE OUTPUT

output [31:0] address_out_EX, j_address_out_EX;
output Branch_out_EX, MemWrite_out_EX, MemRead_out_EX, RegWrite_out_EX, MemtoReg_out_EX, jump_out_EX, Zero_EX;
output [31:0] Read_data2_out_EX, ALUresult_EX;
output [4:0] rtd_EX;


reg   Zero_EX;
reg [31:0]  ALUresult_EX;

reg [31:0] Read_data2_out_EX;
reg [31:0] Data_input_two;
reg [3:0] ALUControl;

assign Branch_out_EX = Branch_in_EX;
assign MemWrite_out_EX = MemWrite_in_EX;
assign MemRead_out_EX = MemRead_in_EX;
assign RegWrite_out_EX = RegWrite_in_EX;
assign MemtoReg_out_EX = MemtoReg_in_EX;
assign jump_out_EX = jump_in_EX;
//assign Read_data2_out_EX = Read_data2_in_EX;
assign j_address_out_EX = j_address_in_EX;
assign address_out_EX = extend_EX * 4 + address_in_EX; 
assign rtd_EX = (RegDst_EX) ? rd_EX : rt_EX;

//Forwarding
reg [31:0] For_inputA, For_inputB;

always@(ALUSrc_EX or ALUOp_EX or Read_data1_EX or Read_data2_in_EX or extend_EX or  ForwardA or ForwardB) begin
   case (ForwardA)
	     0: For_inputA = Read_data1_EX;
		  1: For_inputA = Address_WB; 
		  2: For_inputA = Address_in_MEM;
		  default:  For_inputA = 32'bx;
   endcase	

   case (ForwardB)
	     0: For_inputB = Read_data2_in_EX;
		  1: For_inputB = Address_WB; 
		  2: For_inputB = Address_in_MEM;
		  default:  For_inputB = 32'bx;
   endcase			
   
	
   case (ALUSrc_EX)
		      0: Data_input_two =  For_inputB;
				1: Data_input_two = extend_EX;
				default: Data_input_two = 32'bx;
		  endcase
		  
		  Read_data2_out_EX = For_inputB;
		  
		   if(ALUOp_EX == 2) 
            begin
				    case(extend_EX[5:0])
					     6'b100000: ALUControl = 4'b0010;
						  6'b100010: ALUControl = 4'b0110;
						  6'b100100: ALUControl = 4'b0000;
						  6'b100101: ALUControl = 4'b0001;
						  6'b101010: ALUControl = 4'b0111;
						  default: ALUControl = 3'bx;
					 endcase
				end
			
			else if(ALUOp_EX == 0) //addi
            begin
				    ALUControl = 2;
				end
			
			else if(ALUOp_EX == 3) //andi
            begin
				    ALUControl = 0;
				end	
			
			else if(ALUOp_EX == 1) //beq
            begin
				    ALUControl = 6;
				end	
		  
	     case (ALUControl)
		      4'b0010: ALUresult_EX =  For_inputA + Data_input_two;
				4'b0110: ALUresult_EX =  For_inputA - Data_input_two;
				4'b0000: ALUresult_EX =  For_inputA & Data_input_two;
				4'b0001: ALUresult_EX =  For_inputA | Data_input_two;
				4'b0111: ALUresult_EX =  For_inputA < Data_input_two;
				default  ALUresult_EX = 32'bx;
		  endcase
		  if(For_inputA == Data_input_two) Zero_EX = 1; 
		  else Zero_EX = 0;
end

     /* initial begin
	      $display("************************************************************");
		   $display("The textual simulation results:");
		   $display("************************************************************");
		   $monitor( $time,, " extend_EX[5:0] = %b read1 = %d read2 = %d ALUreseult = %d ForwardA = %d ForwardB = %d MEM = %d WB = %d ALUControl = %d", extend_EX[5:0], Read_data1_EX , Data_input_two,ALUresult_EX, ForwardA , ForwardB, Address_in_MEM, Address_WB, ALUControl );			
	   end */

  /*initial begin
	      $display("************************************************************");
		   $display("The textual simulation results:");
		   $display("************************************************************");
		   $monitor( $time,, "RegWrite_in = %d, RegWrite_out = %d ",RegWrite_in_EX, RegWrite_out_EX);
end*/

endmodule
