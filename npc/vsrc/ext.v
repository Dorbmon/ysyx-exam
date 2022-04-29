module ysyx_22041207_ext(
    input  [31:0] instr,
    output [63:0] immI,
    output [63:0] immS,
    output [63:0] immB,
    output [63:0] immU,
    output [63:0] immJ,
    output [6:0]  funct7,
    output [2:0]  funct3
);
assign immI = $signed({52'b0, instr[31:20]});
assign immS = $signed({52'b0, instr[31:25], instr[11:7]});
assign immB = $signed({51'b0 ,instr[31], instr[7], instr[30:25], instr[11:8], 1'b0});
assign immU = $signed({32'b0,instr[31:12], 12'b0});
assign immJ = $signed({instr[31], instr[19:12], instr[20], instr[30:21], 1'b0});
endmodule