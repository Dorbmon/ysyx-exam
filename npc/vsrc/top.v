module ysyx_22041207_top (
  input clk,
  output reg [63:0] pc
);

wire [4:0] r1addr,r2addr,rwaddr;
wire [63:0] r1data,r2data,rwdata;
wire wen;
RegisterFile #(32, 5, 64) r(clk, rwdata, rwaddr, r1addr, r1data, r2addr, r2data, wen);
wire [63:0] newPcValue;
always @ (posedge clk) begin
if (newPcValue != 64'b0) begin
    pc <= newPcValue;
end
else begin
    pc <= pc + 64'h00000004;
end
end
initial begin
  pc = 64'h80000000;
end
wire  [31:0] inst;
wire  [63:0] origin;
ysyx_22041207_MR pc_mr(1'b1, pc, origin);
assign inst = origin [31:0];
// always @(*) begin
//   $display("pc:%x,here:%b", pc, inst[6:0]);
// end
assign r1addr = inst [19:15];
assign r2addr = inst [24:20];
assign rwaddr = inst [11:7];
ysyx_22041207_ALU alu(pc, inst, r1data, r2data, wen, rwaddr, rwdata, newPcValue);
Vysyx_22041207_System system(inst);
endmodule