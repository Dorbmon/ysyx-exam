module ysyx_22041207_Memory(
    input [63:0] raddr,
    output [63:0] rdata,
    input [63:0] waddr,
    input [63:0] wdata,
    input [7:0] wmask
);

import "DPI-C" function void pmem_read(
  input longint raddr, output longint rdata);
import "DPI-C" function void pmem_write(
  input longint waddr, input longint wdata, input byte wmask);
always @(*) begin
  pmem_read(raddr, rdata);
  pmem_write(waddr, wdata, wmask);
end
endmodule