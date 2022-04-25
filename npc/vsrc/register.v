module RegisterFile #(REGISTER_NUM = 2, ADDR_WIDTH = 1, DATA_WIDTH = 1) (
  input clk,
  input [DATA_WIDTH-1:0] wdata,
  input [ADDR_WIDTH-1:0] waddr,
  input [ADDR_WIDTH-1:0] raddr,
  input wen,
  output [DATA_WIDTH-1:0] rdata
);
  reg [DATA_WIDTH-1:0] rf [REGISTER_NUM-1:0];
  assign rdata = rf[raddr];
  always @(posedge clk) begin
    if (wen && waddr != 0) rf[waddr] <= wdata;
  end
endmodule