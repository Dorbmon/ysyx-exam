import "DPI-C" function void ebreak ();
module ysyx_22041207_ebreak (
    input clk,
    input ebreak_i
);
always @(posedge clk) begin
    if (ebreak_i) begin
        ebreak();
    end
end
endmodule