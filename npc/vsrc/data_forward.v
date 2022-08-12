module ysyx_22041207_dataforward(
    input clk,
    input [4:0] r1addr,
    input [4:0] r2addr,
    input [63:0] r1data,
    input [63:0] r2data,
    input ex_writeRD,
    input [4:0] ex_rd,
    input [63:0] ex_rddata,
    input me_writeRD,
    input [4:0] me_rd,
    input [63:0] me_rddata,
    output reg [63:0] r1data_o,
    output reg [63:0] r2data_o
);
    always @(*) begin
        r1data_o = (ex_rd == r1addr && ex_writeRD) ? ex_rddata : ((me_rd == r1addr && me_writeRD) ? me_rddata : r1data);
        r2data_o = (ex_rd == r2addr && ex_writeRD) ? ex_rddata : ((me_rd == r2addr && me_writeRD) ? me_rddata : r2data);
    end
endmodule