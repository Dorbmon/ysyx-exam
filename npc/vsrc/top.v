`include "vsrc/template.v"
`include "vsrc/register.v"
`include "vsrc/addi.v"
module ysyx_22041207_top (
  input [31:0] inst,
  input rst,  // 复位信号
  input clk,
  output reg [31:0] pc
);
wire [4:0] regReadaddr,regWriteaddr;
wire [63:0] regReaddata,regWritedata;
wire wen;
RegisterFile #(32, 5, 64) r(clk, regWritedata, regWriteaddr, regReadaddr,wen, regReaddata);
always @ (posedge rst) begin
  pc <= 32'h80000000;
end
//always @ (posedge clk) begin
  wire [74:0] waddi;
  ysyx_22041207_addi addi(clk, inst,regReaddata,  waddi);
  ysyx_22041207_MuxKey #(1, 7, 75) i0 ({wen, regReadaddr, regWriteaddr, regWritedata}, inst[6:0],  {
    7'b0010011, waddi   // addi
  });
//end
endmodule