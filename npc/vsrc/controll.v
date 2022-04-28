module ControlUnit(
    input [31:0] inst,
    output [4:0] r1addr,
    output [4:0] r2addr,
    output [4:0] rwaddr,
    output [63:0] rwdata,
    input [63:0] r1data,
    input [63:0] r2data,
    output wen,
    output reg [31:0] pc
);
always @(inst) begin
    $display("inst:%b", inst);
end
wire [11:0] immI = inst [31:20];
wire [4:0] rs1 = inst [19:15];
wire [4:0] rs2 = inst [24:20];
wire [4:0] rd = inst [11:7];
wire [6:0] opCode = inst [6:0];
wire [2:0] funct3 = inst [14:12];
assign r1addr = rs1;
assign r2addr = rs2;
//ysyx_22041207_addi addi((inst[6:0] == 7'b0010011),inst, r1data, wen, rwaddr, rwdata);

//ysyx_22041207_EBreak ebreak((inst[6:0] == 7'b1110011 && funct3 == 3'b0));

//ysyx_22041207_auipc auipc((inst[6:0] == 0010111), pc, inst);
endmodule