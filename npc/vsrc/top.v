module bcd7seg(
  input  [2:0] b,
  input e,
  output reg [6:0] h
);
always @(b,e) begin
  if (~e)
    h = ~7'b0000000; 
  else 
  case (b) // 共阳极
  	3'b000 : h = ~7'b0111111;
	  3'b001 : h = ~7'b0000011;
	  3'b010 : h = ~7'b1011011;
	  3'b011 : h = ~7'b1000111;
	  3'b100 : h = ~7'b1100110;
	  3'b101 : h = ~7'b1101101;
	  3'b110 : h = ~7'b1111101;
	  3'b111 : h = ~7'b0000111;
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