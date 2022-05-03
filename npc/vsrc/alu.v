module ysyx_22041207_ALU(
    input [63:0] pc,
    input [31:0] inst,
    input [63:0] rs1,
    input [63:0] rs2,
    output wen,
    output [4:0]  rwaddr,
    output [63:0] wdata,
    output [63:0] newPcValue
);
function [31:0] low32;
    input [63:0] data;
    //low32 = {32'b0, data[31:0]};
    low32 = data[31:0];
endfunction
`define SEXT(x, bit) {{(64 - bit){{x}[bit - 1]}}, {x}[bit- 1:0]}
wire [63:0] immI;
wire [63:0] immS;
wire [63:0] immB;
wire [63:0] immU;
wire [63:0] immJ;
wire [6:0]  funct7;
wire [2:0]  funct3;
ysyx_22041207_ext ext(inst, immI, immS, immB, immU, immJ, funct7, funct3); 
wire [63:0] LValue;
wire [6:0] opCode;
assign opCode = inst[6:0];
wire [63:0] srs1 = $signed(rs1);
wire [63:0] srs2 = $signed(rs2);
ysyx_22041207_MR mr((opCode == 7'b0000011 || opCode == 7'b0000011), rs1 + immI, LValue);
wire [63:0] mwaddr;
wire [63:0] mwdata;
wire [7:0] mwmask;
ysyx_22041207_MW mw(mwaddr, mwdata, mwmask);
always @(*) begin
    $display("r1:%x\n", immI[4:0]);
end
ysyx_22041207_MuxKeyWithDefault #(9, 7, 65) rmux ({wen, wdata}, opCode, 65'b0, {
    7'b0000011, (funct3 == 3'b011)?{1'b1,  LValue}:             //ld
                (funct3 == 3'b001)?{1'b1, `SEXT(LValue[15:0], 16)}:    //lh
                (funct3 == 3'b100)?{1'b1, {56'b0, LValue[7:0]}}:  //lbu
                (funct3 == 3'b101)?{1'b1, {48'b0, LValue[15:0]}}: //lhu  
                (funct3 == 3'b010)?{1'b1, `SEXT(LValue[31:0], 32)}:  //lw
                65'b0,
    7'b0010111, {1'b1, pc + immU},   // auipc
    7'b0110111, {1'b1, immU},        // lui
    7'b1101111, {1'b1, pc + 64'b100},   //jal
    7'b1100111, (funct3 == 3'b000)?{1'b1, pc + 64'b100}:  //jalr
                65'b0,
    7'b0010011, (funct3 == 3'b011)?{1'b1, (rs1 < immI)?64'b1:64'b0}: //sltiu
                (funct3 == 3'b000)?{1'b1, rs1 + immI}:    //addi
                (funct3 == 3'b111)?{1'b1, rs1 & immI}:    //andi
                (funct3 == 3'b100)?{1'b1, rs1 ^ immI}:    //xori
                (funct3 == 3'b101 && funct7[6:1] == 6'b000000)?{1'b1, rs1 >> immI[5:0]}:  //srli
                (funct3 == 3'b101 && funct7 == 7'b0100000)?{1'b1, rs1 >> immI[4:0]}:  //srai
                (funct3 == 3'b001 && funct7[6:1] == 6'b000000)?{1'b1, rs1 << immI[5:0]}:  //slli
                65'b0,
    7'b0011011, (funct3 == 3'b101 && funct7 == 7'b0000000)?{1'b1, `SEXT(rs1 >> immI, 32)}:  //srliw
                (funct3 == 3'b101 && funct7 == 7'b0100000)?{1'b1, `SEXT($signed(rs1[31:0]) >>> $signed(immI[5:0]), 32)}: //sraiw
                (funct3 == 3'b001 && funct7 == 7'b0000000)?{1'b1, `SEXT(rs1 << immI, 32)}:   //slliw
                (funct3 == 3'b000)?{1'b1, `SEXT(low32(rs1 + immI), 32)}:  //addiw
                65'b0,
    7'b0111011, (funct3 == 3'b000 && funct7 == 7'b0100000)?{1'b1, `SEXT(low32(srs1 - srs2), 32)}://subw
                (funct3 == 3'b110 && funct7 == 7'b0000001)?{1'b1, `SEXT(low32(srs1 % srs2), 32)}://remw
                (funct3 == 3'b000 && funct7 == 7'b0000001)?{1'b1, `SEXT(low32(srs1 * srs2), 32)}://mulw
                (funct3 == 3'b111 && funct7 == 7'b0000001)?{1'b1, `SEXT(low32(rs1) %  low32(rs2), 32)}://remuw
                (funct3 == 3'b101 && funct7 == 7'b0000000)?{1'b1, `SEXT(low32(rs1) >> rs2, 32)}://srlw
                (funct3 == 3'b101 && funct7 == 7'b0100000)?{1'b1, `SEXT($signed(low32(rs1)) >>> rs2, 32)}://sraw
                (funct3 == 3'b001 && funct7 == 7'b0000000)?{1'b1, `SEXT(low32(rs1 << rs2), 32)}:  //sllw
                (funct3 == 3'b000 && funct7 == 7'b0000000)?{1'b1, `SEXT(rs1[31:0] + rs2[31:0], 32)}:   //addw
                (funct3 == 3'b100 && funct7 == 7'b0000001)?{1'b1, `SEXT(rs1[31:0] / rs2[31:0], 32)}:   //divw
                (funct3 == 3'b101 && funct7 == 7'b0000001)?{1'b1, `SEXT(rs1[31:0] / rs2[31:0], 32)}://divuw
                65'b0,   
    7'b0110011, (funct3 == 3'b000 && funct7 == 7'b0000001)?{1'b1, rs1 * rs2}: //mul
                (funct3 == 3'b000 && funct7 == 7'b0000000)?{1'b1, rs1 + rs2}: //add
                (funct3 == 3'b010 && funct7 == 7'b0000000)?{1'b1, $signed(rs1)<$signed(rs2)?64'b1:64'b0}://slt
                (funct3 == 3'b110 && funct7 == 7'b0000000)?{1'b1, rs1 | rs2}://or
                (funct3 == 3'b111 && funct7 == 7'b0000000)?{1'b1, rs1 & rs2}://and
                (funct3 == 3'b011 && funct7 == 7'b0000000)?{1'b1, (rs1 < rs2)?64'b1:64'b0}://sltu
                (funct3 == 3'b000 && funct7 == 7'b0100000)?{1'b1, rs1 - rs2}://sub
                (funct3 == 3'b101 && funct7 == 7'b0000001)?{1'b1, rs1 / rs2}://divu
                (funct3 == 3'b100 && funct7 == 7'b0000000)?{1'b1, rs1 ^ rs2}:
                65'b0
    
});
ysyx_22041207_MuxKeyWithDefault #(3, 7, 64) rmuxB (newPcValue, opCode, 64'b0, {
    7'b1100011, (funct3 == 3'b000)?((rs1 == rs2)?(pc + immB):64'b0):    //beq
                (funct3 == 3'b001)?((rs1 != rs2)?(pc + immB):64'b0):    //bne
                (funct3 == 3'b100)?(($signed(rs1) < $signed(rs2))?(pc + immB):64'b0):  //blt
                (funct3 == 3'b101)?(($signed(rs1) >= $signed(rs2))?(pc + immB):64'b0):  //bge
                (funct3 == 3'b110)?((rs1 < rs2)?(pc + immB):64'b0):  //bltu
                (funct3 == 3'b111)?((rs1 >= rs2)?(pc + immB):64'b0):    //bgeu
                64'b0,
    7'b1101111, pc + immJ,   //jal
    7'b1100111, (funct3==0)?(rs1 + immI):64'b0  //jalr
});
ysyx_22041207_MuxKeyWithDefault #(1, 7, 136) mmuxM ({mwmask, mwaddr, mwdata}, opCode, 136'b0, {
    7'b0100011, (funct3 == 3'b011)?{8'b11111111, rs1 + immS, rs2}:  //sd
                (funct3 == 3'b000)?{8'b00000001, rs1 + immS, rs2}:  //sb
                (funct3 == 3'b001)?{8'b00000011, rs1 + immS, rs2}:  //sh
                (funct3 == 3'b010)?{8'b00001111, rs1 + immS, rs2}:  //sw
                136'b0
});
endmodule