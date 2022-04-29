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
    pc <= pc + 32'h00000001;
  end
end
wire [63:0] immI;
wire [63:0] immS;
wire [63:0] immB;
wire [63:0] immU;
wire [63:0] immJ;
assign rwaddr = inst[11:7];
assign r1addr = inst[19:15];
assign r2addr = inst[24:20];
ysyx_22041207_ext ext(inst, immI, immS, immB, immU, immJ);
ysyx_22041207_ALU alu(inst, r1data, r2data, wen, rwdata);

// ControlUnit cu(inst, r1addr, r2addr, rwaddr, rwdata, r1data, r2data, wen, pc);
//end
endmodule