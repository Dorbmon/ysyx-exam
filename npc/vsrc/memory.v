module ysyx_22041207_MR (
    input wen,
    input [63:0] readAddr,
    output reg [63:0] data
);
import "DPI-C" function void pmem_read(
  input longint raddr, output longint rdata);
always_latch @(readAddr) begin
  reg [63:0] data1;
  reg [63:0] data2;
  if (wen) begin
    //s$display("read:%x", readAddr);
    //if (readAddr & )
    pmem_read(readAddr, data1);
    pmem_read(readAddr + 64'b1000, data2);  // 读取八个字节之后的内容
    if (readAddr[2:0] == 3'b000) begin
        data = data1;
    end
    else if (readAddr[2:0] == 3'b001) begin
        data = {data2[7:0], data1[63:8]};
    end
    else if (readAddr[2:0] == 3'b010) begin
        data = {data2[15:0], data1[63:16]};
    end
    else if (readAddr[2:0] == 3'b011) begin
        data = {data2[23:0], data1[63:24]};
    end
    else if (readAddr[2:0] == 3'b100) begin
        data = {data2[31:0], data1[63:32]};
    end
    else if (readAddr[2:0] == 3'b101) begin
        data = {data2[39:0], data1[63:40]};
    end
    else if (readAddr[2:0] == 3'b110) begin
        data = {data2[47:0], data1[63:48]};
    end
    else if (readAddr[2:0] == 3'b111) begin
        data = {data2[55:0], data1[63:56]};
    end
    else begin
        data = 0;
    end
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
wire [3:0] num = 4'b1000 - waddr [2:0]; // 在一个字节内写入的数量
always @(*) begin
  pmem_write(waddr, wdata << waddr [2:0], wmask << waddr [2:0]);
  pmem_write(waddr + 64'b1000, wdata >> (num * 8'b1000), wmask >> num);
end
endmodule
