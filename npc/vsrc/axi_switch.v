module ysyx_22041207_axi_switch# (
    parameter RW_DATA_WIDTH     = 64,
    parameter RW_ADDR_WIDTH     = 64,
    parameter AXI_DATA_WIDTH    = 64,
    parameter AXI_ADDR_WIDTH    = 64,
    parameter AXI_ID_WIDTH      = 4,
    parameter AXI_STRB_WIDTH    = AXI_DATA_WIDTH/8,
    parameter AXI_USER_WIDTH    = 1
) (   // axi 读选择器
    input clk,
    input                               mem_r_valid_i,         //IF&MEM输入信号
	output reg                             mem_r_ready_o,         //IF&MEM输入信号
    output reg [RW_DATA_WIDTH-1:0]      mem_data_read_o,        //IF&MEM输入信号
    input  [RW_ADDR_WIDTH-1:0]          mem_r_addr_i,          //IF&MEM输入信号
    input  [7:0]                        mem_r_size_i,          //IF&MEM输入信号
    output                              mem_r_data_valid,   // 读取数据是否有效
    input                               mem_r_data_ready,   // 是否读取完成

    input                               if_r_valid_i,         //IF&MEM输入信号
	output reg                             if_r_ready_o,         //IF&MEM输入信号
    output reg [RW_DATA_WIDTH-1:0]      if_data_read_o,        //IF&MEM输入信号
    input  [RW_ADDR_WIDTH-1:0]          if_r_addr_i,          //IF&MEM输入信号
    input  [7:0]                        if_r_size_i,          //IF&MEM输入信号
    output                              if_r_data_valid,   // 读取数据是否有效
    input                               if_r_data_ready,   // 是否读取完成

    output  reg                             s_r_valid_i,         //IF&MEM输入信号
	input                              s_r_ready_o,         //IF&MEM输入信号
    input  [RW_DATA_WIDTH-1:0]      s_data_read_o,        //IF&MEM输入信号
    output reg [RW_ADDR_WIDTH-1:0]          s_r_addr_i,          //IF&MEM输入信号
    output reg [7:0]                        s_r_size_i,          //IF&MEM输入信号
    input                              s_r_data_valid,   // 读取数据是否有效
    output  reg                             s_r_data_ready   // 是否读取完成
);
initial begin
    memUsing = 0;
    busy = 0;
end

reg memUsing, busy;
always @(posedge clk) begin
    // mem模块优先级更高，如果mem模块有信号，那就给mem模块，否则给if模块
    if (mem_r_valid_i && ~busy) begin    // mem抢占了
        memUsing <= 1;
        busy <= 1;
    end else if (if_r_valid_i && ~busy) begin   // if抢占
        busy <= 1;
    end
    if (s_r_data_valid && ( memUsing ? mem_r_data_ready : if_r_data_ready)) begin
        busy <= 0;
        memUsing <= 0;
    end
end
always @(posedge clk) begin
    s_r_valid_i <= memUsing ? mem_r_valid_i : if_r_valid_i;
    mem_r_ready_o <= memUsing ? s_r_ready_o : 0; if_r_ready_o <= memUsing ? 0 : s_r_ready_o; 
    
    s_r_addr_i <= memUsing ? mem_r_addr_i : if_r_addr_i;
    s_r_size_i <= memUsing ? mem_r_size_i : if_r_size_i;

    mem_r_data_valid <= memUsing ? s_r_data_valid : 0; if_r_data_valid <= memUsing ? 0 : s_r_data_valid;
    s_r_data_ready <= memUsing ? mem_r_data_ready : if_r_data_ready;
    mem_data_read_o <= s_data_read_o;
    if_data_read_o <= s_data_read_o;
end
endmodule