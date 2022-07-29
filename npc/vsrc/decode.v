`include "vsrc/alu_define.v"
import "DPI-C" function void ebreak ();
module ysyx_22041207_decoder(
    input [31:0] inst,
    input [63:0] imm,
    output reg [3:0] aluOperate,
    output reg sel_a,
    output reg sel_b,
    output reg [7:0] memoryWriteMask,
    output reg writeRD,
    output reg pc_sel,
    output reg npc_op,
    output reg [1:0] writeBackDataSelect
);

wire [6:0] opCode;
wire [6:0] funct7;
wire [2:0] funct3;
assign opCode = inst [6:0];
assign funct7 = inst [31:25];
assign funct3 = inst [14:12];
always @(*)
begin
    if (inst[6:0] == 7'b1110011 && funct3 == 0 && imm == 64'h1) begin
        ebreak();
    end
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
        writeBackDataSelect = 2'b00;
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
        sel_b = 1'b0;
        writeRD = 1'b1;
        pc_sel = 1'b0;
        npc_op = 1'b0;
        memoryWriteMask = 8'b0;
        writeBackDataSelect = 2'b00;
        case (funct3)
        3'b0: aluOperate = `ALU_ADD;//addi
        default: aluOperate = 0;
        endcase
    end
    7'b0010111: // U型指令 auipc
    begin
        sel_a = 1'b0;
        sel_b = 1'b0;
        writeRD = 1'b1;
        pc_sel = 1'b0;
        npc_op = 1'b0;
        memoryWriteMask = 8'b0;
        writeBackDataSelect = 2'b00;
        aluOperate = `ALU_ADD;
    end
    7'b0110111: // U型指令 lui
    begin
        sel_a = 1'b0;
        sel_b = 1'b0;
        writeRD = 1'b1;
        pc_sel = 1'b0;
        npc_op = 1'b0;
        memoryWriteMask = 8'b0;
        writeBackDataSelect = 2'b00;
        aluOperate = `ALU_RETURN_B;
    end
    7'b1101111: // J型指令 jal
    begin
        //sel_a = 1'b0;
        //sel_b = 1'b0;
        writeRD = 1'b1;
        pc_sel = 1'b0;
        npc_op = 1'b1;
        memoryWriteMask = 8'b0;
        writeBackDataSelect = 2'b10;
        //aluOperate = `ALU_RETURN_B;
    end
    7'b0100011: // S型指令
    begin
        sel_a = 1'b1;
        sel_b = 1'b0;   // 地址永远为rs1 + imm
        writeRD = 1'b0;
        pc_sel = 1'b0;
        npc_op = 1'b0;
        //memoryWriteMask = 8'b0;
        //writeBackDataSelect = 2'b00;
        aluOperate = `ALU_ADD;
        $display("here");
        case (funct3)
        3'b000:begin  //sb
            memoryWriteMask = 8'b00000001;
        end
        3'b001:begin  //sh
            memoryWriteMask = 8'b00000011;
        end
        3'b010:begin  //sw
            memoryWriteMask = 8'b00001111;
        end
        3'b011:begin  //sd
            memoryWriteMask = 8'b11111111;
        end
        default: memoryWriteMask = 8'b0;
        endcase
        $display("mask:%x", memoryWriteMask);
    end
    endcase   
end
endmodule