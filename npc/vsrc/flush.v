module ysyx_22041207_flush (
    input clk,
    input me_jal,
    input me_jalr,
    input me_branch,
    input [63:0] me_aluRes,
    output reg flush
);
always @(posedge clk) begin
    // 下一个周期需要冲刷掉中间的全部指令
    flush = me_jal || me_jalr || (me_branch && me_aluRes == 0);
    if (flush) begin
        $display("flush = %d", flush);
    end
end
endmodule