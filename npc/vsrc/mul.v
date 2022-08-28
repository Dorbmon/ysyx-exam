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
initial begin
    mul_res = 0;
    mul_ready = 1;
end
reg [63:0] l_multiplicand, l_multiplier;
reg [63:0] mul_res;
reg [6:0] count;
wire op1sign, op2sign;
assign result_hi = mul_res [63:32];
assign result_lo = mul_res [31:0];
always @(negedge clk) begin   // 重置数据
end
always @(posedge clk) begin
    if (rst) begin
        mul_res <= 0;
        count <= 0;
        mul_ready <= 1;
    end else begin
        if (mul_valid && (mul_ready || flush)) begin
            $display("mul %x %x", multiplicand, multiplier);
            l_multiplicand <= multiplicand;
            l_multiplier <= multiplier;
            count <= 0;
            mul_ready <= 0;
            mul_res <= 0;
        end
        if (~flush && ~mul_ready && count != 7'h3E) begin
            mul_res <= mul_res + ((l_multiplier[0]) ? l_multiplicand : 0);
            l_multiplicand <= l_multiplicand << 1;
            l_multiplier <= l_multiplier >> 1;
            count <= count + 1;
        end
        if (~flush && ~mul_ready && count == 7'h3E && ~out_valid) begin
            mul_res <= mul_res + ((l_multiplier[0]) ? l_multiplicand : 0);
            //$display("mul %x %x %x", multiplicand, multiplier, mul_res + ((l_multiplier[0]) ? l_multiplicand : 0));
            out_valid <= 1;
        end
        if (out_valid) begin
            out_valid <= 0;
            mul_ready <= 1;
        end
    end
end
endmodule