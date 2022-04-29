module ysyx_22041207_ALU(
    input [63:0] pc,
    input [31:0] inst,
    input [63:0] rs1,
    input [63:0] rs2,
    output wen,
    output [63:0] wdata,
    output [63:0] newPcValue
);
wire [63:0] immI;
wire [63:0] immS;
wire [63:0] immB;
wire [63:0] immU;
wire [63:0] immJ;
wire [6:0]  funct7;
wire [2:0]  funct3;
ysyx_22041207_ext ext(inst, immI, immS, immB, immU, immJ, funct7, funct3); 
ysyx_22041207_MuxKeyWithDefault #(5, 7, 129) rmux ({wen, wdata, newPcValue}, inst[6:0], 129'b0, {
    7'b0010011, {1'b1, rs1 + immI, 64'b0},   // addi
    7'b0010111, {1'b0, 64'b0, pc + immU},   // auipc
    7'b0110111, {1'b1, immU, 64'b0},
    7'b1101111, {1'b1, pc + 64'o4, pc + immJ},   //jal
    7'b1100111, (funct3==0)?{1'b1, pc + 64'b100, rs1 + immJ}:129'b0  //jalr
});
endmodule