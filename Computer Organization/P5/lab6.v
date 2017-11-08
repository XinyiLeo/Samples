`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:26:17 06/29/2015 
// Design Name: 
// Module Name:    lab6 
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
module lab6(clock, re, SSDv, ringresult);
input clock;
input re;
output [6:0] SSDv;
output[3:0] ringresult;
wire fiveclock;
wire oneclock;
wire [3:0] one;
wire [2:0] ten;
onedividor M2 (clock, re, oneclock);
ring M3 (clock, re, ringresult);
timer M4 (oneclock, re, one, ten);
SSD M5 (one, ten, ringresult, SSDv);
endmodule



module onedividor(clock, reset, Out);
parameter n = 1;
input clock;
input reset;
output Out;
reg Out;
reg [n:0] count;
always@(posedge clock or posedge reset)begin
    if(reset == 1) begin Out = 0; count = 0; end
	 else begin
	     count=count+1;
		  if(count == 500) begin Out = 1;count=0;end
		  else Out=0;
	 end
end
endmodule

module timer(clock, reset, oneOut, tenOut);
input clock;
input reset;
output [3:0] oneOut;
output [2:0] tenOut;
reg [3:0]oneOut;
reg [2:0] tenOut;
always@(posedge clock or posedge reset)begin
    if(reset == 1) begin oneOut = 0; tenOut = 0; end
	 else begin
	     if(oneOut == 9) begin 
		      oneOut = 0; 
				if(tenOut == 5) tenOut = 0;
				else tenOut=tenOut+1;
		  end
		  else if(oneOut == 7'bXXXXXXX)begin oneOut = 0;tenOut = 0; end
		  else oneOut = oneOut+1;
	 end
end
endmodule

module ring(clock,reset, Out);
input clock;
input reset;
output [3:0] Out;
reg [3:0] Out;
always@(posedge clock or posedge reset)begin
    if(reset == 1) Out = 4'b1110;
    else begin
	     case (Out)
		  4'b1110: Out=4'b1101;
		  4'b1101: Out=4'b1011;
		  4'b1011: Out=4'b0111;
		  4'b0111: Out=4'b1110;
		  endcase
    end	 
end
endmodule


module SSD (oneclock, tenclock, ringresult, SSDr);
input [3:0] oneclock;
input [2:0] tenclock;
input [3:0] ringresult;
output [6:0] SSDr;
reg [6:0] SSDr;
always@(ringresult)begin
    if(ringresult == 4'b1110)begin
	     case (oneclock)
		    0:       SSDr = 1;
		    1:       SSDr = 79;
			 2:       SSDr = 18;
		    3:       SSDr = 6;
			 4:       SSDr = 76;
		    5:       SSDr = 36;
			 6:       SSDr = 32;
		    7:       SSDr = 15;
			 8:       SSDr = 0;
		    9:       SSDr = 4;
		  endcase
	 end
	 else if(ringresult == 4'b1101)begin
	     case (tenclock)
	       0:       SSDr = 1;
		    1:       SSDr = 79;
			 2:       SSDr = 18;
		    3:       SSDr = 6;
			 4:       SSDr = 76;
		    5:       SSDr = 36;
        endcase
	 end
	 else if(ringresult == 4'b1011) SSDr = 127;
	 else if(ringresult == 4'b0111) SSDr = 127;
end
endmodule

