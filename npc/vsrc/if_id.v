module ysyx_22041207_if_id (
    input clk,
    input bubble,
    input [31:0] inst,
    input [63:0] pc,
    output reg [31:0] inst_o,
    output reg [63:0] pc_o
);
always @(negedge clk) begin
    if (bubble) begin
        $display("wwww");
        inst_o <= inst_o;
        pc_o <= pc_o;
    end else begin
        inst_o <= inst;
        pc_o <= pc;
    end
    $display("npc:%x", pc_o);
end
endmodule