// Burst types
`define AXI_BURST_TYPE_FIXED                                2'b00               //突发类型  FIFO
`define AXI_BURST_TYPE_INCR                                 2'b01               //ram  
`define AXI_BURST_TYPE_WRAP                                 2'b10
// Access permissions
`define AXI_PROT_UNPRIVILEGED_ACCESS                        3'b000
`define AXI_PROT_PRIVILEGED_ACCESS                          3'b001
`define AXI_PROT_SECURE_ACCESS                              3'b000
`define AXI_PROT_NON_SECURE_ACCESS                          3'b010
`define AXI_PROT_DATA_ACCESS                                3'b000
`define AXI_PROT_INSTRUCTION_ACCESS                         3'b100
// Memory types (AR)
`define AXI_ARCACHE_DEVICE_NON_BUFFERABLE                   4'b0000
`define AXI_ARCACHE_DEVICE_BUFFERABLE                       4'b0001
`define AXI_ARCACHE_NORMAL_NON_CACHEABLE_NON_BUFFERABLE     4'b0010
`define AXI_ARCACHE_NORMAL_NON_CACHEABLE_BUFFERABLE         4'b0011
`define AXI_ARCACHE_WRITE_THROUGH_NO_ALLOCATE               4'b1010
`define AXI_ARCACHE_WRITE_THROUGH_READ_ALLOCATE             4'b1110
`define AXI_ARCACHE_WRITE_THROUGH_WRITE_ALLOCATE            4'b1010
`define AXI_ARCACHE_WRITE_THROUGH_READ_AND_WRITE_ALLOCATE   4'b1110
`define AXI_ARCACHE_WRITE_BACK_NO_ALLOCATE                  4'b1011
`define AXI_ARCACHE_WRITE_BACK_READ_ALLOCATE                4'b1111
`define AXI_ARCACHE_WRITE_BACK_WRITE_ALLOCATE               4'b1011
`define AXI_ARCACHE_WRITE_BACK_READ_AND_WRITE_ALLOCATE      4'b1111
// Memory types (AW)
`define AXI_AWCACHE_DEVICE_NON_BUFFERABLE                   4'b0000
`define AXI_AWCACHE_DEVICE_BUFFERABLE                       4'b0001
`define AXI_AWCACHE_NORMAL_NON_CACHEABLE_NON_BUFFERABLE     4'b0010
`define AXI_AWCACHE_NORMAL_NON_CACHEABLE_BUFFERABLE         4'b0011
`define AXI_AWCACHE_WRITE_THROUGH_NO_ALLOCATE               4'b0110
`define AXI_AWCACHE_WRITE_THROUGH_READ_ALLOCATE             4'b0110
`define AXI_AWCACHE_WRITE_THROUGH_WRITE_ALLOCATE            4'b1110
`define AXI_AWCACHE_WRITE_THROUGH_READ_AND_WRITE_ALLOCATE   4'b1110
`define AXI_AWCACHE_WRITE_BACK_NO_ALLOCATE                  4'b0111
`define AXI_AWCACHE_WRITE_BACK_READ_ALLOCATE                4'b0111
`define AXI_AWCACHE_WRITE_BACK_WRITE_ALLOCATE               4'b1111
`define AXI_AWCACHE_WRITE_BACK_READ_AND_WRITE_ALLOCATE      4'b1111

`define AXI_SIZE_BYTES_1                                    3'b000                //突发宽度一个数据的宽度
`define AXI_SIZE_BYTES_2                                    3'b001
`define AXI_SIZE_BYTES_4                                    3'b010
`define AXI_SIZE_BYTES_8                                    3'b011
`define AXI_SIZE_BYTES_16                                   3'b100
`define AXI_SIZE_BYTES_32                                   3'b101
`define AXI_SIZE_BYTES_64                                   3'b110
`define AXI_SIZE_BYTES_128                                  3'b111


module axi_rw # (
    parameter RW_DATA_WIDTH     = 64,
    parameter RW_ADDR_WIDTH     = 64,
    parameter AXI_DATA_WIDTH    = 64,
    parameter AXI_ADDR_WIDTH    = 64,
    parameter AXI_ID_WIDTH      = 4,
    parameter AXI_STRB_WIDTH    = AXI_DATA_WIDTH/8,
    parameter AXI_USER_WIDTH    = 1
)(
    input                               clock,
    input                               reset,

	input                               r_valid_i,         //IF&MEM输入信号
	output reg                             r_ready_o,         //IF&MEM输入信号
    output reg [RW_DATA_WIDTH-1:0]      data_read_o,        //IF&MEM输入信号
    input  [RW_ADDR_WIDTH-1:0]          r_addr_i,          //IF&MEM输入信号
    input  [7:0]                        r_size_i,          //IF&MEM输入信号
    output                              r_data_valid,   // 读取数据是否有效
    input                               r_data_ready,   // 是否读取完成

    input                               w_valid_i,         //IF&MEM输入信号
	output  reg                            w_ready_o,         //IF&MEM输入信号
    input [RW_DATA_WIDTH-1:0]           w_data_i,        //IF&MEM输入信号
    input  [RW_ADDR_WIDTH-1:0]          w_addr_i,          //IF&MEM输入信号
    input  [7:0]                        w_mask_i,          //IF&MEM输入信号
    output                              w_valid_o,
    input                               w_ready_i,
    // Advanced eXtensible Interface
    input                               axi_aw_ready_i,              
    output                              axi_aw_valid_o,
    output [AXI_ADDR_WIDTH-1:0]         axi_aw_addr_o,
    output [2:0]                        axi_aw_prot_o,
    output [AXI_ID_WIDTH-1:0]           axi_aw_id_o,
    output [AXI_USER_WIDTH-1:0]         axi_aw_user_o,
    output [7:0]                        axi_aw_len_o,
    output [2:0]                        axi_aw_size_o,
    output [1:0]                        axi_aw_burst_o,
    output                              axi_aw_lock_o,
    output [3:0]                        axi_aw_cache_o,
    output [3:0]                        axi_aw_qos_o,
    output [3:0]                        axi_aw_region_o,

    input                               axi_w_ready_i,                
    output                              axi_w_valid_o,
    output [AXI_DATA_WIDTH-1:0]         axi_w_data_o,
    output [AXI_DATA_WIDTH/8-1:0]       axi_w_strb_o,
    output                              axi_w_last_o,
    output [AXI_USER_WIDTH-1:0]         axi_w_user_o,
    
    output                              axi_b_ready_o,                
    input                               axi_b_valid_i,
    input  [1:0]                        axi_b_resp_i,                 
    input  [AXI_ID_WIDTH-1:0]           axi_b_id_i,
    input  [AXI_USER_WIDTH-1:0]         axi_b_user_i,

    input                               axi_ar_ready_i,                
    output                              axi_ar_valid_o,
    output [AXI_ADDR_WIDTH-1:0]         axi_ar_addr_o,
    output [2:0]                        axi_ar_prot_o,
    output [AXI_ID_WIDTH-1:0]           axi_ar_id_o,
    output [AXI_USER_WIDTH-1:0]         axi_ar_user_o,
    output [7:0]                        axi_ar_len_o,
    output [2:0]                        axi_ar_size_o,
    output [1:0]                        axi_ar_burst_o,
    output                              axi_ar_lock_o,
    output [3:0]                        axi_ar_cache_o,
    output [3:0]                        axi_ar_qos_o,
    output [3:0]                        axi_ar_region_o,
    
    output                              axi_r_ready_o,                 
    input                               axi_r_valid_i,                
    input  [1:0]                        axi_r_resp_i,
    input  [AXI_DATA_WIDTH-1:0]         axi_r_data_i,
    input                               axi_r_last_i,
    input  [AXI_ID_WIDTH-1:0]           axi_r_id_i,
    input  [AXI_USER_WIDTH-1:0]         axi_r_user_i
);
    
    // ------------------State Machine------------------TODO
    wire cache_hit;
    reg cache_update_en, cache_wupdate_en;
    assign cache_update_data = axi_r_data_i; // 读缓存更新
    assign cache_update_address = r_addr_i;
    assign cache_wupdate_address = w_addr_i;
    assign cache_wupdate_data = w_data_i;
    wire [63:0] cache_data, cache_update_address, cache_update_data, cache_wupdate_address, cache_wupdate_data;
    ysyx_22041207_cache rx_cache(clock, reset, r_addr_i, cache_hit, cache_data, 
    cache_wupdate_en, cache_wupdate_address, cache_wupdate_data, w_mask_i, cache_update_en, cache_update_address, cache_update_data);
    // 写通道状态切换
    initial begin
        w_ready_o = 0;
        w_state_write = 0;
        w_state_resp = 0;
    end
    reg w_state_addr, w_state_write, w_state_resp;
    always @(posedge clock) begin
        if (w_valid_i && ~w_ready_o) begin    // 外部模块要求写入数据
            w_ready_o <= 1;
            w_state_addr <= 1;
            w_state_write <= 1;
        end
        if (w_valid_i && w_ready_o) begin    // 外部模块要求写入数据
            w_ready_o <= 0;
        end
        if (w_state_addr && axi_aw_ready_i) begin   // 已经收到了写入地址
            w_state_addr <= 0;
            w_state_resp <= 1;
        end
        if (w_state_write && axi_w_ready_i) begin   // 已经收到了写入数据
            w_state_write <= 0;
            w_state_resp <= 1;
            cache_wupdate_en <= 1;
        end
        if (axi_b_valid_i && w_state_resp) begin    // 收到了响应，完成写入
            w_state_resp <= 0;
            w_valid_o <= 1;
        end
        if (cache_wupdate_en) begin
            cache_wupdate_en <= 0;
        end
        if (w_valid_o && w_ready_i) begin
            w_valid_o <= 0;
        end
    end

    // 读通道状态切换
    reg r_state_addr, r_state_read;
    initial begin
        r_state_addr = 0;
        r_state_read = 0;
    end
    always @(posedge clock) begin
        if (r_valid_i && ~r_ready_o) begin  // 收到外部模块读请求
            if (cache_hit) begin    // 缓存击中，那就直接读缓存
                //$display("cache hit");
                r_ready_o <= 1; // 告诉外部模块，已经读取到请求
                r_state_addr <= 1;  // 那就不读了
            end else begin
                r_ready_o <= 1; // 告诉外部模块，已经读取到请求
                r_state_addr <= 1;  // 告知从机地址已准备就绪
            end
        end
        if (r_valid_i && r_ready_o) begin
            // if (cache_hit) begin
            //     case (r_addr_i[2:0])
            //     default: data_read_o <= 0;
            //     3'h1: data_read_o <= cache_data >> 8;
            //     3'h2: data_read_o <= cache_data >> 16;
            //     3'h3: data_read_o <= cache_data >> 24;
            //     3'h4: data_read_o <= cache_data >> 32;
            //     3'h5: data_read_o <= cache_data >> 40;
            //     3'h6: data_read_o <= cache_data >> 48;
            //     3'h7: data_read_o <= cache_data >> 56;
            //     3'h0: data_read_o <= cache_data;
            //     endcase
            //     r_data_valid <= 1;
            // end
            r_ready_o <= 0;
        end
        if (axi_ar_ready_i && r_state_addr) begin   // 从机已经接收到地址了
            r_state_addr <= 0;
            r_state_read <= 1;
        end
        if (axi_r_valid_i) begin    // 从机数据读取完成
            case (r_addr_i[2:0])
            default: data_read_o <= 0;
            3'h1: data_read_o <= axi_r_data_i >> 8;
            3'h2: data_read_o <= axi_r_data_i >> 16;
            3'h3: data_read_o <= axi_r_data_i >> 24;
            3'h4: data_read_o <= axi_r_data_i >> 32;
            3'h5: data_read_o <= axi_r_data_i >> 40;
            3'h6: data_read_o <= axi_r_data_i >> 48;
            3'h7: data_read_o <= axi_r_data_i >> 56;
            3'h0: data_read_o <= axi_r_data_i;
            endcase
            // 告知缓存更新
            cache_update_en <= 1;
            if (cache_hit) begin
                $display("%x %x", cache_data, axi_r_data_i);
            end
            //$display("read.. %x", axi_r_data_i);
            r_state_read <= 0;
            r_data_valid <= 1;  // 告诉外部模块，数据已经读取完成
        end
        if (cache_update_en) begin
            cache_update_en <= 0;
        end
        if (r_data_valid && r_data_ready) begin
            r_data_valid <= 0;
        end
    end

    // ------------------Write Transaction------------------
    parameter AXI_SIZE      = $clog2(AXI_DATA_WIDTH / 8);
    wire [AXI_ID_WIDTH-1:0] axi_id              = {AXI_ID_WIDTH{1'b0}};
    wire [AXI_USER_WIDTH-1:0] axi_user          = {AXI_USER_WIDTH{1'b0}};
    wire [7:0] axi_len      =  8'b0 ;
    wire [2:0] axi_size     = AXI_SIZE[2:0];
    // 写地址通道  以下没有备注初始化信号的都可能是你需要产生和用到的
    assign axi_aw_valid_o   = w_state_addr;
    assign axi_aw_addr_o    = w_addr_i;
    assign axi_aw_prot_o    = `AXI_PROT_UNPRIVILEGED_ACCESS | `AXI_PROT_SECURE_ACCESS | `AXI_PROT_DATA_ACCESS;  //初始化信号即可
    assign axi_aw_id_o      = axi_id;                                                                           //初始化信号即可
    assign axi_aw_user_o    = axi_user;                                                                         //初始化信号即可
    assign axi_aw_len_o     = axi_len;
    assign axi_aw_size_o    = axi_size;
    assign axi_aw_burst_o   = `AXI_BURST_TYPE_INCR;                                                             
    assign axi_aw_lock_o    = 1'b0;                                                                             //初始化信号即可
    assign axi_aw_cache_o   = `AXI_AWCACHE_WRITE_BACK_READ_AND_WRITE_ALLOCATE;                                  //初始化信号即可
    assign axi_aw_qos_o     = 4'h0;                                                                             //初始化信号即可
    assign axi_aw_region_o  = 4'h0;                                                                             //初始化信号即可

    // 写数据通道
    assign axi_w_valid_o    = w_state_write;
    assign axi_w_data_o     = w_data_i ;
    assign axi_w_strb_o     = w_mask_i;
    assign axi_w_last_o     = 1'b1;
    assign axi_w_user_o     = axi_user;                                                                         //初始化信号即可

    // 写应答通道
    assign axi_b_ready_o    = w_state_resp;

    // ------------------Read Transaction------------------

    // Read address channel signals
    assign axi_ar_valid_o   = r_state_addr;
    assign axi_ar_addr_o    = r_addr_i;
    assign axi_ar_prot_o    = `AXI_PROT_UNPRIVILEGED_ACCESS | `AXI_PROT_SECURE_ACCESS | `AXI_PROT_DATA_ACCESS;  //初始化信号即可
    assign axi_ar_id_o      = axi_id;                                                                           //初始化信号即可                        
    assign axi_ar_user_o    = axi_user;                                                                         //初始化信号即可
    assign axi_ar_len_o     = axi_len;                                                                          
    assign axi_ar_size_o    = axi_size;
    assign axi_ar_burst_o   = `AXI_BURST_TYPE_INCR;
    assign axi_ar_lock_o    = 1'b0;                                                                             //初始化信号即可
    assign axi_ar_cache_o   = `AXI_ARCACHE_NORMAL_NON_CACHEABLE_NON_BUFFERABLE;                                 //初始化信号即可
    assign axi_ar_qos_o     = 4'h0;                                                                             //初始化信号即可

    // Read data channel signals
    assign axi_r_ready_o    = r_state_read;

endmodule