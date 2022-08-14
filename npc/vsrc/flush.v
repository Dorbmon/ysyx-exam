module ysyx_22041207_flush (
    input clk,
    input ex_jal,
    input ex_jalr,
    input ex_branch,
    input [63:0] ex_aluRes,
    output reg flush
);
always @(posedge clk) begin
    // 下一个周期需要冲刷掉中间的全部指令
    flush <= ex_jal || ex_jalr || (ex_branch && ex_aluRes == 0);
end
endmodule