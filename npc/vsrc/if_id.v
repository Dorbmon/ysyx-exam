module ysyx_22041207_if_id (
    input clk,
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
    end else begin
        inst_o <= inst;
        pc_o <= pc;
    end
    $display("npc:%x", pc);
end
endmodule