module ysyx_22041207_mul (
    input clk,
    input rst,
    input mul_valid,
    input flush,
    //input [1:0] mul_signed,
    input [63:0] multiplicand,  // 被乘数
    input [63:0] multiplier,    // 乘数
    output reg mul_ready,
    output reg out_valid,
    output [31:0] result_hi,
    output [31:0] result_lo
);
reg mul_busy;
initial begin
    mul_busy = 0;
    mul_res = 0;
    mul_ready = 1;
end
reg [63:0] l_multiplicand, l_multiplier;
reg [63:0] mul_res;
reg positive;   // 乘数是否为正数
reg [5:0] count;
assign result_hi = mul_res [63:32];
assign result_lo = mul_res [31:0];
always @(negedge clk) begin   // 重置数据
end
always @(posedge clk) begin
    if (rst) begin
        mul_busy <= 0;
        mul_res <= 0;
        count <= 0;
        mul_ready <= 1;
    end else begin
        if (mul_valid && (~mul_busy || flush)) begin
            mul_busy <= 1;
            l_multiplicand <= multiplicand;
            l_multiplier <= multiplier;
            positive <= multiplier [63];
            count <= 0;
            mul_ready <= 0;
        end
        if (~flush && mul_busy && count != 6'h1F) begin   // 如果已经进行了31次，那最后一次就要根据符号判断如何计算
            mul_res <= mul_res + ((l_multiplier[0]) ? l_multiplicand : 0);
            l_multiplicand <= l_multiplicand << 1;
            l_multiplier <= l_multiplier >> 1;
            count <= count + 1;
        end
        if (~flush && mul_busy && count == 6'h1F) begin
            if (positive) begin
                mul_res <= mul_res + ((l_multiplier[0]) ? l_multiplicand : 0);
            end else begin
                mul_res <= $signed(mul_res) - ((l_multiplier[0]) ? $signed(l_multiplicand) : 0);
            end
            count <= count + 1;
            out_valid <= 1;
        end
        if (out_valid) begin
            out_valid <= 0;
            mul_busy <= 0;
            mul_ready <= 1;
        end
    end
end
endmodule