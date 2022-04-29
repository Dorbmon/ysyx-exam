module ysyx_22041207_ALU(
    input [31:0] inst,
    input [63:0] rs1,
    input [63:0] rs2,
    output wen,
    output [63:0] wdata
);
wire [63:0] immI;
wire [63:0] immS;
wire [63:0] immB;
wire [63:0] immU;
wire [63:0] immJ;
ysyx_22041207_ext ext(inst, immI, immS, immB, immU, immJ);
ysyx_22041207_MuxKeyWithDefault #(1, 7, 65) rmux ({wen,wdata}, inst[6:0], 65'b0, {
    7'b0010011, {1'b1,rs1 + immI}
});
endmodule