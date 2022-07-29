`define ALU_ADD 4'b0000
`define ALU_SUB 4'b0001
`define ALU_RETURN_A 4'b0010
`define ALU_RETURN_B 4'b0011
`define ALU_XOR 4'b0100
`define ALU_OR 4'b0101
`define ALU_AND 4'b0110
`define ALU_SLL 4'b0111
`define ALU_SRL 4'b1000
`define ALU_SLT 4'b1001
`define ALU_SLTU 4'b1010
`define ALU_NONE 4'b1011
`define ALU_MUL 4'b1100
`define ALU_REM 4'b1101
`define ALU_DIVU 4'b1110
`define ALU_REMU 4'b1111
`define R_Type 3'b000
`define J_Type 3'b001
`define I_Type 3'b010
`define S_Type 3'b011
`define U_Type 3'b100
`define B_Type 3'b101
`define SEXT(x, target, exist) {{(target - exist){x[exist-1]}}, x[exist - 1:0]}
`define NSEXT(x, target, exist) {{(target - exist){1'b0}}, x[exist - 1:0]}