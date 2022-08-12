module ysyx_22041207_WB(
    input   [63:0]  alu_c   ,
    input   [63:0]  pc      ,
    input   [63:0]  ramdout ,
    input   [63:0]  imm     ,
    input   [63:0]  csrValue,
    input   [ 2:0]  wd_sel  ,
    output  reg [63:0]  wD
    );
    always @(*)
    begin
        case(wd_sel)
        3'b000:  wD = alu_c  ;
        3'b001:  wD = ramdout;
        3'b010:  wD = pc+4   ;
        3'b011:  wD = imm    ;
        3'b100:  wD = {{(32){alu_c [31]}}, alu_c [31:0]};
        3'b101:  wD = csrValue;
        default: wD = 64'h0  ;
        endcase
    end
endmodule