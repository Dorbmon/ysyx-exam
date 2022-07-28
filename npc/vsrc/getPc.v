module ysyx_22041207_GetPC(
    input   [63:0]  imm     ,//符号扩展结果
    input   [63:0]  rs1     ,//寄存器的第一输出
    input           pc_sel  ,//是否跳转
    input           npc_op  ,//是否有操作
    input   [63:0]  pc      ,
    output  [63:0]  npc
    );
    assign npc = npc_op ? (pc_sel ? rs1 + imm : pc + imm) : pc + 4;
endmodule