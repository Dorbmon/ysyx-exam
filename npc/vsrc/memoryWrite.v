// 所有写入数据都是从rs2中而来
`include "vsrc/alu_define.v"
module ysyx_22041207_Memory (
    input clk,
    input readWen,
    input [63:0] addr,
    input [63:0] rs2,
    input [7:0]  wmask,
    input sext,
    input [3:0] readNum,
    output reg [63:0] dout
);
import "DPI-C" function void pmem_write(
  input longint waddr, input longint wdata, input byte wmask);
wire [3:0] num = 4'b1000 - addr [2:0]; // 在第一个8字节内写入的数量
reg [63:0] readData;

ysyx_22041207_read_mem read(addr, (wmask == 8'b0 && readWen), readData);
always @(posedge clk) begin
  if (wmask == 8'b0) begin
    // 读取操作
    dout = readData;
    if (sext) begin
      // 需要做符号扩展
      dout = (readNum == 1) ? `SEXT(readData, 64, 8)
      : ((readNum == 2) ? `SEXT(readData, 64, 16)
      : ((readNum == 4) ? `SEXT(readData, 64, 32)
      : ((readNum == 8) ? `SEXT(readData, 64, 64) : 0
      )));
    end
    else begin
      dout = (readNum == 1) ? `NSEXT(readData, 64, 8)
      : ((readNum == 2) ? `NSEXT(readData, 64, 16)
      : ((readNum == 4) ? `NSEXT(readData, 64, 32)
      : ((readNum == 8) ? `NSEXT(readData, 64, 64) : 0
      )));
    end
  end
  else begin
    pmem_write(addr, rs2 << (addr [2:0] * 8'b1000), wmask << addr [2:0]);
    if (addr[2:0] != 3'b0) begin
      pmem_write(addr + 64'b1000, rs2 >> (num * 8'b1000), wmask >> num);
    end
    dout = 64'b0;
  end
  
end
endmodule