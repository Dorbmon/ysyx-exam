`include "vsrc/alu_define.v"

module ysyx_22041207_decoder(
    input clk,
    input [31:0] inst,
    output reg [4:0] aluOperate,
    output reg [1:0] sel_a,
    output reg [1:0] sel_b,
    output reg [7:0] memoryWriteMask,
    output reg writeRD,
    output reg pc_sel,
    output reg jalr,
    output reg jal,
    output reg [2:0] writeBackDataSelect,
    output reg memoryReadWen,
    output reg sext,
    output reg [3:0] readNum,
    output reg rs1to32,
    output reg wMtvec,
    output reg wMepc,
    output reg wMcause,
    output reg wMstatus,
    output reg pc_panic, // 是否为异常跳转
    output reg pc_mret,   // 是否为mret
    output reg csrWen,
    output reg branch,
    output reg [63:0] imm_o,
    output reg [4:0] rs1addr,
    output reg [4:0] rs2addr,
    output reg [4:0] rwaddr,
    output reg [2:0] csr_order
);
wire [63:0] imm;
wire [2:0] instType;
ysyx_22041207_GetInstType getInstType(inst [6:0], instType);
ysyx_22041207_SEXT SEXT(inst, instType, imm);
wire [6:0] opCode;
wire [6:0] funct7;
wire [2:0] funct3;
assign opCode = inst [6:0];
assign funct7 = inst [31:25];
assign funct3 = inst [14:12];
always @(posedge clk)
begin
    imm_o = imm;
    rs1addr = inst [19:15];
    rs2addr = inst [24:20];
    rwaddr = inst [11:7];
    //$display("decode %x", inst);
    memoryWriteMask = 8'b0;
    wMtvec = 1'b0;
    wMepc = 1'b0;
    wMcause = 1'b0;
    wMstatus = 1'b0;
    pc_panic = 1'b0;
    pc_mret = 1'b0;
    csrWen = 1'b0;
    memoryReadWen = 1'b0;
    writeRD = 1'b0;
    pc_sel = 1'b0;
    rs1to32 = 1'b0;
    sext = 1'b0;
    branch = 1'b0;
    jalr = 1'b0;
    jal = 1'b0;
    csr_order = 0;
    case (opCode)
    default: ;
    7'b1110011: // 系统指令
    begin
        case (funct3)
        3'b001: begin   // csrrw
        // 将csr的值写入rd 并将csr的值更新为rs1
        // csr写回的值直接设置为alu res
            writeRD = 1'b1;
            writeBackDataSelect = 3'b101;
            csrWen = 1'b1;
            sel_a = 2'b1;
            aluOperate = `ALU_RETURN_A;
        end
        3'b010: begin   // csrrs
            writeRD = 1'b1;
            writeBackDataSelect = 3'b101;   // 写回csr
            sel_a = 2'b1;   // 选择rs1作为a
            sel_b = 2'h3;   // 选择csr作为b
            aluOperate = `ALU_OR;
        end
        3'b0: begin
            case (imm)
                64'h1: begin     // ebreak
                    csr_order = 3'b1;
                end
                64'b0: begin
                    // ecall
                    wMepc = 1'b1;   // epc = pc
                    wMcause = 1'b1; // cause = cause
                    wMstatus = 1'b1;
                    // 然后更改pc
                    pc_panic = 1'b1;
                end
                64'b001100000010: begin // mret
                    // 返回mepc
                    pc_mret = 1'b1;
                end
                default: wMepc = 1'b0;
            endcase
        end
        default: aluOperate = `ALU_NONE;
        endcase
    end
    7'b0110011: // R型指令
    begin
        sel_a = 2'b1;
        sel_b = 2'b1;
        writeRD = 1'b1;
        writeBackDataSelect = 3'b000;
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
            3'b001: aluOperate = `ALU_SLL;  // sll
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
        sel_a = 2'b1;
        sel_b = 2'b0;
        writeBackDataSelect = 3'b000;
        writeRD = 1'b1;
        case (funct3)
        3'b000: aluOperate = `ALU_ADD;//addi
        3'b100: aluOperate = `ALU_XOR;//xori
        3'b110: aluOperate = `ALU_OR;  //ori
        3'b111: aluOperate = `ALU_AND; //andi
        3'b001: aluOperate = `ALU_SLL;  // slli
        3'b101: case (funct7[6:1])
            6'h0: aluOperate = `ALU_SRL;    //srli
            6'h10: aluOperate = `ALU_SRA;    //srai
            default: aluOperate = `ALU_NONE;
        endcase
        3'b010: aluOperate = `ALU_SLT;  //slti
        3'b011: aluOperate = `ALU_SLTU; //sltiu
        default: aluOperate = 0;
        endcase
    end
    7'b0010111: // U型指令 auipc
    begin
        sel_a = 2'b0;
        sel_b = 2'b0;
        writeRD = 1'b1;
        writeBackDataSelect = 3'b00;
        aluOperate = `ALU_ADD;
    end
    7'b0000011: // I型指令 但是 读取内存
    begin
        sel_a = 2'b1;
        sel_b = 2'b0;   //rs1 + imm
        writeRD = 1'b1;
        writeBackDataSelect = 3'b001;
        memoryReadWen = 1'b1;
        aluOperate = `ALU_ADD;
        case(funct3)
        default: begin
            sext = 1'b0;
            readNum = 4'h0;
        end
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
        3'h6: begin // lwu
            sext = 1'b0;
            readNum = 4'h4;
        end
        endcase
    end
    7'b0110111: // U型指令 lui
    begin
        //sel_a = 2'b00;
        sel_b = 2'b00;
        writeRD = 1'b1;
        writeBackDataSelect = 3'b000;
        aluOperate = `ALU_RETURN_B;
    end
    7'b1101111: // J型指令 jal
    begin
        writeRD = 1'b1;
        writeBackDataSelect = 3'b10;
        jal = 1'b1;
        //$display("decode jal");
    end
    7'b0100011: // S型指令
    begin
        sel_a = 2'b1;
        sel_b = 2'b0;   // 地址永远为rs1 + imm
        aluOperate = `ALU_ADD;
        case (funct3)
        3'b000:begin  //sb
            //$display("catch sb");
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
        sel_a = 2'b1;
        sel_b = 2'b1;
        writeRD = 1'b1;
        writeBackDataSelect = 3'b100;   // 对32位做符号扩展
        case (funct7)
        default: aluOperate = `ALU_NONE;
        7'b0100000: begin
            case (funct3)
            3'b000: begin
                aluOperate = `ALU_SUB;
            end
            3'b101: begin
                aluOperate = `ALU_SRA;
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
                aluOperate = `ALU_DIVU; // divuw
            end
            3'b111: begin
                aluOperate = `ALU_REMU; // remu
            end
            3'b100: begin
                aluOperate = `ALU_DIV;  // divuw
            end
            default: aluOperate = `ALU_NONE;
            endcase
        end
        7'b0000000: begin
            case (funct3)
            3'b000: begin
                writeBackDataSelect = 3'b100;   // 结果截取32位，再做扩展
                case (funct7)
                    7'b0100000: aluOperate = `ALU_SUB;  // subw
                    7'b0000000: aluOperate = `ALU_ADD;  // addw
                    default aluOperate = `ALU_NONE;
                endcase
            end
            3'b001: begin
                writeBackDataSelect = 3'b100;
                aluOperate = `ALU_SLL;  // sllw
            end
            3'b101: begin
                rs1to32 = 1'b1;
                case (funct7)
                    7'b0100000: aluOperate = `ALU_SRA;  // sraw
                    7'b0000000: aluOperate = `ALU_SRL;  // srlw
                    default aluOperate = `ALU_NONE;
                endcase
                
            end
            default: aluOperate = `ALU_NONE;
            endcase
        end
        endcase
        
    end
    7'b0011011: // I型指令
    begin
        sel_a = 2'b1;
        sel_b = 2'b0;
        writeRD = 1'b1;
        writeBackDataSelect = 3'b100;   // 对32位做符号扩展
        case (funct3)
        3'b000: begin   
            aluOperate = `ALU_ADD; // addiw
        end
        3'b001: begin
            aluOperate = `ALU_SLL;  // slliw
        end
        3'b101: begin
            rs1to32 = 1'b1;
            case (funct7)
            7'b0000000: begin
                aluOperate = `ALU_SRL;  // srliw
            end
            7'b0100000: begin
                aluOperate = `ALU_SRA;  // sraiw
            end
            default: aluOperate = `ALU_NONE;
            endcase
        end
        default: aluOperate = `ALU_NONE;
        endcase
    end
    7'b1100111: // I型指令 jalr
    begin
        writeRD = 1'b1;
        pc_sel = 1'b1;
        jalr = 1'b1;
        writeBackDataSelect = 3'b10;
    end
    7'b1100011: // B型指令
    begin
        sel_a = 2'b1;
        sel_b = 2'b1;
        branch = 1'b1;
        case(funct3)
        default: aluOperate = `ALU_NONE;
        3'h0: begin // beq  相等的时候跳转
            aluOperate = `ALU_XOR;  //只有相等的时候为0
        end
        3'h1: begin // bne
            // 不相等的时候为0
            aluOperate = `ALU_EQ;
        end
        3'h4: begin // blt
            // 小于的时候跳转
            aluOperate = `ALU_LOE;
        end
        3'h5: begin // bge
           // 小于的时候为1
           aluOperate = `ALU_SLT;
        end
        3'b110: begin // bltu
            aluOperate = `ALU_LOEU;
        end
        3'b111: begin // bgeu
            aluOperate = `ALU_SLTU;
        end
        endcase
    end
    endcase
end
endmodule