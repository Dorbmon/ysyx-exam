`include "vsrc/alu_define.v"
module ysyx_22041207_alu(
    input clk,
    input [63:0] pc,
    input [4:0] operate,
    input [63:0] rs1,
    input [63:0] rs2,
    input [63:0] imm,
    input sel_a,
    input sel_b,
    output reg [63:0] res
);
wire [63:0] a;
wire [63:0] b;
assign a = sel_a ? rs1 : pc;
assign b = sel_b ? rs2 : imm;
// ALU的第一个操作数是pc或者rs1
// 第二个操作数为imm或者rs2
always @(*) begin
    case(operate)
        `ALU_ADD: res = a + b;
        `ALU_SUB: res = a - b;
        `ALU_RETURN_A: res = a;
        `ALU_RETURN_B: res = b;
        `ALU_XOR: res = a ^ b;
        `ALU_OR: res = a | b;
        `ALU_AND: res = a & b;
        `ALU_SLL: res = a << b;
        `ALU_SRL: res = a >> b;
        `ALU_SLT: res = $signed(a) < $signed(b) ? 1 : 0;
        `ALU_SLTU: res = a < b ? 1 : 0;
        `ALU_MUL: res = a * b;
        `ALU_REM: res = $signed(a) % $signed(b);
        `ALU_DIVU: res = a / b;
        `ALU_REMU: res = a % b;
        `ALU_DIV: res = $signed(a) / $signed(b);
        default: res = 0;
    endcase
    //$display("res:%h", a);
end
endmodule