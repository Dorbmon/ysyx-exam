module ysyx_22041207_flush (
    input ex_jal,
    input ex_jalr,
    input ex_brach,
    input [63:0] ex_aluRes,
    output reg flush
);
always @(*) begin
    flush = ex_jal || ex_jalr || (ex_brach && ex_aluRes == 0);
end
endmodule