`include "vsrc/alu_define.v"

module ysyx_22041207_GetInstType (
    input [6:0] opCode,
    output [2:0] instType
);
assign instType = (opCode == 7'b0110011) ? `R_Type : 
    (
    (opCode == 7'b0010011 || opCode == 7'b0000011 || opCode == 7'b1100111 || opCode == 7'b1110011) ? `I_Type : 
    (opCode == 7'b0100011 ? `S_Type : 
    (opCode == 7'b1100011 ? `B_Type : 
    (opCode == 7'b1101111 ? `J_Type : 
    ((opCode == 7'b0110111 || opCode == 7'b0010111) ? `U_Type : 3'b0
    )))));

endmodule