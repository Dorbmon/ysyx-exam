module ysyx_22041207_Bubble (
    input [4:0] ex_r1,
    input [4:0] ex_r2,
    input [4:0] me_rd,
    input [3:0] me_readNum,
    output reg pc_delay,
    output reg bubble
);
always @(*) begin
    if (me_readNum == 4'b0) begin
        pc_delay = 1'b0;
        bubble = 1'b0;
    end
    else begin
        pc_delay = (me_rd == ex_r1 || me_rd == ex_r2) ? 1'b1 : 1'b0;
        bubble = (me_rd == ex_r1 || me_rd == ex_r2) ? 1'b1 : 1'b0;
    end
end
endmodule