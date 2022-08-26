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
    output reg [63:0] dout,
    // axi 写
    output reg                  w_valid_i,
	  input                       w_ready_o,
    output reg [63:0]           w_data_i,
    output  reg [63:0]          w_addr_i,
    output reg [7:0]            w_mask_i,
    input  wire                 w_valid_o,
    output  wire                 w_ready_i,
    // axi 读
    output reg rx_r_valid_i,
    input      rx_r_ready_o,
    input [63:0] rx_data_read_o,
    output reg [63:0] rx_r_addr_i,
    output [7:0] rx_r_size_i,
    input rx_data_valid,
    output reg rx_data_ready,
    output reg me_wait_for_axi
);
initial begin
  me_wait_for_axi = 0;
  busy = 0;
end
reg busy;
always @(posedge clk) begin
  // 写入
  if (wmask != 8'b0 && ~busy) begin  // 说明要进入数据写入，可以开始卡住流水线了
    busy <= 1;
    w_valid_i <= 1;
    w_addr_i <= addr;
    case (addr[2:0])
    default: w_mask_i <= 0;
    3'h0: w_mask_i <= wmask;
    3'h1: w_mask_i <= wmask<<1;
    3'h2: w_mask_i <= wmask<<2;
    3'h4: w_mask_i <= wmask<<4;
    endcase
    case (addr[2:0])
    default: w_data_i <= 0;
    3'h0: w_data_i <= rs2;
    3'h1: w_data_i <= rs2<<8;
    3'h2: w_data_i <= rs2<<16;
    3'h4: w_data_i <= rs2<<32;
    endcase
    me_wait_for_axi <= 1;
  end
  if (w_valid_i && w_ready_o) begin
    w_valid_i <= 0; // axi模块已经收到写入请求
    w_ready_i <= 1;
  end
  if (w_valid_o && w_ready_i) begin  // 已经完成写入
    //$display("write %x %x %b", w_addr_i, w_data_i, w_mask_i);
    w_ready_i <= 0;
    me_wait_for_axi <= 0;
    busy <= 0;
  end

  // 读取
  if (readWen && ~busy) begin
    rx_r_valid_i <= 1;
    rx_r_addr_i <= addr;
    me_wait_for_axi <= 1;
    busy <= 1;
  end
  if (rx_r_valid_i && rx_r_ready_o) begin // axi模块已经收到读取请求
    rx_r_valid_i <= 0;
    rx_data_ready <= 1;
  end
  if (rx_data_valid && rx_data_ready) begin  // 收到axi模块返回的数据
    rx_data_ready <= 0;
    busy <= 0;
    me_wait_for_axi <= 0;
    if (sext) begin
      $display("sext");
      // 需要做符号扩展
      dout <= (readNum == 1) ? `SEXT(rx_data_read_o, 64, 8)
      : ((readNum == 2) ? `SEXT(rx_data_read_o, 64, 16)
      : ((readNum == 4) ? `SEXT(rx_data_read_o, 64, 32)
      : ((readNum == 8) ? `SEXT(rx_data_read_o, 64, 64) : 0
      )));
    end
    else begin
      dout <= (readNum == 1) ? `NSEXT(rx_data_read_o, 64, 8)
      : ((readNum == 2) ? `NSEXT(rx_data_read_o, 64, 16)
      : ((readNum == 4) ? `NSEXT(rx_data_read_o, 64, 32)
      : ((readNum == 8) ? `NSEXT(rx_data_read_o, 64, 64) : 0
      )));
    end
  end
  
end
endmodule