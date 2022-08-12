module ysyx_22041207_IF (
    input clk,
    input pc_delay,
    input ex_jal,
    input ex_jalr,
    input ex_branch,
    input [63:0] ex_aluRes,
    input [63:0] ex_pc,
    input [63:0] ex_imm,
    input [63:0] ex_r1data,
    output reg [31:0] inst_o,
    output reg [63:0] pc_o
);
wire [63:0] rawData;
wire [31:0] inst;
reg [63:0] pc;
initial begin
    pc = 64'h80000000;
end
ysyx_22041207_read_mem readInst(pc, 1'b1, rawData);
assign inst = rawData [31:0];  // 这里可能有BUG
always @(posedge clk) begin
    // 开始读入指令，并更新PC
    if (~pc_delay) begin
        if (ex_jal || (ex_branch && ex_aluRes == 0)) begin
            pc = ex_pc + ex_imm;
        end
        else if (ex_jalr) begin
            pc = ex_r1data + ex_imm;
        end
        else begin
            pc = pc + 4;
        end
    end
    $display("read inst:%x %d", ex_pc, ex_jal);
    inst_o = rawData[31:0];
    pc_o = pc;
    
end
endmodule