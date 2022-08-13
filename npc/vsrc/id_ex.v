module ysyx_22041207_ID_EX (
    input clk,
    input bubble,
    input flush,
    input  [4:0] aluOperate,
    input  [1:0] sel_a,
    input  [1:0] sel_b,
    input  [7:0] memoryWriteMask,
    input  writeRD,
    input  pc_sel,
    input  jalr,
    input  jal,
    input  [2:0] writeBackDataSelect,
    input  memoryReadWen,
    input  sext,
    input  [3:0] readNum,
    input  rs1to32,
    input  wMtvec,
    input  wMepc,
    input  wMcause,
    input  wMstatus,
    input  pc_panic, // 是否为异常跳转
    input  pc_mret,   // 是否为mret
    input  csrWen,
    input  brach,
    input  [63:0] imm,
    input  [4:0] rs1addr,
    input  [4:0] rs2addr,
    input  [4:0] rwaddr,
    input  [63:0] pc,
    output reg  [4:0] aluOperate_o,
    output reg  [1:0] sel_a_o,
    output reg  [1:0] sel_b_o,
    output reg  [7:0] memoryWriteMask_o,
    output reg  writeRD_o,
    output reg  pc_sel_o,
    output reg  jalr_o,
    output reg  jal_o,
    output reg  [2:0] writeBackDataSelect_o,
    output reg  memoryReadWen_o,
    output reg  sext_o,
    output reg  [3:0] readNum_o,
    output reg  rs1to32_o,
    output reg  wMtvec_o,
    output reg  wMepc_o,
    output reg  wMcause_o,
    output reg  wMstatus_o,
    output reg  pc_panic_o, // 是否为异常跳转
    output reg  pc_mret_o,   // 是否为mret
    output reg  csrWen_o,
    output reg  brach_o,
    output reg  [63:0] imm_o,
    output reg  [4:0] rs1addr_o,
    output reg  [4:0] rs2addr_o,
    output reg  [4:0] rwaddr_o,
    output reg  [63:0] pc_o
);
always @(negedge clk) begin
    if (bubble || flush) begin
        $display("5666");
        aluOperate_o <= 0;
        sel_a_o <= 0;
        sel_b_o <= 0;
        memoryWriteMask_o <= 0;
        writeRD_o <= 0;
        pc_sel_o <= 0;
        jalr_o <= 0;
        jal_o <= 0;
        writeBackDataSelect_o <= 0;
        memoryReadWen_o <= 0;
        sext_o <= 0;
        readNum_o <= 0;
        rs1to32_o <= 0;
        wMtvec_o <= 0;
        wMepc_o <= 0;
        wMcause_o <= 0;
        wMstatus_o <= 0;
        pc_panic_o <= 0; // 是否为异常跳转
        pc_mret_o <= 0;   // 是否为mret
        csrWen_o <= 0;
        brach_o <= 0;
        imm_o <= 0;
        rs1addr_o <= 0;
        rs2addr_o <= 0;
        rwaddr_o <= 0;
        pc_o <= 0;
    end
    else begin
        aluOperate_o <= aluOperate;
        sel_a_o <= sel_a;
        sel_b_o <= sel_b;
        memoryWriteMask_o <= memoryWriteMask;
        writeRD_o <= writeRD;
        pc_sel_o <= pc_sel;
        jalr_o <= jalr;
        jal_o <= jal;
        writeBackDataSelect_o <= writeBackDataSelect;
        memoryReadWen_o <= memoryReadWen;
        sext_o <= sext;
        readNum_o <= readNum;
        rs1to32_o <= rs1to32;
        wMtvec_o <= wMtvec;
        wMepc_o <= wMepc;
        wMcause_o <= wMcause;
        wMstatus_o <= wMstatus;
        pc_panic_o <= pc_panic; // 是否为异常跳转
        pc_mret_o <= pc_mret;   // 是否为mret
        csrWen_o <= csrWen;
        brach_o <= brach;
        imm_o <= imm;
        rs1addr_o <= rs1addr;
        rs2addr_o <= rs2addr;
        rwaddr_o <= rwaddr;
        pc_o <= pc;
    end
end
endmodule