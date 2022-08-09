module ysyx_22041207_top (
  input clk,
  //input [31:0] inst,
  output reg [63:0] pc
);

wire [4:0] r1addr,r2addr,rwaddr;
wire [63:0] r1data,r2data,rwdata;
wire writeRD;
ysyx_22041207_RegisterFile #(32, 5, 64) r(clk, stage, rwdata, rwaddr, r1addr, r1data, r2addr, r2data, writeRD);
//reg [63:0] pc;
initial begin
  pc = 64'h80000000;
end
wire [63:0] imm;
wire pc_sel, npc_op;
wire [1:0] sel_a, sel_b;
wire [63:0] npc;


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
assign csrAddress = imm[11:0];
wire csrWen;
wire [63:0] mtvec, mepc, mcause, mstatus, csrReadData;
wire wMtvec, wMepc, wMcause, wMstatus;
wire [63:0] mtvec_v, mepc_v, mcause_v, mstatus_v;
assign mepc_v = pc + 64'h4; // mepc永远是写入pc
wire pc_panic, pc_mret;
wire [2:0] stage;
ysyx_22041207_IF rif(clk, stage, pc, inst);
wire [31:0] inst;
always @(posedge clk) begin
  if (stage == 3'h4) begin
    pc <= npc;
  end
end
assign r1addr = inst [19:15];
assign r2addr = inst [24:20];
assign rwaddr = inst [11:7]; 
ysyx_22041207_stageManager stageManager(clk, stage);
ysyx_22041207_GetPC getPc(imm, r1data, pc_sel, npc_op, pc, pc_panic, pc_mret, mtvec, mepc, npc);
ysyx_22041207_csrRegister csrRegister(clk, pc_mret, csrAddress, aluRes, wMtvec, mtvec_v, wMepc, mepc_v, 
wMcause, mcause_v, wMstatus, mstatus_v, csrWen, mtvec, mepc, mcause, mstatus, csrReadData);
ysyx_22041207_Memory memory(clk, stage, memoryReadWen, aluRes, r2data, memoryWriteMask, sext, readNum, memoryReadData);
ysyx_22041207_SEXT SEXT(inst, instType, imm);
ysyx_22041207_decoder decoder(clk, stage, inst, imm, r1data, r2data, aluOperate, sel_a, sel_b, memoryWriteMask, 
writeRD, pc_sel, npc_op, writeBackDataSelect, memoryReadWen, sext, readNum, rs1to32, wMtvec, wMepc, wMcause, wMstatus, pc_panic, pc_mret, csrWen);

ysyx_22041207_alu alu(pc, aluOperate, r1data, r2data, csrReadData, imm, sel_a, sel_b, rs1to32, aluRes);
ysyx_22041207_WB WB(aluRes, pc, memoryReadData, imm, csrReadData, writeBackDataSelect, rwdata);

endmodule

