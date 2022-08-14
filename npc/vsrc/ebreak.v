import "DPI-C" function void ebreak ();
module ysyx_22041207_csrOrder (
    input clk,
    input [2:0] ex_csrOrder
);
always @(posedge clk) begin
    if (ex_csrOrder == 3'h1) begin
        ebreak();
    end
end
endmodule