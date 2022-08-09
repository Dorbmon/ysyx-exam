module ysyx_22041207_stageManager (
    input clk,
    output reg [2:0] currentStage
);
always @(posedge clk) begin
    currentStage <= (currentStage + 1) % 3'h5;  // 总共五个阶段
end
endmodule