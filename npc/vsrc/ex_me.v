module ysyx_22041207_EX_ME(
    input clk,
    input flush,
    input bubble,
    input [63:0] aluRes,
    input memoryReadWen,
    input [3:0] readNum,
    input [63:0] pc,
    input [63:0] imm,
    input [2:0] wd_sel,
    input [63:0] rs1,
    input [63:0] rs2,
    input [7:0] memoryWriteMask,
    input sext,
    input writeRD,
    input [4:0] rwaddr,
    input jal,
    input jalr,
    input branch,
    input csrWen,
    output reg [63:0] aluRes_o,
    output reg memoryReadWen_o,
    output reg [3:0] readNum_o,
    output reg [63:0] pc_o,
    output reg [63:0] imm_o,
    output reg [2:0] wd_sel_o,
    output reg [63:0] rs1_o,
    output reg [63:0] rs2_o,
    output reg [7:0] memoryWriteMask_o,
    output reg sext_o,
    output reg writeRD_o,
    output reg [4:0] rwaddr_o,
    output reg jal_o,
    output reg jalr_o,
    output reg branch_o,
    output reg csrWen_o
);
always @(negedge clk) begin
    if (bubble || flush) begin
        $display("hhh");
        aluRes_o <= 0;
        memoryReadWen_o <= 0;
        readNum_o <= 0;
        pc_o <= 0;
        imm_o <= 0;
        wd_sel_o <= 0;
        rs1_o <= 0;
        rs2_o <= 0;
        memoryWriteMask_o <= 0;
        sext_o <= 0;
        writeRD_o <= 0;
        rwaddr_o <= 0;
        jal_o <= 0;
        jalr_o <= 0;
        branch_o <= 0;
        csrWen_o <= 0;
    end
    else begin
        aluRes_o <= aluRes;
        memoryReadWen_o <= memoryReadWen;
        readNum_o <= readNum;
        pc_o <= pc;
        imm_o <= imm;
        wd_sel_o <= wd_sel;
        rs1_o <= rs1;
        rs2_o <= rs2;
        memoryWriteMask_o <= memoryWriteMask;
        sext_o <= sext;
        writeRD_o <= writeRD;
        rwaddr_o <= rwaddr;
        jal_o <= jal;
        jalr_o <= jalr;
        branch_o <= branch;
        csrWen_o <= csrWen;
    end
    
end
endmodule