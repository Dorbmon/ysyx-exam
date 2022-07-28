`include "vsrc/alu_define.v"
module ysyx_22041207_decoder(
    input [31:0] inst,
    output reg [3:0] aluOperate,
    output reg sel_a,
    output reg sel_b,
    output reg [7:0] memoryWriteMask,
    output reg [63:0] memoryWriteAddress,
    output reg writeRD,
    output reg pc_sel,
    output reg npc_op
);

wire [6:0] opCode;
wire [6:0] funct7;
wire [2:0] funct3;
assign opCode = inst [6:0];
assign funct7 = inst [31:25];
assign funct3 = inst [14:12];
always @(*)
begin
    case (opCode)
    default: ;
    7'b0110011: // R型指令
    begin
        sel_a = 1'b1;
        sel_b = 1'b1;
        writeRD = 1'b1;
        pc_sel = 1'b0;
        npc_op = 1'b0;
        memoryWriteMask = 8'b0;
        case (funct3)
            3'b0: 
            case (funct7)
                7'b0:  aluOperate = `ALU_ADD;//add
                default: aluOperate = 0;
            endcase
            default: aluOperate = 0;
        endcase
    end
    7'b0010011:    // I型指令
    begin
        sel_a = 1'b1;
        sel_b = 0'b1;
        writeRD = 1'b1;
        pc_sel = 1'b0;
        npc_op = 1'b0;
        memoryWriteMask = 8'b0;
        case (funct3)
        3'b0: aluOperate = `ALU_ADD;//addi
        default: aluOperate = 0;
        endcase
    end
    endcase   
end
endmodule