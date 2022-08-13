module ysyx_22041207_ME_WB (
    input clk,
    input   [63:0]  alu_c   ,
    input   [63:0]  pc      ,
    input   [63:0]  ramdout ,
    input   [63:0]  imm     ,
    input   [63:0]  csrValue,
    input   [ 2:0]  wd_sel  ,
    input           writeRD ,
    input   [4:0]   rwddr   ,
    input ebreak,
    output reg  [63:0]  alu_c_o   ,
    output reg  [63:0]  pc_o      ,
    output reg  [63:0]  ramdout_o ,
    output reg  [63:0]  imm_o     ,
    output reg  [63:0]  csrValue_o,
    output reg  [ 2:0]  wd_sel_o  ,
    output reg           writeRD_o,
    output reg   [4:0]   rwddr_o,
    output reg ebreak_o
);
always @(negedge clk) begin
    alu_c_o   <= alu_c;
    pc_o      <= pc;
    ramdout_o <= ramdout;
    imm_o     <= imm;
    csrValue_o<= csrValue;
    wd_sel_o  <= wd_sel;
    writeRD_o <= writeRD;
    rwddr_o <= rwddr;
    ebreak_o <= ebreak;
end
endmodule