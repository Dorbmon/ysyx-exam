module ysyx_22041207_Bubble (
    input clk,
    input [4:0] ex_r1,
    input [4:0] ex_r2,
    input [4:0] me_rd,
    input [3:0] me_readNum,
    output wire bubble
);
assign bubble = (me_readNum == 4'b0) ? 1'b0 : (((me_rd == ex_r1 || me_rd == ex_r2) && me_rd != 0) ? 1'b1 : 1'b0);
endmodule