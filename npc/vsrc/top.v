//`include "vsrc/template.v"
//`include "vsrc/register.v"
//`include "vsrc/addi.v"
module ysyx_22041207_top (
  input [31:0] inst,
  input rst,  // 复位信号
  input clk,
  output reg [31:0] pc
);

wire [4:0] r1addr,r2addr,rwaddr;
wire [63:0] r1data,r2data,rwdata;
wire wen;
RegisterFile #(32, 5, 64) r(clk, rwdata, rwaddr, r1addr, r1data, r2addr, r2data, wen);
always @ (posedge rst or posedge clk) begin
  if (rst) begin
    pc <= 32'h80000000;
  end
  else begin
    pc <= pc + 32'h00000004;
  end
end
ControlUnit cu(inst, r1addr, r2addr, rwaddr, rwdata, r1data, r2data, wen);
//end
endmodule