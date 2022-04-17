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

module clock(clk,c);
input clk;
output reg c;
reg [31:0] count;
always @(posedge clk) //只读取上行 若频率为50MHz 则25MHZ进行一次反转 即可做到每秒计时
begin
  if (count == 24999999) begin
    count <= 0;
    c <= ~c;
  end 
  else begin
    count <= count + 1;
  end
end
endmodule
module top(clk,HEX0,HEX1);
output [6:0] HEX0, HEX1;
input clk;
reg c;
reg [6:0] s0,s1;
reg [6:0] count;
clock timer1(clk,c);
bcd7seg seg0(s0[2:0],HEX0);
bcd7seg seg1(s1[2:0],HEX1);
always @(posedge c) // 周期为1S
begin
  count = count + 1;
  s0 = count % 10;
  s1 = (count / 10) - s0;
  if (count == 100)
    count = 0;
end
endmodule