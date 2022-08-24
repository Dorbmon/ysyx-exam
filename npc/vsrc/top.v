module ysyx_22041207_top (
  input clk,
  input rst,
  //input [31:0] inst,
  output reg [63:0] pc,

  // Advanced eXtensible Interface
  input                               axi_aw_ready_i,              
    output                              axi_aw_valid_o,
    output [63:0]         axi_aw_addr_o,
    output [2:0]                        axi_aw_prot_o,
    output [3:0]           axi_aw_id_o,
    output [0:0]         axi_aw_user_o,
    output [7:0]                        axi_aw_len_o,
    output [2:0]                        axi_aw_size_o,
    output [1:0]                        axi_aw_burst_o,
    output                              axi_aw_lock_o,
    output [3:0]                        axi_aw_cache_o,
    output [3:0]                        axi_aw_qos_o,
    output [3:0]                        axi_aw_region_o,

    input                               axi_w_ready_i,                
    output                              axi_w_valid_o,
    output [63:0]         axi_w_data_o,
    output [7:0]       axi_w_strb_o,
    output                              axi_w_last_o,
    output [0:0]         axi_w_user_o,
    
    output                              axi_b_ready_o,                
    input                               axi_b_valid_i,
    input  [1:0]                        axi_b_resp_i,                 
    input  [3:0]           axi_b_id_i,
    input  [0:0]         axi_b_user_i,

    input                               axi_ar_ready_i,                
    output                              axi_ar_valid_o,
    output [63:0]         axi_ar_addr_o,
    output [2:0]                        axi_ar_prot_o,
    output [3:0]           axi_ar_id_o,
    output [0:0]         axi_ar_user_o,
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
    input  [63:0]         axi_r_data_i,
    input                               axi_r_last_i,
    input  [3:0]           axi_r_id_i,
    input  [0:0]         axi_r_user_i
);
wire flush;
wire [31:0] if_inst, id_inst;
wire [63:0] if_pc, id_pc;
wire clear_afterID;
assign clear_afterID = id_csrOrder != 0 && ~id_afterIDClear;  // 是否需要等待id之后的流水级清空
// if 的 axi 读信号
wire if_r_valid_i, if_r_ready_o;
wire [63:0] if_data_read_o;
wire [63:0] if_r_addr_i;
wire [7:0] if_r_size_i;
wire if_data_valid, if_data_ready;
ysyx_22041207_IF rxIF(clk, bubble | clear_afterID, me_jal, me_jalr, me_dbranch, ex_pc_panic, me_aluRes, csr_mtvec, me_pc, me_imm, me_r1data, if_inst, if_pc, if_r_valid_i, if_r_ready_o, if_data_read_o, if_r_addr_i, if_r_size_i, if_data_valid, if_data_ready);
ysyx_22041207_if_id rx_if_id(clk, flush, bubble | clear_afterID, if_inst, if_pc, id_inst, id_pc);
// axi 读信号
wire rx_r_valid_i, rx_r_ready_o;
wire [63:0] rx_data_read_o;
wire [63:0] rx_r_addr_i;
wire [7:0] rx_r_size_i;
wire rx_data_valid, rx_data_ready;
// axi 写信号
wire rx_w_valid_i, rx_w_ready_o;
wire [63:0] rx_data_write_i;
wire [63:0] rx_w_addr_i;
wire [7:0] rx_w_mask_i;
wire rx_w_ready_i, rx_w_valid_o;

ysyx_22041207_axi_switch rx_axi_switch (clk, 
mem_r_valid_i, mem_r_ready_o, mem_data_read_o, mem_r_addr_i, mem_r_size_i, mem_data_valid, mem_data_ready,
if_r_valid_i, if_r_ready_o, if_data_read_o, if_r_addr_i, if_r_size_i, if_data_valid, if_data_ready,
rx_r_valid_i, rx_r_ready_o, rx_data_read_o, rx_r_addr_i, rx_r_size_i, rx_data_valid, rx_data_ready
);
axi_rw rx_axi(clk, rst, rx_r_valid_i, rx_r_ready_o, rx_data_read_o, rx_r_addr_i, rx_r_size_i, rx_data_valid, rx_data_ready,
rx_w_valid_i, rx_w_ready_o, rx_data_write_i, rx_w_addr_i, rx_w_mask_i, rx_w_valid_o, rx_w_ready_i, 
 axi_aw_ready_i,axi_aw_valid_o,axi_aw_addr_o,axi_aw_prot_o,axi_aw_id_o,axi_aw_user_o,axi_aw_len_o,axi_aw_size_o,axi_aw_burst_o,axi_aw_lock_o,axi_aw_cache_o,axi_aw_qos_o,axi_aw_region_o,
axi_w_ready_i,axi_w_valid_o,axi_w_data_o,axi_w_strb_o,axi_w_last_o,axi_w_user_o,axi_b_ready_o,axi_b_valid_i,axi_b_resp_i,axi_b_id_i,axi_b_user_i,
axi_ar_ready_i,axi_ar_valid_o,axi_ar_addr_o,axi_ar_prot_o,axi_ar_id_o,axi_ar_user_o,axi_ar_len_o,axi_ar_size_o,axi_ar_burst_o,axi_ar_lock_o,axi_ar_cache_o,axi_ar_qos_o,axi_ar_region_o,axi_r_ready_o,axi_r_valid_i,axi_r_resp_i,axi_r_data_i,axi_r_last_i,axi_r_id_i,axi_r_user_i);
/*  id 导线  */
wire  bubble;
wire [4:0] id_aluOperate;
wire [1:0] id_sel_a, id_sel_b;
wire [7:0] id_memoryWriteMask;
wire id_writeRD;
wire id_pc_sel;
wire id_jalr, id_jal;
wire[2:0] id_writeBackDataSelect;
wire id_memoryReadWen;
wire id_sext;
wire [3:0] id_readNum;
wire id_rs1to32, id_wMtvec, id_wMepc, id_wMcause, id_wMstatus, id_pc_panic, id_pc_mret, id_csrWen, id_dbranch;
wire [63:0] id_imm, id_mcause_o;
wire [4:0] id_r1addr, id_r2addr, id_rwaddr;
wire [2:0] id_csrOrder;
wire id_afterIDClear; // ID后的部分是否清空
assign id_afterIDClear = (ex_pc == 0 && me_pc == 0 && wb_pc == 0);
ysyx_22041207_decoder decoder(clk, id_inst, id_aluOperate, id_sel_a, id_sel_b, id_memoryWriteMask, 
id_writeRD, id_pc_sel, id_jalr, id_jal, id_writeBackDataSelect, id_memoryReadWen, id_sext, id_readNum, id_rs1to32, id_wMtvec,
 id_wMepc, id_wMcause, id_mcause_o, id_wMstatus, id_pc_panic, id_pc_mret, id_csrWen, id_dbranch, id_imm, id_r1addr, id_r2addr, id_rwaddr, id_csrOrder);
/*  ex 导线  */
wire [4:0] ex_aluOperate;
wire [1:0] ex_sel_a, ex_sel_b;
wire [7:0] ex_memoryWriteMask;
wire ex_writeRD;
wire ex_pc_sel;
wire ex_jalr, ex_jal;
wire[2:0] ex_writeBackDataSelect;
wire ex_memoryReadWen;
wire ex_sext;
wire [3:0] ex_readNum;
wire ex_rs1to32, ex_wMtvec, ex_wMepc, ex_wMcause, ex_wMstatus, ex_pc_panic, ex_pc_mret, ex_csrWen, ex_dbranch;
wire [63:0] ex_imm;
wire [4:0] ex_r1addr, ex_r2addr, ex_rwaddr;
wire [63:0] ex_r1data, ex_r2data;
wire [63:0] ex_pc, ex_mcause;
wire [2:0] ex_csrOrder;
ysyx_22041207_ID_EX rxID_EX(clk, bubble, flush, clear_afterID, id_aluOperate, id_sel_a, id_sel_b, id_memoryWriteMask, 
id_writeRD, id_pc_sel, id_jalr, id_jal,  id_writeBackDataSelect, id_memoryReadWen, id_sext, id_readNum, id_rs1to32, id_wMtvec, id_wMepc,
 id_wMcause, id_wMstatus, id_pc_panic, id_pc_mret, id_csrWen, id_dbranch, id_imm, id_r1addr, id_r2addr, id_rwaddr, id_pc, id_csrOrder,id_mcause_o,
 ex_aluOperate, ex_sel_a, ex_sel_b, ex_memoryWriteMask, 
ex_writeRD, ex_pc_sel, ex_jalr, ex_jal,  ex_writeBackDataSelect, ex_memoryReadWen, ex_sext, ex_readNum, ex_rs1to32, ex_wMtvec,
 ex_wMepc, ex_wMcause, ex_wMstatus, ex_pc_panic, ex_pc_mret, ex_csrWen, ex_dbranch, ex_imm, ex_r1addr, ex_r2addr, ex_rwaddr, ex_pc, ex_csrOrder,ex_mcause
 );
wire [63:0] ex_aluRes;
wire [63:0] ex_forward_rs1, ex_forward_rs2;
ysyx_22041207_dataforward data_forward(ex_r1addr, ex_r2addr, ex_r1data, ex_r2data, me_writeRD, me_rwaddr, me_writeBackData,
 wb_writeRD, wb_rwaddr, wb_writeBackData, ex_forward_rs1, ex_forward_rs2
);
wire ex_csrWen;
ysyx_22041207_csrOrder rex_csrOrder(clk, ex_csrOrder);

ysyx_22041207_alu ex_alu(
    clk,
    ex_pc,
    ex_aluOperate,
    ex_forward_rs1,
    ex_forward_rs2,
    ex_csr_readData,
    ex_imm,
    ex_sel_a,
    ex_sel_b,
    ex_rs1to32,  // rs1 转换为32bit
    ex_aluRes
);
// bubble决定下次是否需要重新计算
ysyx_22041207_Bubble rx_bubble (clk, ex_r1addr, ex_r2addr, me_rwaddr, me_readNum, me_wait_for_axi, bubble);
wire [63:0] me_csrValue;
wire [63:0] me_writeBackData;
ysyx_22041207_WB me_builtin_wb(me_aluRes, me_pc, me_memoryReadData, me_imm, me_csrValue, me_writeBackDataSelect, me_writeBackData);
wire [63:0] me_aluRes;
wire me_memoryReadWen, me_sext, me_writeRD;
wire [3:0] me_readNum;
wire [63:0] me_pc;
wire [63:0] me_imm, me_r1data, me_r2data;
wire [2:0] me_writeBackDataSelect;
wire [7:0] me_memoryWriteMask;
wire [63:0] me_memoryReadData;
wire [4:0] me_rwaddr;
ysyx_22041207_EX_ME rxEX_ME(clk, 
    flush,
    bubble,
    ex_aluRes,
    ex_memoryReadWen,
    ex_readNum,
    ex_pc,
    ex_imm,
    ex_writeBackDataSelect,
    ex_forward_rs1,
    ex_forward_rs2,
    ex_memoryWriteMask,
    ex_sext,
    ex_writeRD,
    ex_rwaddr,
    ex_jal,
    ex_jalr,
    ex_dbranch,
    ex_csrWen,
    me_aluRes,
    me_memoryReadWen,
    me_readNum,
    me_pc,
    me_imm,
    me_writeBackDataSelect,
    me_r1data,
    me_r2data,
    me_memoryWriteMask,
    me_sext,
    me_writeRD,
    me_rwaddr,
    me_jal,
    me_jalr,
    me_dbranch,
    me_csrWen
);
wire me_jal, me_jalr, me_dbranch, me_csrWen;
wire [4:0] wb_rwaddr;
ysyx_22041207_flush rx_flush (clk, me_jal, me_jalr, ex_pc_panic, me_dbranch, me_aluRes, flush);
wire me_wait_for_axi;
// mem的axi读信号
wire mem_r_valid_i, mem_r_ready_o;
wire [63:0] mem_data_read_o;
wire [63:0] mem_r_addr_i;
wire [7:0] mem_r_size_i;
wire mem_data_valid, mem_data_ready;

ysyx_22041207_Memory mem(clk, me_memoryReadWen, me_aluRes, me_r2data, me_memoryWriteMask, me_sext, me_readNum, me_memoryReadData,
// axi接口
rx_w_valid_i, rx_w_ready_o, rx_data_write_i, rx_w_addr_i, rx_w_mask_i, rx_w_valid_o, rx_w_ready_i,
mem_r_valid_i, mem_r_ready_o, mem_data_read_o, mem_r_addr_i, mem_r_size_i, mem_data_valid, mem_data_ready,
me_wait_for_axi
);
ysyx_22041207_ME_WB me_wb(clk,
 me_aluRes   ,me_pc      ,me_memoryReadData ,me_imm     ,//csrValue,
 0, me_writeBackDataSelect  , me_writeRD , me_rwaddr, me_csrWen, me_wait_for_axi,
wb_aluRes   , wb_pc      , wb_memoryReadData , wb_imm     ,
wb_csrValue,
 wb_writeBackDataSelect  ,wb_writeRD , wb_rwaddr, wb_csrWen
);
wire [63:0] wb_csrValue;
wire [63:0] wb_writeBackData, wb_aluRes, wb_pc, wb_memoryReadData, wb_imm;
ysyx_22041207_WB wb(wb_aluRes, wb_pc, wb_memoryReadData, wb_imm, wb_csrValue, wb_writeBackDataSelect, wb_writeBackData);
wire [2:0] wb_writeBackDataSelect;
wire wb_writeRD;
wire wb_csrWen;
wire [11:0] wb_csrWriteAddress;
wire [63:0] csr_mcause, csr_mtvec, csr_mepc, csr_mcause, csr_mstatus, ex_csr_readData;
ysyx_22041207_RegisterFile #(32, 5, 64) r(clk, wb_writeBackData, wb_rwaddr, ex_r1addr, ex_r1data, ex_r2addr, ex_r2data, wb_writeRD);
ysyx_22041207_csrRegister csrRegister(clk, ex_pc_mret, wb_csrWen, ex_pc_panic, ex_imm[11:0], wb_imm[11:0], wb_aluRes, ex_wMepc, ex_pc, ex_wMcause, ex_mcause, csr_mtvec, csr_mepc, csr_mcause, csr_mstatus, ex_csr_readData);
endmodule

