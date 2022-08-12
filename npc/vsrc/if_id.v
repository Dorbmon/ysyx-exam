module ysyx_22041207_if_id(
    input clk,
    input bubble,
    input flush,
    input [31:0] inst,
    input [63:0] pc,
    output reg [31:0] inst_o,
    output reg [63:0] pc_o
);
always @(negedge clk) begin
    if (flush) begin
        inst_o <= 0;
        pc_o <= 0;
        $display("flush...");
    end
    else if (bubble) begin
        inst_o <= inst_o;
        pc_o <= pc_o;
    end 
    else begin
        inst_o <= inst;
        pc_o <= pc;
    end
end
endmodule