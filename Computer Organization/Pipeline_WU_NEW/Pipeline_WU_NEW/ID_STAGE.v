`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:11:22 11/25/2015 
// Design Name: 
// Module Name:    ID_STAGE 
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
module ID_STAGE(select, Data,ID_Flush, MUXCOntrol, RegWrite, rtd_out_ID, W_data_ID, clock, Address_in, Instruction_ID, MemtoReg_out, RegWrite_out, Branch, MemRead, MemWrite, RegDst, ALUSrc, jump,  ALUOp, rt, rd,rs, Address_out, j_address, R_Data1, R_Data2, Extend);
//ID_STAGE INPUT
integer K;
input [31:0] Address_in;
input [31:0] Instruction_ID;
input clock;
input RegWrite, ID_Flush;
input [4:0] rtd_out_ID;
input [31:0] W_data_ID;
input MUXCOntrol;
input [4:0] select;
output [31:0] Data;

//ID_STAGE OUTPUT

//nine control signals
output MemtoReg_out, RegWrite_out, Branch, MemRead, MemWrite, RegDst, ALUSrc, jump;
output [1:0] ALUOp;
reg MemtoReg_out, RegWrite_out, Branch, MemRead, MemWrite, RegDst, ALUSrc, jump;
reg [1:0] ALUOp;
//reg RegWrite_Temp;
reg [31:0] Reg_Memory [31:0];

reg Final;

output [4:0] rt, rd, rs;
output [31:0] Address_out, R_Data1, R_Data2, Extend;
output [31:0] j_address;



initial begin
    for(K=0;K<32;K=K+1)
    begin
      Reg_Memory[K] = 32'b0;
    end
end

assign Data = Reg_Memory[select]; 

assign j_address[31:28] = Address_in[31:28];
assign j_address[27:2] = Instruction_ID[25:0];
assign j_address[1:0] = 2'b0;

assign Address_out = Address_in;
assign Extend = (Instruction_ID[15]) ? 32'b11111111111111110000000000000000 + Instruction_ID[15:0] : 32'b0 + Instruction_ID[15:0];
assign rt = Instruction_ID[20:16];
assign rd = Instruction_ID[15:11];
assign rs = Instruction_ID[25:21];

//Read from Register File
assign R_Data1 = Reg_Memory[Instruction_ID[25:21]];
assign R_Data2 = Reg_Memory[Instruction_ID[20:16]];


always@(negedge clock)
        begin
		  Final = ID_Flush || MUXCOntrol;
		  if(Final) begin
		      MemWrite = 0;
				MemRead = 0;
				MemtoReg_out = 0;
				ALUSrc = 0;
				jump = 0;
				RegWrite_out = 0;
				Branch = 0;
			   ALUOp = 2'b00;
				RegDst = 0;
		  end
		  else if(Instruction_ID == 0)
		  begin
		      MemWrite = 0;
				RegWrite_out = 0;	
            jump = 0;	
            Branch = 0;				
		  end
		  else begin
   	  //Control Stage
			    case (Instruction_ID[31:26])
		       6'b0: begin  //R type
				           MemWrite = 0;
							  MemRead = 0;
							  MemtoReg_out = 1;
							  ALUSrc = 0;
							  jump = 0;
							  RegWrite_out = 1;
							  Branch = 0;
							  ALUOp = 2'b10;
							  RegDst = 1;
				       end
				 6'b001000:  //addi
                   begin
				           MemWrite = 0;
							  MemRead = 0;
							  MemtoReg_out = 1;
							  ALUSrc = 1;
							  jump = 0;
							  RegWrite_out = 1;
							  Branch = 0;
							  ALUOp = 2'b00;
							  RegDst = 0;
				       end	
             6'b001100:   //andi
                   begin
				           MemWrite = 0;
							  MemRead = 0;
							  MemtoReg_out = 1;
							  ALUSrc = 1;
							  jump = 0;
							  RegWrite_out = 1;
							  Branch = 0;
							  ALUOp = 2'b11;
							  RegDst = 0;
				       end	
             6'b000010: //jump
                   begin
				           MemWrite = 0;
							  MemRead = 0;
							  MemtoReg_out = 0;
							  ALUSrc = 0;
							  jump = 1;
							  RegWrite_out = 0;
							  Branch = 0;
							  ALUOp = 2'b00;
							  RegDst = 0;
				       end		
             6'b100011: //load word
                   begin
				           MemWrite = 0;
							  MemRead = 1;
							  MemtoReg_out = 0;
							  ALUSrc = 1;
							  jump = 0;
							  RegWrite_out = 1;
							  Branch = 0;
							  ALUOp = 2'b00;
							  RegDst = 0;
				       end	
             6'b101011: //store word
                   begin
				           MemWrite = 1;
							  MemRead = 0;
							  MemtoReg_out = 1'bx;
							  ALUSrc = 1;
							  jump = 0;
							  RegWrite_out = 0;
							  Branch = 0;
							  ALUOp = 2'b00;
							  RegDst = 1'bx;
				       end		
             6'b000100: //beq
                   begin
				           MemWrite = 0;
							  MemRead = 0;
							  MemtoReg_out = 1'bx;
							  ALUSrc = 0;
							  jump = 0;
							  RegWrite_out = 0;
							  Branch = 1;
							  ALUOp = 2'b01;
							  RegDst = 1'bx;
				       end	
             default: 	
                    begin
				           MemWrite = 1'bx;
							  MemRead = 1'bx;
							  MemtoReg_out = 1'bx;
							  ALUSrc = 1'bx;
							  jump = 1'bx;
							  RegWrite_out = 1'bx;
							  Branch = 1'bx;
							  ALUOp = 2'bx;
							  RegDst = 1'bx;
				       end					 
        endcase		  
		  end
	
        if(RegWrite == 1) Reg_Memory[rtd_out_ID] = W_data_ID;
		  //RegWrite_Temp = 0;
		  
		  end
		  
		 /*initial begin
	      $display("************************************************************");
		   $display("The textual simulation results:");
		   $display("************************************************************");
		   $monitor( $time,, "read_1 = %d, read_2 = %d RegWrite = %b  RegWrite_Temp = %b rs = %d rt = %d rtd_out_ID = %d W_data_ID = %b Insturction_ID = %b",R_Data1, R_Data2, RegWrite, RegWrite_Temp, Instruction_ID[25:21],Instruction_ID[20:16], rtd_out_ID , W_data_ID, Instruction_ID);			
	   end */
		  
		/* initial begin
	      $display("The debug process in ID_STAGE");
         $monitor($time,, "clock = %b  rtd_out_ID = %d W_data_ID = %b RegWrite = %b   Reg_Memory[10] = %b", clock, rtd_out_ID, W_data_ID,RegWrite,  Reg_Memory[10]);			
	     end */ 
		  
	  initial begin
	   $display("************************************************************");
		$display("The textual simulation results:");
		$display("************************************************************");
		$monitor("Time: %g; \n [clk] = %b [Instruction] = %b  PC_Address = %d \n [$s0] = %h  [$s1] = %h  [$s2] = %h \n [$s3] = %h  [$s4] = %h  [$s5] = %h \n [$s6] = %h  [$s7] = %h  [$t0] = %h \n [$t1] = %h  [$t2] = %h  [$t3] = %h \n [$t4] = %h  [$t5] = %h  [$t6] = %h \n [$t9] = %h  [$t8] = %h  [$t9] = %h \n\t"
		        , $stime, clock, Instruction_ID, Address_in - 4, Reg_Memory[16], Reg_Memory[17], Reg_Memory[18], Reg_Memory[19], 
					 Reg_Memory[20], Reg_Memory[21], Reg_Memory[22], Reg_Memory[23],
					 Reg_Memory[8], Reg_Memory[9], Reg_Memory[10], Reg_Memory[11], Reg_Memory[12]
					 , Reg_Memory[13], Reg_Memory[14], Reg_Memory[15], Reg_Memory[24], Reg_Memory[25]);
	    end
		 
		 
		  
endmodule
