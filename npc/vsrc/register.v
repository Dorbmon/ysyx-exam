import "DPI-C" function void set_gpr_ptr(input logic [63:0] a []);
`include "vsrc/alu_define.v"
module ysyx_22041207_RegisterFile #(REGISTER_NUM = 2, ADDR_WIDTH = 1, DATA_WIDTH = 1) (
  input clk,
  input [DATA_WIDTH-1:0] wdata,
  input [ADDR_WIDTH-1:0] waddr,
  input [ADDR_WIDTH-1:0] r1addr,
  output [DATA_WIDTH-1:0] r1data,
  input [ADDR_WIDTH-1:0] r2addr,
  output [DATA_WIDTH-1:0] r2data,
  input wen
);
  
  initial set_gpr_ptr(rf);  // rf为通用寄存器的二维数组变量
  reg [DATA_WIDTH-1:0] rf [REGISTER_NUM-1:0];
  assign r1data = rf[r1addr];
  assign r2data = rf[r2addr];
  always @(posedge clk) begin
    if (wen && waddr != 0) rf[waddr] <= wdata;
    //$display("a1:%b", rf [1]);
  end
endmodule
// 0x341 mepc
// 0x342 mcause
// 0x305 mtvec
module ysyx_22041207_csrRegister (
  input clk,
  input [11:0] address,
  input [63:0] writeValue,
  input wMtvec,
  input [63:0] mtvec_v,
  input wMepc,
  input [63:0] mepc_v,
  input wMcause,
  input [63:0] mcause_v,
  input wen,
  output [63:0] mtvec_o,
  output [63:0] mepc_o,
  output [63:0] mcause_o,
  output reg [63:0] readData
);

reg [63:0] mepc, mcause, mtvec;
assign mtvec_o = mtvec;
assign mepc_o = mepc;
assign mcause_o = mcause;
always @(posedge clk) begin
  if (address == `CSR_MCAUSE_ADDRESS && wen) begin
    mcause <= writeValue;
  end else if (wMcause) begin
    mcause <= mcause_v;
  end
end
always @(posedge clk) begin
  if (address == `CSR_MEPC_ADDRESS && wen) begin
    mepc <= writeValue;
  end else if (wMepc) begin
    mepc <= mepc_v;
  end
end
always @(posedge clk) begin
  if (address == `CSR_MTVEC_ADDRESS && wen) begin
    mtvec <= writeValue;
  end else if (wMtvec) begin
    mtvec <= mtvec_v;
  end
end
always @(posedge clk) begin
  case (address)
  `CSR_MCAUSE_ADDRESS: readData = mcause;
  `CSR_MEPC_ADDRESS: readData = mepc;
  `CSR_MTVEC_ADDRESS: readData = mtvec;
  default: readData = 0;
  endcase
end
endmodule