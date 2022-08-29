module ysyx_22041207_div (
    input clk,
    input rst,
    input div_valid,
    input flush,
    input [63:0] dividend,  // 被除数
    input [63:0] divisor,    // 除s数
    input sign_div,
    output reg div_ready,
    output reg out_valid,
    output reg [63:0] div_res_o,
    output reg [63:0] remain_o
);
initial begin
    div_ready = 1;
    out_valid = 0;
    count = 0;
end
reg [127:0] l_dividend, l_divisor;
reg [7:0] count;
wire op1sign, op2sign;
reg sign;
wire [63:0] div_res = l_dividend[63:0];
wire [63:0] remain = l_dividend[127:64];
always @(posedge clk) begin
    if (rst) begin
        count <= 0;
        div_ready <= 1;
        out_valid <= 0;
    end else begin
        if (div_valid && (div_ready || flush)) begin
            //$display("div %x %x", divtiplicand, divtiplier);
            sign <= (dividend[63] != divisor[63]);
            l_dividend <= {64'b0, (dividend[63]&&sign_div)?(~dividend + 1):dividend};
            l_divisor <= {(divisor[63]&&sign_div)?(~divisor + 1):divisor, 64'b0};
            count <= 0;
            div_ready <= 0;
        end
        if (~flush && ~div_ready && count != 8'h40) begin
           //div_res <= div_res + 
           //l_dividend <= l_dividend << 1;
           if (l_dividend >= l_divisor) begin
                l_dividend <= (l_dividend<<1) - l_divisor + 1'b1;
           end else begin
                l_dividend <= l_dividend<<1;
           end
        end
        if (~flush && ~div_ready && count == 8'h40 && ~out_valid) begin
            //div_res <= div_res + ((l_divtiplier[0]) ? l_divtiplicand : 0);
            //div_res <= divtiplicand * divtiplier;
            //$display("div %x %x %x", divtiplicand, divtiplier, div_res);
            out_valid <= 1;
            count <= 0;
            if (sign && sign_div) begin
                div_res_o <= (~div_res) | (1 << 63);
                remain_o <= remain_o;
            end else begin
                div_res_o <= div_res;
                remain_o <= remain_o;
            end
        end
        if (out_valid) begin
            div_ready <= 1;
            out_valid <= 0;
        end
    end
end
endmodule