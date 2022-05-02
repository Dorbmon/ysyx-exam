module ysyx_22041207_MR (
    input wen,
    input [63:0] readAddr,
    output reg [63:0] data
);
import "DPI-C" function void pmem_read(
  input longint raddr, output longint rdata);
always @(*) begin
  if (wen) begin
    pmem_read(readAddr, data);
  end
  else begin
    data = 0;
  end
end
endmodule
module ysyx_22041207_MW (
    input [63:0] waddr,
    input [63:0] wdata,
    input [7:0]  wmask
);
import "DPI-C" function void pmem_write(
  input longint waddr, input longint wdata, input byte wmask);
always @(*) begin
  pmem_write(waddr, wdata, wmask);
end
endmodule
