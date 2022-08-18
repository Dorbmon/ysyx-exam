module ysyx_22041207_dataforward(
    input [4:0] r1addr,
    input [4:0] r2addr,
    input [63:0] r1data,
    input [63:0] r2data,
    input me_writeRD,
    input [4:0] me_rd,
    input [63:0] me_rddata,
    input wb_writeRD,
    input [4:0] wb_rd,
    input [63:0] wb_rddata,
    output reg [63:0] r1data_o,
    output reg [63:0] r2data_o
);
    always @(*) begin
        r1data_o = (me_rd == r1addr && me_writeRD) ? me_rddata : ((wb_rd == r1addr && wb_writeRD) ? wb_rddata : r1data);
        //$display("r1:%x", r1data_o);
        r2data_o = (me_rd == r2addr && me_writeRD) ? me_rddata : ((wb_rd == r2addr && wb_writeRD) ? wb_rddata : r2data);
    end
endmodule