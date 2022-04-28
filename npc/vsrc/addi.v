module ysyx_22041207_addi(
    input isAdd,
    input [31:0] inst,
    input [63:0] rs1,
    output reg wen,
    output reg [4:0] waddr,
    output reg [63:0] wdata
);
always @(*) begin
    if (isAdd == 1'b1) begin
        wen = 1'b1;
        waddr = inst [11:7];
        wdata = $signed({52'b0, inst [31:20]}) + rs1;
    end
    else begin
        wen = 1'b0;
        waddr = 0;
        wdata = 0;
    end
end
endmodule