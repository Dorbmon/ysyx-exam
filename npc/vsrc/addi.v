module ysyx_22041207_addi(
    input isAdd,
    input [31:0] inst,
    input [63:0] rs1,
    output wen,
    output reg [4:0] waddr,
    output reg [63:0] wdata
);
assign wen = isAdd;
assign waddr = inst [11:7];
assign wdata = $signed({52'b0, inst [31:20]}) + rs1;
endmodule