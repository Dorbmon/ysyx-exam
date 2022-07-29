// 所有写入数据都是从rs2中而来
module ysyx_22041207_Memory (
    input readWen,
    input [63:0] addr,
    input [63:0] rs2,
    input [7:0]  wmask,
    output reg [63:0] dout
);
import "DPI-C" function void pmem_write(
  input longint waddr, input longint wdata, input byte wmask);
wire [3:0] num = 4'b1000 - addr [2:0]; // 在第一个8字节内写入的数量
reg [63:0] readData;
ysyx_22041207_read_mem read(addr, (wmask == 8'b0 && readWen), readData);
always @(*) begin
  if (wmask == 8'b0) begin
    // 读取操作
    dout = readData;
  end
  else begin
    $display("write:%x\n", addr);
    pmem_write(addr, rs2 << (addr [2:0] * 8'b1000), wmask << addr [2:0]);
    pmem_write(addr + 64'b1000, rs2 >> (num * 8'b1000), wmask >> num);
    dout = 64'b0;
  end
  
end
endmodule