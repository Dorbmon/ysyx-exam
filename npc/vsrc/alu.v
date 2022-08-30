`include "vsrc/alu_define.v"
module ysyx_22041207_alu(
    input clk,
    input rst,
    input flush,
    input [63:0] pc,
    input [4:0] operate,
    input [63:0] rs1,
    input [63:0] rs2,
    input [63:0] csr,
    input [63:0] imm,
    input [1:0] sel_a,
    input [1:0] sel_b,
    input rs1to32,  // rs1 转换为32bit
    output reg [63:0] res,
    output reg alu_wait
);
wire [63:0] a;
wire [63:0] b;
assign a = (sel_a == 2'b1) ? (rs1to32 ? {32'b0, rs1 [31:0]} : rs1) : pc;
assign b = (sel_b == 2'b1) ? rs2 : ((sel_b == 2'h2) ? csr : imm);
reg mul_valid;
wire mul_ready, mul_out_valid;
wire [63:0] mul_res;
initial begin
    alu_wait = 0;
end
reg div_valid;
wire div_ready, div_out_valid;
reg div_sign;
wire [63:0] div_out, remain_out;
ysyx_22041207_mul rx_mul(clk, rst, mul_valid, flush, a, b, mul_ready, mul_out_valid, mul_res);
ysyx_22041207_div rx_div(clk, rst, div_valid, flush, a, b, div_sign, div_ready, div_out_valid, div_out, remain_out);
// ALU的第一个操作数是pc或者rs1
// 第二个操作数为imm或者rs2
reg [31:0] ccc;
always @(posedge clk) begin
    case(operate)
        `ALU_ADD: begin
            res <= a + b;
            //$display("add %x %x %x", a, b, a + b);
        end
        `ALU_SUB: begin 
            res <= a - b;
        end
        `ALU_RETURN_A: res <= a;
        `ALU_RETURN_B: res <= b;
        `ALU_XOR: res <= a ^ b;
        `ALU_OR: res <= a | b;
        `ALU_AND: res <= a & b;
        `ALU_SLL: res <= a << b [5:0];
        `ALU_SRL: res <= a >> b [5:0];
        `ALU_SLT: begin
            res <= $signed(a) < $signed(b) ? 64'b1 : 64'b0;
        end
        `ALU_SLTU: res <= a < b ? 64'b1 : 64'b0;
        `ALU_MUL: begin
            if (~alu_wait) begin
                alu_wait <= 1;   // 卡住alu
                mul_valid <= 1;
            end

            if (mul_valid) begin
                mul_valid <= 0;
            end
            if (mul_out_valid) begin
                res <= mul_res;
                alu_wait <= 0;
            end
        end
        `ALU_REM: res <= $signed(a) % $signed(b);
        `ALU_DIVU: begin 
            
            if (~alu_wait) begin
                div_sign <= 0;
                alu_wait <= 1;   // 卡住alu
                div_valid <= 1;
            end

            if (div_valid) begin
                div_valid <= 0;
            end
            if (div_out_valid) begin
                res <= div_out;
                alu_wait <= 0;
                $display("div %x %x %x %x", a, b, a / b, div_out);
            end
        end
        `ALU_REMU: res <= a % b;
        `ALU_DIV:begin
             //res <= $signed(a) / $signed(b);
            if (~alu_wait) begin
                div_sign <= 1;
                alu_wait <= 1;   // 卡住alu
                div_valid <= 1;
            end
            if (div_valid) begin
                div_valid <= 0;
            end
            if (div_out_valid) begin
                res <= div_out;
                alu_wait <= 0;
                $display("div %x %x %x %x", a, b, a / b, div_out);
            end
        end
        `ALU_SRA: res <= rs1to32 ? {32'b0, ($signed(a [31:0]) >>> b [5:0])} : ($signed(a) >>> b [5:0]);
        `ALU_EQ:  res <= (a == b) ? 1 : 0;
        `ALU_LOE: res <= ($signed(a) >= $signed(b))?1:0;
        `ALU_LOEU: res <= (a >= b)?1:0;
        default: res <= 0;
    endcase
    //$display("res:%h", a);
end
endmodule