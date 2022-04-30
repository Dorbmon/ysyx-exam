import "DPI-C" function void set_gpr_ptr(input logic [63:0] a []);
module RegisterFile #(REGISTER_NUM = 2, ADDR_WIDTH = 1, DATA_WIDTH = 1) (
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