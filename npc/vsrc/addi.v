module ysyx_22041207_addi(
    input clk,
    input [31:0] inst,
    input [63:0] regReaddata,
    output [74:0] data
);
wire [11:0] imm;
assign imm = inst [31:20];
assign data [74:74] = 1'b1;
assign data [73:69] = inst [19:15];   //读入指定寄存器
always @ (posedge clk) begin
    data [68:64] = inst [11:7];
    data [63:0]  = {52'b0 ,imm} + regReaddata;
end

endmodule