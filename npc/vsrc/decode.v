`include "vsrc/alu_define.v"
import "DPI-C" function void ebreak ();
module ysyx_22041207_decoder(
    input [31:0] inst,
    input [63:0] imm,
    input [63:0] rs1,
    input [63:0] rs2,
    output reg [3:0] aluOperate,
    output reg sel_a,
    output reg sel_b,
    output reg [7:0] memoryWriteMask,
    output reg writeRD,
    output reg pc_sel,
    output reg npc_op,
    output reg [2:0] writeBackDataSelect,
    output reg memoryReadWen,
    output reg sext,
    output reg [3:0] readNum
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
        writeBackDataSelect = 3'b00;
        memoryReadWen = 1'b0;
        case (funct3)
            3'b0: 
            case (funct7)
                7'b0:  aluOperate = `ALU_ADD;//add
                7'h20: aluOperate = `ALU_SUB;//sub
                7'b0000001: aluOperate = `ALU_MUL;//mul
                default: aluOperate = `ALU_NONE;
            endcase
            3'b100: aluOperate = `ALU_XOR; //xor
            3'b110: aluOperate = `ALU_OR;  //or
            3'b111: aluOperate = `ALU_AND; //and
            3'b001: aluOperate = `ALU_SLL;
            3'b101: case (funct7)
                7'h0: aluOperate = `ALU_SRL;    //srl
                default: aluOperate = `ALU_NONE;
            endcase
            3'b010: aluOperate = `ALU_SLT;  //slt
            3'b011: aluOperate = `ALU_SLTU; //sltu
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
        writeBackDataSelect = 3'b00;
        memoryReadWen = 1'b0;
        case (funct3)
        3'b0: aluOperate = `ALU_ADD;//addi
        3'b100: aluOperate = `ALU_XOR;//xori
        3'b110: aluOperate = `ALU_OR;  //ori
        3'b111: aluOperate = `ALU_AND; //andi
        3'b001: aluOperate = `ALU_SLL;
        3'b101: case (funct7)
            7'h0: aluOperate = `ALU_SRL;    //srli
            default: aluOperate = `ALU_NONE;
        endcase
        3'b010: aluOperate = `ALU_SLT;  //slti
        3'b011: aluOperate = `ALU_SLTU; //sltui
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
        writeBackDataSelect = 3'b00;
        memoryReadWen = 1'b0;
        aluOperate = `ALU_ADD;
    end
    7'b0000011: // I型指令 但是 读取内存
    begin
        sel_a = 1'b1;
        sel_b = 1'b0;   //rs1 + imm
        writeRD = 1'b1;
        pc_sel = 1'b0;
        npc_op = 1'b0;
        memoryWriteMask = 8'b0;
        writeBackDataSelect = 3'b01;
        memoryReadWen = 1'b1;
        aluOperate = `ALU_ADD;
        case(funct3)
        default: aluOperate = `ALU_NONE;
        3'h0: begin // lb
            sext = 1'b1;
            readNum = 4'h1;
        end
        3'h1: begin // lh
            sext = 1'b1;
            readNum = 4'h2;
        end
        3'h2: begin // lw
            sext = 1'b1;
            readNum = 4'h4;
        end
        3'h3: begin // ld
            sext = 1'b1;
            readNum = 4'h8;
        end
        3'h4: begin // lbu
            sext = 1'b0;
            readNum = 4'h1;
        end
        3'h5: begin // lhu
            sext = 1'b0;
            readNum = 4'h2;
        end
        endcase
    end
    7'b0110111: // U型指令 lui
    begin
        sel_a = 1'b0;
        sel_b = 1'b0;
        writeRD = 1'b1;
        pc_sel = 1'b0;
        npc_op = 1'b0;
        memoryWriteMask = 8'b0;
        writeBackDataSelect = 3'b00;
        memoryReadWen = 1'b0;
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
        writeBackDataSelect = 3'b10;
        memoryReadWen = 1'b0;
        //aluOperate = `ALU_RETURN_B;
    end
    7'b0100011: // S型指令
    begin
        sel_a = 1'b1;
        sel_b = 1'b0;   // 地址永远为rs1 + imm
        writeRD = 1'b0;
        pc_sel = 1'b0;
        npc_op = 1'b0;
        memoryReadWen = 1'b0;
        aluOperate = `ALU_ADD;
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
    end
    7'b0111011: // R型指令 带w 截取32位的指令
    begin
        sel_a = 1'b1;
        sel_b = 1'b1;
        writeRD = 1'b1;
        pc_sel = 1'b0;
        npc_op = 1'b0;
        memoryWriteMask = 8'b0;
        writeBackDataSelect = 3'b100;   // 对32位做符号扩展
        memoryReadWen = 1'b0;
        case (funct7)
        default: aluOperate = `ALU_NONE;
        7'b0100000: begin
            case (funct3)
            3'b000: begin
                aluOperate = `ALU_SUB;
            end
            default: aluOperate = `ALU_NONE;
            endcase
        end
        7'b0000001: begin
            case (funct3)
            3'b0: begin
                aluOperate = `ALU_MUL;  // mulw
            end
            3'b110: begin
                aluOperate = `ALU_REM;  // remw
            end
            3'b101: begin
                aluOperate = `ALU_DIVU; // divu
            end
            3'b111: begin
                aluOperate = `ALU_REMU;
            end
            default: aluOperate = `ALU_NONE;
            endcase
        end
        7'b0000000: begin
            case (funct3)
            3'b000: begin
                aluOperate = `ALU_ADD;  // addw
            end
            default: aluOperate = `ALU_NONE;
            endcase
        end
        endcase
        
    end
    7'b0011011: // I型指令
    begin
        sel_a = 1'b1;
        sel_b = 1'b0;
        writeRD = 1'b1;
        pc_sel = 1'b0;
        npc_op = 1'b0;
        memoryWriteMask = 8'b0;
        writeBackDataSelect = 3'b100;   // 对32位做符号扩展
        memoryReadWen = 1'b0;
        case (funct3)
        3'b000: begin
            aluOperate = `ALU_ADD;
        end
        default: aluOperate = `ALU_NONE;
        endcase
    end
    7'b1100111: // I型指令 jalr
    begin
        //sel_a = 1'b0;
        //sel_b = 1'b0;
        writeRD = 1'b1;
        pc_sel = 1'b1;
        npc_op = 1'b1;
        memoryWriteMask = 8'b0;
        writeBackDataSelect = 3'b10;
        memoryReadWen = 1'b0;
        //aluOperate = `ALU_RETURN_B;
    end
    7'b1100011: // B型指令
    begin
        writeRD = 1'b0;
        memoryWriteMask = 8'b0;
        memoryReadWen = 1'b0;
        pc_sel = 1'b0;
        writeBackDataSelect = 3'b000;
        case(funct3)
        default: npc_op = 1'b0;
        3'h0: begin
            npc_op = ($signed(rs1) == $signed(rs2))?1'b1:1'b0;
        end
        3'h1: begin
            npc_op = ($signed(rs1) != $signed(rs2))?1'b1:1'b0;
        end
        3'h4: begin
            npc_op = ($signed(rs1) < $signed(rs2))?1'b1:1'b0;
        end
        3'h5: begin // bge
            npc_op = ($signed(rs1) >= $signed(rs2))?1'b1:1'b0;
        end
        3'b110: begin // bltu
            npc_op = (rs1 < rs2)?1'b1:1'b0;
        end
        3'b111: begin // bgeu
            npc_op = (rs1 >= rs2)?1'b1:1'b0;
        end
        endcase
    end
    endcase   
end
endmodule