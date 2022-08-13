module ysyx_22041207_EX_ME(
    input clk,
    input bubble,
    input [63:0] aluRes,
    input memoryReadWen,
    input [3:0] readNum,
    input [63:0] pc,
    input [63:0] imm,
    input [2:0] wd_sel,
    input [63:0] rs2,
    input [7:0] memoryWriteMask,
    input sext,
    input writeRD,
    input [4:0] rwaddr,
    output reg [63:0] aluRes_o,
    output reg memoryReadWen_o,
    output reg [3:0] readNum_o,
    output reg [63:0] pc_o,
    output reg [63:0] imm_o,
    output reg [2:0] wd_sel_o,
    output reg [63:0] rs2_o,
    output reg [7:0] memoryWriteMask_o,
    output reg sext_o,
    output reg writeRD_o,
    output reg [4:0] rwaddr_o
);
always @(negedge clk) begin
    if (bubble) begin
        // aluRes_o <= aluRes_o;
        // memoryReadWen_o <= memoryReadWen_o;
        // readNum_o <= readNum_o;
        // pc_o <= pc_o;
        // imm_o <= imm_o;
        // wd_sel_o <= wd_sel_o;
        // rs2_o <= rs2_o;
        // memoryWriteMask_o <= memoryWriteMask_o;
        // sext_o <= sext_o;
        // writeRD_o <= writeRD_o;
        // rwaddr_o <= rwaddr_o;
        aluRes_o <= 0;
        memoryReadWen_o <= 0;
        readNum_o <= 0;
        pc_o <= 0;
        imm_o <= 0;
        wd_sel_o <= 0;
        rs2_o <= 0;
        memoryWriteMask_o <= 0;
        sext_o <= 0;
        writeRD_o <= 0;
        rwaddr_o <= 0;
    end
    else begin
        aluRes_o <= aluRes;
        memoryReadWen_o <= memoryReadWen;
        readNum_o <= readNum;
        pc_o <= pc;
        imm_o <= imm;
        wd_sel_o <= wd_sel;
        rs2_o <= rs2;
        memoryWriteMask_o <= memoryWriteMask;
        sext_o <= sext;
        writeRD_o <= writeRD;
        rwaddr_o <= rwaddr;
    end
    
end
endmodule