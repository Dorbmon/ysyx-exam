`define ALU_ADD 5'b00000
`define ALU_SUB 5'b00001
`define ALU_RETURN_A 5'b00010
`define ALU_RETURN_B 5'b00011
`define ALU_XOR 5'b00100
`define ALU_OR 5'b00101
`define ALU_AND 5'b00110
`define ALU_SLL 5'b00111
`define ALU_SRL 5'b01000
`define ALU_SLT 5'b01001
`define ALU_SLTU 5'b01010
`define ALU_NONE 5'b01011
`define ALU_MUL 5'b01100
`define ALU_REM 5'b01101
`define ALU_DIVU 5'b01110
`define ALU_REMU 5'b01111
`define ALU_DIV 5'b10000
`define ALU_SRA 5'b10001
`define ALU_EQ 5'b10010
`define ALU_LOE 5'b10011
`define ALU_LOEU 5'b10100
`define R_Type 3'b000
`define J_Type 3'b001
`define I_Type 3'b010
`define S_Type 3'b011
`define U_Type 3'b100
`define B_Type 3'b101
`define SEXT(x, target, exist) {{(target - exist){x[exist-1]}}, x[exist - 1:0]}
`define NSEXT(x, target, exist) {{(target - exist){1'b0}}, x[exist - 1:0]}

// csr address:
`define CSR_MEPC_ADDRESS 12'h341
`define CSR_MCAUSE_ADDRESS 12'h342
`define CSR_MTVEC_ADDRESS 12'h305
`define CSR_MSTATUS_ADDRESS 12'h300