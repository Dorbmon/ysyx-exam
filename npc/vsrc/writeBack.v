module ysyx_22041207_WB(
    input   [63:0]  alu_c   ,
    input   [63:0]  pc      ,
    input   [63:0]  ramdout ,
    input   [63:0]  imm     ,
    input   [ 1:0]  wd_sel  ,
    output  reg [63:0]  wD
    );
    always @(*)
    begin
        case(wd_sel)
        2'b00:  wD = alu_c  ;
        2'b01:  wD = ramdout;
        2'b10:  wD = pc+4   ;
        2'b11:  wD = imm    ;
        default:wD = 64'h0  ;
        endcase
    end
endmodule