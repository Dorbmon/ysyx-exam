module ysyx_22041207_IF (
    input clk,
    input pc_delay,
    input me_jal,
    input me_jalr,
    input me_branch,
    input pc_panic,
    input [63:0] me_aluRes,
    input [63:0] csr_mtvec,
    input [63:0] me_pc,
    input [63:0] me_imm,
    input [63:0] me_r1data,
    output reg [31:0] inst_o,
    output reg [63:0] pc_o,
    output reg rx_r_valid_i,
    input      rx_r_ready_o,
    input [63:0] rx_data_read_o,
    output reg [63:0] rx_r_addr_i,
    output [7:0] rx_r_size_i,
    input rx_data_valid,
    output reg rx_data_ready
);
wire [63:0] rawData;
wire [31:0] inst;
reg [63:0] pc;
initial begin
    pc = 64'h80000000 - 64'h4;
    rx_r_addr_i = 64'h00000000;
    rx_data_ready = 0;
    rx_r_valid_i = 0;
end
assign rx_r_size_i = 8'b00001111;
// ysyx_22041207_read_mem readInst(pc, 1'b1, rawData);
// assign inst = rawData [31:0];  // 这里可能有BUG
always @(posedge clk) begin
    // 开始读入指令
    if (rx_r_addr_i == pc && rx_data_valid && rx_data_ready) begin
        // 当前pc的指令已经取完了 并且读的是当前应该读的pc(因为中途可能发生了跳转)
        //inst_o <= rawData[31:0];
        //$display("%x %x", rx_r_addr_i, rx_data_read_o[31:0]);
        if (rx_r_addr_i[2:0] == 3'b0) begin
            inst_o <= rx_data_read_o[31:0];
        end else begin
            inst_o <= rx_data_read_o[63:32];
        end
        pc_o <= rx_r_addr_i;
    end else begin
        inst_o <= 0;
        pc_o <= 0;
    end
end
reg axi_finished;
always @(negedge clk) begin
    // 此时pc地址已经确定，可以向axi模块发送地址了
    if (axi_finished || (rx_r_addr_i == 0)) begin    // axi 模块
        rx_data_ready <= 0;
        rx_r_addr_i <= pc;
        rx_r_valid_i <= 1;
        axi_finished <= 0;
        //$display("start to read pc:%x", pc);
    end
    if (rx_r_valid_i && rx_r_ready_o) begin // axi模块已经接收到了地址
        rx_r_valid_i <= 0;
        rx_data_ready <= 1;
    end
    if ((rx_data_valid && rx_data_ready)) begin
        $display("finish read...");
        axi_finished <= 1;
    end
end
always @(posedge clk) begin
    
end
wire [63:0] addRes;
assign addRes = me_r1data + me_imm;
always @(posedge clk) begin
        if (me_jal || (me_branch && me_aluRes == 0)) begin
            //$display("catch jal... %x", me_pc + me_imm);
            pc <= me_pc + me_imm;
        end
        else if (me_jalr) begin // jalr要求最后一位置0
            //(ex_r1data + ex_imm)
            //$display("catch jalr...");
            //$display("jalr %x", {addRes[63:1], 1'b0});
            pc <= {addRes[63:1], 1'b0};
        end
        else if (pc_panic) begin
            $display("pc_panic %x", csr_mtvec);
            pc <= csr_mtvec;
        end else if (~pc_delay  && (pc == rx_r_addr_i)) begin
            $display("update %x", pc + 4);
            // 第二个条件表示当前pc已经处理完成
            pc <= pc + 4;
        end else begin
            pc <= pc;
        end
end
endmodule