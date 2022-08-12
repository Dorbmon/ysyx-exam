module ysyx_22041207_Ex(
    input clk,
    input  [4:0] aluOperate,
    input  [1:0] sel_a,
    input  [1:0] sel_b,
    input  [7:0] memoryWriteMask,
    input  writeRD,
    input  pc_sel,
    input  jalr,
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
    input  [63:0] pc,
    input  [63:0] rs1,
    input  [63:0] rs2,
    output [63:0] aluRes
);
ysyx_22041207_alu alu(
    pc,
    aluOperate,
    rs1,
    rs2,
    csr,
    imm,
    sel_a,
    sel_b,
    rs1to32,
    aluRes
);
endmodule