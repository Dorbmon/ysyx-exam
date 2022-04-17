module bcd7seg(
  input  [2:0] b,
  input e,
  output reg [6:0] h
);
/*
assign segs[0] = 8'b1111110;
assign segs[1] = 8'b0110000;
assign segs[2] = 8'b1101101;
assign segs[3] = 8'b1111001;
assign segs[4] = 8'b0110011;
assign segs[5] = 8'b1011011;
assign segs[6] = 8'b1011111;
assign segs[7] = 8'b1110000;
*/
always @(b,e) begin
  if (~e)
    h = ~7'b0000000; 
  else 
  case (b) // 共阳极
  	3'b000 : h = ~7'b1111110;
	  3'b001 : h = ~7'b0110000;
	  3'b010 : h = ~7'b0110000;
	  3'b011 : h = ~7'b0110000;
	  3'b100 : h = ~7'b0110000;
	  3'b101 : h = ~7'b0110000;
	  3'b110 : h = ~7'b0110000;
	  3'b111 : h = ~7'b0110000;
    default: h = ~7'b0000000;
  endcase
end
endmodule
module top(x,e,y,indicator,HEX0);
input [7:0] x;
input e;
output [6:0] HEX0;
output reg [2:0] y;
output reg indicator;
integer i;
bcd7seg seg7(y,e,HEX0);
always @(x or e) begin
  y = 0;
  indicator = 0;
  if (e) begin
    for (i = 0;i <= 7;i ++) begin
      if(x[i] == 1) begin
        y = i[2:0];
      end
    end
    if (y == 3'b000)
      indicator = 0;
    else
      indicator = 1;
  end 
  else begin
    y = 0;
  end
end 
endmodule