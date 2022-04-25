import "DPI-C" function void ebreak (input int is);
module Vysyx_22041207_EBreak(
    input isEBreak
);
always @(*) begin
    //$display("ebreak:%b", isEBreak);
    ebreak({31'b0,isEBreak});
end
endmodule