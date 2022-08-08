module ysyx_22041207_read_mem(
    input       [63:0]      readAddr    ,// alu的计算结果就是读取的地址
    input wen,
    output      reg [63:0]      data
);
import "DPI-C" function void pmem_read(
  input longint raddr, output longint rdata);
always @(readAddr) begin
  reg [63:0] data1;
  reg [63:0] data2;
  if (wen) begin
    $display("read:%x, wen:%b", readAddr, wen);
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
        data1 = 0;
        data2 = 0;
    end
  end
  else begin
    data = 0;
    data1 = 0;
    data2 = 0;
  end
end
endmodule