module ysyx_22041207_SEXT(
    input [31:0]  instr,
    input [ 2:0] sext_op ,
    output reg  [63:0]  imm
    );
    wire [2:0] funct3;
    assign funct3 = instr[14:12];
    always @(*)
    begin
            case(sext_op)
            `I_Type:
                imm = {{(53){instr[31]}}, instr[30:20]};
            `S_Type:
                imm = {{(53){instr[31]}}, instr[30:25], instr[11:7]};
            `B_Type: begin
                case (funct3)
                    3'b110: begin
                        // 0扩展
                        imm = {51'b0, instr[31], instr[7], instr[30:25], instr[11:8], 1'b0};
                    end
                    3'h7: begin
                        // 0扩展
                        imm = {51'b0, instr[31], instr[7], instr[30:25], instr[11:8], 1'b0};
                    end
                    default: imm = {{(52){instr[31]}}, instr[7], instr[30:25], instr[11:8], 1'b0};
                endcase
            end
            `U_Type:
                imm = {{(33){instr[31]}}, instr[30:12], 12'b0};
            `J_Type:
                imm = {{(44){instr[31]}}, instr[19:12], instr[20], instr[30:21], 1'b0};
            default:         imm = 64'b0;
            endcase
            //$display("imm:%x", imm);
    end
endmodule