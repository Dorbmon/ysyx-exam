module bcd7seg(
  input  [2:0] b,
  output reg [6:0] h
);
always @(b)
  case (b) // 共阳极
    3'b000 : h = ~7'b1111110;
    3'b001 : h = ~7'b0110000;
    3'b010 : h = ~7'b1101101;
    3'b011 : h = ~7'b1111001;
    3'b100 : h = ~7'b0110011;
    3'b101 : h = ~7'b1011011;
    3'b110 : h = ~7'b1011111;
    3'b111 : h = ~7'b1110000;
    default: h = ~7'b0000000;
  endcase
endmodule
/* verilator lint_off UNOPTFLAT */
module top(clk,HEX0,HEX1,HEX2);
output [6:0] HEX0, HEX1, HEX2;
input clk;
reg c;
reg [7:0] s0,s1,s2;
reg [7:0] count;
reg [7:0] data;
bcd7seg seg0(s0[2:0],HEX0);
bcd7seg seg1(s1[2:0],HEX1);
bcd7seg seg2(s2[2:0],HEX2);
always @(clk) // 周期为1S
begin
  if (data == 0)
    data = 8'b11111111;
  // 移动
  data = {data[0]^data[2]^data[3]^data[4],data[6:0]};
  s0 = data % 10;
  s1 = (data / 10) % 10;
  s2 = (data / 100) % 10;
end
endmodule