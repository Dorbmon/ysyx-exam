module ysyx_22041207_auipc(
    input is,
    input [31:0] pc,
    input [63:0] inst,
    output [31:0] nPc
);
assign nPc = pc + {inst[31:12], 12'b0};
endmodule