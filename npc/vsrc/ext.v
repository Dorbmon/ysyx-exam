module ysyx_22041207_ext(
    input [31:0] instr,
    output [31:0] immI,
    output [31:0] immS,
    output [31:0] immB,
    output [31:0] immU,
    output [31:0] immJ
);
assign immI = $signed({20'b0, instr[31:20]});
assign immS = $signed({20'b0, instr[31:25], instr[11:7]});
assign immB = $signed({19'b0 ,instr[31], instr[7], instr[30:25], instr[11:8], 1'b0});
assign immU = $signed({instr[31:12], 12'b0});
assign immJ = $signed({11'b0, instr[31], instr[19:12], instr[20], instr[30:21], 1'b0});
endmodule