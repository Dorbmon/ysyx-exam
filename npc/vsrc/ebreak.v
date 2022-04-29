import "DPI-C" function void ebreak ();
module Vysyx_22041207_System(
    input [31:0] inst
);
wire [63:0] immI;
wire [63:0] immS;
wire [63:0] immB;
wire [63:0] immU;
wire [63:0] immJ;
wire [6:0]  funct7;
wire [2:0]  funct3;
ysyx_22041207_ext ext(inst, immI, immS, immB, immU, immJ, funct7, funct3); 
always @(*) begin
    //$display("inst:%b", inst);
    if (inst[6:0] == 7'b1110011 && funct3 == 0 && immI == 64'h1) begin
        ebreak();
    end
end
endmodule