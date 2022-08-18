module ysyx_22041207_IF (
    input clk,
    input flush,
    input bubble,
    input me_jal,
    input me_jalr,
    input me_branch,
    input pc_panic,
    input [63:0] me_aluRes,
    input [63:0] csr_mtvec,
    input [63:0] me_pc,
    input [63:0] me_imm,
    input [63:0] me_r1data,
    output reg [31:0] inst_o,
    output reg [63:0] pc_o
);
wire [63:0] rawData;
wire [31:0] inst;
reg [63:0] pc;
initial begin
    pc = 64'h80000000 - 64'h4;
end
ysyx_22041207_read_mem readInst(pc, 1'b1, rawData);
assign inst = rawData [31:0];  // 这里可能有BUG
always @(negedge clk) begin
    if (bubble) begin

    end
    else begin
        inst_o <= inst;
        pc_o <= pc;
    end
    
    $display("npc:%x", pc);
end
wire [63:0] addRes;
assign addRes = me_r1data + me_imm;
always @(posedge clk) begin
        if (flush) begin
            $display("flush");
        end
        if (me_jal || (me_branch && me_aluRes == 0)) begin
            $display("catch jal.. %x %x", me_pc, me_pc + me_imm);
            pc <= me_pc + me_imm;
        end
        else if (me_jalr) begin // jalr要求最后一位置0
            //(ex_r1data + ex_imm)
            pc <= {addRes[63:1], 1'b0};
        end
        else if (pc_panic) begin
            $display("pc_panic %x", csr_mtvec);
            pc <= csr_mtvec;
        end 
        else if (~bubble) begin
            pc <= pc + 4;
        end
        else begin
            $display("bubble");
            pc <= pc;
        end
end
endmodule