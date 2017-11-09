`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:10:23 11/25/2015 
// Design Name: 
// Module Name:    IF_STAGE 
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
module IF_STAGE(stop, reset, clock, PCWrite, PCSrc, Instruction_IF,  PC_Address_next, jump, j_address, address);
    integer K;

    //IF_STAGE INPUT
    //input [31:0] Addr_after_funct;
    input PCSrc, clock, reset;
	 input [31:0]  j_address, address;
	 input jump;
	 input PCWrite, stop;

    //IF_STAGE OUTPUT (including final_address)

    output [31:0] Instruction_IF; 
    output [31:0] PC_Address_next;
	 
	 reg [31:0] Addr_temp;

	 
	 reg [31:0] Imemory [63:0];
	 reg [31:0] PC_Cnt;
	 //for debug
	 
	 
	 //end for
	 
	 initial begin

    for(K=0;K<64;K=K+1)
    begin
      Imemory[K] = 32'b0;
    end
	 PC_Cnt = 0;

    //Add the instruction here
	 
    Imemory[0] = 32'b00100000000010000000000000100000;
    Imemory[1] = 32'b00100000000010010000000000110111;
    Imemory[2] = 32'b00000001000010011000000000100000;
    Imemory[3] = 32'b00000001000010011000100000100010;
    Imemory[4] = 32'b00000001000010011001000000100100;
	 Imemory[5] = 32'b00000001000010011001100000100101;
    Imemory[6] = 32'b00000001000010011010000000101010;
	 Imemory[7] = 32'b00010010100000000000000000000110;
	 Imemory[8] = 32'b00000001000010010101000000100000;
	 Imemory[9] = 32'b00000001010010010101000000100000;
	 Imemory[10] = 32'b00000001010010000101100000100000;
	 Imemory[11] = 32'b10001100000101010000000000000100;
	 Imemory[12] = 32'b00000001010101011011000000100000;
	 Imemory[13] = 32'b00000010101010111011100000100000;
	 Imemory[14] = 32'b10101100000101010000000000001000;
	 Imemory[15] = 32'b00001000000000000000000000000110; 
	 /*
	 Imemory[0] = 32'b00100000000010000000000000100000; //addi $t0, $zero, 32
  	 Imemory[1] = 32'b00100000000010010000000000110111; //addi $t1, $zero, 55 
	 Imemory[2] = 32'b00000001000010011000000000100100; //and $s0, $t0, $t1   
	 Imemory[3] = 32'b00000001000010011000000000100101; //or $s0, $t0, $t1    
	 Imemory[4] = 32'b10101100000100000000000000000100; //sw $s0, 4($zero) 
	 Imemory[5] = 32'b10101100000010000000000000001000; //sw $t0, 8($zero)
	 Imemory[6] = 32'b00000001000010011000100000100000; //add $s1, $t0, $t1  
	 Imemory[7] = 32'b00000001000010011001000000100010; //sub $s2, $t0, $t1   
	 Imemory[8] = 32'b00010010001100100000000000001001; //beq $s1, $s2, error0   
	 Imemory[9] = 32'b10001100000100010000000000000100; //lw $s1, 4($zero)  
	 Imemory[10]= 32'b00110010001100100000000001001000; //andi $s2, $s1, 48 
	 Imemory[11] =32'b00010010001100100000000000001001; //beq $s1, $s2, error1
	 Imemory[12] =32'b10001100000100110000000000001000; //lw $s3, 8($zero)    
	 Imemory[13] =32'b00010010000100110000000000001010; //beq $s0, $s3, error2
	 Imemory[14] =32'b00000010010100011010000000101010; //slt $s4, $s2, $s1 (Last) 
	 Imemory[15] =32'b00010010100000000000000000001111; //beq $s4, $0, EXIT
	 Imemory[16] =32'b00000010001000001001000000100000; //add $s2, $s1, $0
	 Imemory[17] =32'b00001000000000000000000000001110; //j Last  
    Imemory[18] =32'b00100000000010000000000000000000; //addi $t0, $0, 0(error0) 
    Imemory[19] =32'b00100000000010010000000000000000; //addi $t1, $0, 0
	 Imemory[20] =32'b00001000000000000000000000011111; //j EXIT 
    Imemory[21] =32'b00100000000010000000000000000001; //addi $t0, $0, 1(error1) 
	 Imemory[22] =32'b00100000000010010000000000000001; //addi $t1, $0, 1 
	 Imemory[23] =32'b00001000000000000000000000011111; //j EXIT 
    Imemory[24] =32'b00100000000010000000000000000010; //addi $t0, $0, 2(error2) 
	 Imemory[25] =32'b00100000000010010000000000000010; //addi $t1, $0, 2
	 Imemory[26] =32'b00001000000000000000000000011111; //j EXIT 
    Imemory[27] =32'b00100000000010000000000000000011; //addi $t0, $0, 3(error3)
	 Imemory[28] =32'b00100000000010010000000000000011; //addi $t1, $0, 3
	 Imemory[29] =32'b00001000000000000000000000011111; //j EXIT 
	 */
	 
	 end
	 
	 
	 assign PC_Address_next = PC_Cnt + 4;
	 assign Instruction_IF = Imemory[PC_Cnt/4];zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzkkkkkk
	 
	 //assign Addr_temp = (PCSrc) ? address : PC_Cnt + 4;
  
0000000000000000000000000000000000000000000000000000000000000000000000000000000009	 /* initial begin
	      $display("The debug process in IF_STAGE");
         $monitor($time,, "clock = %d, PC_Cnt = %d PCSrc = %d jump = %d PCWrite = %d", clock,  PC_Cnt, PCSrc ,jump, PCWrite);			
	  end */
	 
	/* initial begin
	      $display("The debug process in IF_STAGE");
         $monitor($time,, "clock = %b, Instruction_IF = %b", clock,  Instruction_IF );			
	  end */
	 
	 always@(posedge clock or posedge reset)
	 begin
	    if(reset == 1) PC_Cnt = 0; 
		 else if(stop == 1);
		 else if(PCWrite == 0);	 
		 else begin
		      case(PCSrc)
			    0: Addr_temp = PC_Cnt + 4;
				 1: Addr_temp = address;
				 default: Addr_temp = PC_Cnt + 4;
		 endcase
			  
		     case(jump)
			    0: PC_Cnt = Addr_temp;
				 1: PC_Cnt = j_address;
		 endcase
	    end
	 end
	 

endmodule
