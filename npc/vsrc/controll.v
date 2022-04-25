module ControlUnit(
    input [31:0] inst,
    output [4:0] r1addr,
    output [4:0] r2addr,
    output [4:0] rwaddr,
    output [63:0] rwdata,
    input [63:0] r1data,
    input [63:0] r2data,
    output wen
);
wire [11:0] immI = inst [31:20];
wire [4:0] rs1 = inst [19:15];
wire [4:0] rs2 = inst [24:20];
wire [4:0] rd = inst [11:7];
wire [6:0] opCode = inst [6:0];
assign r1addr = rs1;
assign r2addr = rs2;
ysyx_22041207_addi addi((inst[6:0] == 7'b0010011),inst, r1data, wen, rwaddr, rwdata);
endmodule