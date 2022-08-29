module ysyx_22041207_mul (
    input clk,
    input rst,
    input mul_valid,
    input flush,
    input [63:0] multiplicand,  // 被乘数
    input [63:0] multiplier,    // 乘数
    output reg mul_ready,
    output reg out_valid,
    output reg [63:0] mul_res_o
);
initial begin
    mul_res = 0;
    mul_ready = 1;
    out_valid = 0;
    count = 0;
end
reg [63:0] l_multiplicand, l_multiplier;
reg [63:0] mul_res;
reg [7:0] count;
wire op1sign, op2sign;
always @(posedge clk) begin
    if (rst) begin
        mul_res <= 0;
        count <= 0;
        mul_ready <= 1;
        out_valid <= 0;
    end else begin
        if (mul_valid && (mul_ready || flush)) begin
            //$display("mul %x %x", multiplicand, multiplier);
            l_multiplicand <= multiplicand;
            l_multiplier <= multiplier;
            count <= 0;
            mul_ready <= 0;
            mul_res <= 0;
        end
        if (~flush && ~mul_ready && count != 8'h40) begin
            mul_res <= mul_res + ((l_multiplier[0]) ? l_multiplicand : 0);
            l_multiplicand <= l_multiplicand << 1;
            l_multiplier <= l_multiplier >> 1;
            count <= count + 1;
        end
        if (~flush && ~mul_ready && count == 8'h40 && ~out_valid) begin
            //mul_res <= mul_res + ((l_multiplier[0]) ? l_multiplicand : 0);
            //mul_res <= multiplicand * multiplier;
            //$display("mul %x %x %x", multiplicand, multiplier, mul_res);
            out_valid <= 1;
            count <= 0;
            mul_res_o <= mul_res;
        end
        if (out_valid) begin
            mul_ready <= 1;
            out_valid <= 0;
        end
    end
end
endmodule