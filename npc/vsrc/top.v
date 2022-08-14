module ysyx_22041207_top (
  input clk,
  //input [31:0] inst,
  output reg [63:0] pc
);
wire flush;
wire [31:0] if_inst, id_inst;
wire [63:0] if_pc, id_pc;
wire clear_afterID;
assign clear_afterID = id_csrOrder != 0 && ~id_afterIDClear;  // 是否需要等待id之后的流水级清空
ysyx_22041207_IF rxIF(clk, pc_delay | clear_afterID, me_jal, me_jalr, me_dbranch, me_aluRes, me_pc, me_imm, ex_r1data, if_inst, if_pc);
ysyx_22041207_if_id rxIF_ID(clk, bubble | clear_afterID, flush, if_inst, if_pc, id_inst, id_pc);
/*  id 导线  */
wire pc_delay, bubble;
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
wire [63:0] id_imm;
wire [4:0] id_r1addr, id_r2addr, id_rwaddr;
wire [2:0] id_csrOrder;
wire id_afterIDClear; // ID后的部分是否清空
assign id_afterIDClear = (ex_pc == 0 && me_pc == 0 && wb_pc == 0);
ysyx_22041207_decoder decoder(clk, id_inst, id_aluOperate, id_sel_a, id_sel_b, id_memoryWriteMask, 
id_writeRD, id_pc_sel, id_jalr, id_jal, id_writeBackDataSelect, id_memoryReadWen, id_sext, id_readNum, id_rs1to32, id_wMtvec,
 id_wMepc, id_wMcause, id_wMstatus, id_pc_panic, id_pc_mret, id_csrWen, id_dbranch, id_imm, id_r1addr, id_r2addr, id_rwaddr, id_csrOrder);
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
wire [63:0] ex_pc;
wire [2:0] ex_csrOrder;
ysyx_22041207_ID_EX rxID_EX(clk, bubble, flush, clear_afterID, id_aluOperate, id_sel_a, id_sel_b, id_memoryWriteMask, 
id_writeRD, id_pc_sel, id_jalr, id_jal,  id_writeBackDataSelect, id_memoryReadWen, id_sext, id_readNum, id_rs1to32, id_wMtvec, id_wMepc,
 id_wMcause, id_wMstatus, id_pc_panic, id_pc_mret, id_csrWen, id_dbranch, id_imm, id_r1addr, id_r2addr, id_rwaddr, id_pc, id_csrOrder, 
 ex_aluOperate, ex_sel_a, ex_sel_b, ex_memoryWriteMask, 
ex_writeRD, ex_pc_sel, ex_jalr, ex_jal,  ex_writeBackDataSelect, ex_memoryReadWen, ex_sext, ex_readNum, ex_rs1to32, ex_wMtvec,
 ex_wMepc, ex_wMcause, ex_wMstatus, ex_pc_panic, ex_pc_mret, ex_csrWen, ex_dbranch, ex_imm, ex_r1addr, ex_r2addr, ex_rwaddr, ex_pc, ex_csrOrder
 );
wire [63:0] ex_aluRes;
wire [63:0] ex_forward_rs1, ex_forward_rs2;
ysyx_22041207_dataforward data_forward(ex_r1addr, ex_r2addr, ex_r1data, ex_r2data, me_writeRD, me_rwaddr, me_writeBackData,
 wb_writeRD, wb_rwaddr, wb_writeBackData, ex_forward_rs1, ex_forward_rs2
);
ysyx_22041207_csrOrder rex_csrOrder(clk, ex_csrOrder);
ysyx_22041207_alu ex_alu(
    clk,
    ex_pc,
    ex_aluOperate,
    ex_forward_rs1,
    ex_forward_rs2,
    //csrReadData,
    0,
    ex_imm,
    ex_sel_a,
    ex_sel_b,
    ex_rs1to32,  // rs1 转换为32bit
    ex_aluRes
);

ysyx_22041207_Bubble rx_bubble (clk, ex_r1addr, ex_r2addr, me_rwaddr, me_readNum, pc_delay, bubble);
wire [63:0] me_csrValue;
wire [63:0] me_writeBackData;
ysyx_22041207_WB me_builtin_wb(me_aluRes, me_pc, me_memoryReadData, me_imm, me_csrValue, me_writeBackDataSelect, me_writeBackData);
wire [63:0] me_aluRes;
wire me_memoryReadWen, me_sext, me_writeRD;
wire [3:0] me_readNum;
wire [63:0] me_pc;
wire [63:0] me_imm, me_r2data;
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
    ex_r2data,
    ex_memoryWriteMask,
    ex_sext,
    ex_writeRD,
    ex_rwaddr,
    ex_jal,
    ex_jalr,
    ex_dbranch,
    me_aluRes,
    me_memoryReadWen,
    me_readNum,
    me_pc,
    me_imm,
    me_writeBackDataSelect,
    me_r2data,
    me_memoryWriteMask,
    me_sext,
    me_writeRD,
    me_rwaddr,
    me_jal,
    me_jalr,
    me_dbranch
);
wire me_jal, me_jalr, me_dbranch;
wire [4:0] wb_rwaddr;
ysyx_22041207_flush rx_flush (me_jal, me_jalr, me_dbranch, me_aluRes, flush);
ysyx_22041207_Memory mem(clk, me_memoryReadWen, me_aluRes, me_r2data, me_memoryWriteMask, me_sext, me_readNum, me_memoryReadData);
ysyx_22041207_ME_WB me_wb(clk, me_aluRes   ,me_pc      ,me_memoryReadData ,me_imm     ,//csrValue,
 0, me_writeBackDataSelect  , me_writeRD , me_rwaddr,
wb_aluRes   , wb_pc      , wb_memoryReadData , wb_imm     ,
wb_csrValue,
 wb_writeBackDataSelect  ,wb_writeRD , wb_rwaddr
);
wire [63:0] wb_csrValue;
wire [63:0] wb_writeBackData, wb_aluRes, wb_pc, wb_memoryReadData, wb_imm;
ysyx_22041207_WB wb(wb_aluRes, wb_pc, wb_memoryReadData, wb_imm, wb_csrValue, wb_writeBackDataSelect, wb_writeBackData);
wire [2:0] wb_writeBackDataSelect;
wire wb_writeRD;
ysyx_22041207_RegisterFile #(32, 5, 64) r(clk, wb_writeBackData, wb_rwaddr, ex_r1addr, ex_r1data, ex_r2addr, ex_r2data, wb_writeRD);
endmodule

