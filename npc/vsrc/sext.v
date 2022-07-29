module ysyx_22041207_SEXT(
    input [31:0]  instr,
    input [ 2:0] sext_op ,
    output reg  [63:0]  imm
    );
    always @(*)
    begin
            case(sext_op)
            `I_Type:
                imm = {{(53){instr[31]}}, instr[30:20]};
            `S_Type:
                imm = {{(53){instr[31]}}, instr[30:25], instr[11:7]};
            `B_Type:
                imm = {{(52){instr[31]}}, instr[7], instr[30:25], instr[11:8], 1'b0};
            `U_Type:
                imm = {{(33){instr[31]}}, instr[30:12], 12'b0};
            `J_Type:
                imm = {{(44){instr[31]}}, instr[19:12], instr[20], instr[30:21], 1'b0};
            default:         imm = 64'b0;
            endcase
            //$display("imm:%x", imm);
    end
endmodule