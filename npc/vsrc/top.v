module ysyx_22041207_top (
  input clk,
  //input [31:0] inst,
  output reg [63:0] pc
);

wire [4:0] r1addr,r2addr,rwaddr;
wire [63:0] r1data,r2data,rwdata;
wire writeRD;
ysyx_22041207_RegisterFile #(32, 5, 64) r(clk, rwdata, rwaddr, r1addr, r1data, r2addr, r2data, writeRD);
//reg [63:0] pc;
initial begin
  pc = 64'h80000000;
end
wire [63:0] imm;
wire pc_sel, npc_op;
wire sel_a, sel_b;
wire [63:0] npc;
ysyx_22041207_GetPC getPc(imm, r1data, pc_sel, npc_op, pc, npc);
always @(posedge clk) begin
  pc <= npc;
  //$display("inst:%h", pc);
end
// 从npc取指
wire [63:0] rawData;
wire [31:0] inst;
  assign r1addr = inst [19:15];
  assign r2addr = inst [24:20];
  assign rwaddr = inst [11:7];
ysyx_22041207_read_mem readInst(pc, 1'b1, rawData);
assign inst = rawData [31:0];  // 这里可能有BUG
// 传入解码
wire [4:0] aluOperate;

wire [2:0] instType;
wire [63:0] aluRes;
ysyx_22041207_GetInstType getInstType(inst [6:0], instType);
wire [63:0] memoryReadData;
wire [2:0] writeBackDataSelect; // 写回数据选择
wire [7:0] memoryWriteMask;
wire memoryReadWen;
wire sext;
wire [3:0] readNum;
wire rs1to32;
wire [11:0] csrAddress;
wire csrWen;
wire [63:0] mtvec;
wire [63:0] mepc;
wire [63:0] mcause;
wire [63:0] csrReadData;
wire wMtvec;
wire [63:0] mtvec_v;
wire wMepc;
wire [63:0] mepc_v;
wire wMcause;
wire [63:0] mcause_v;
assign mepc = pc;
ysyx_22041207_csrRegister csrRegister(clk, csrAddress, rwdata, wMtvec, mtvec_v, wMepc, mepc_v, wMcause, mcause_v, csrWen, mtvec, mepc, mcause, csrReadData);
ysyx_22041207_Memory memory(memoryReadWen, aluRes, r2data, memoryWriteMask, sext, readNum, memoryReadData);
ysyx_22041207_SEXT SEXT(inst, instType, imm);
ysyx_22041207_decoder decoder(inst, imm, r1data, r2data, aluOperate, sel_a, sel_b, memoryWriteMask, 
writeRD, pc_sel, npc_op, writeBackDataSelect, memoryReadWen, sext, readNum, rs1to32, wMtvec, wMepc, wMcause);

ysyx_22041207_alu alu(clk, pc, aluOperate, r1data, r2data, imm, sel_a, sel_b, rs1to32, aluRes);
ysyx_22041207_WB WB(aluRes, pc, memoryReadData, imm, csrReadData, writeBackDataSelect, rwdata);

endmodule

