module ysyx_22041207_IF (
    input clk,
    input [2:0] stage,
    input [63:0] pc,
    output reg [31:0] inst_o
);
wire [63:0] rawData;
wire [31:0] inst;
ysyx_22041207_read_mem readInst(pc, 1'b1, rawData);
assign inst = rawData [31:0];  // 这里可能有BUG
always @(posedge clk) begin
    if (stage == 3'h0) begin
        inst_o = inst;
        // 然后更新当前pc为npc
    end
end
endmodule