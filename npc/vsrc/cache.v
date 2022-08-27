module ysyx_22041207_cache (
    input clk,
    input rst,
    input [63:0] readAddress,
    output readHit,
    output [63:0] readData,
    input wUpdateData,
    input [63:0] wUpdateAddress,
    input [63:0] wActualData,
    input [7:0] wMask,
    input updateData,
    input [63:0] updateAddress,
    input [63:0] actualData // 更新的数据 (地址也是readAddress)
);
reg [63:0] way0[0:3], way1[0:3];
reg [58:0] tag0[0:3], tag1[0:3];
reg lastWrite [0:3];
wire [1:0] index = readAddress[4:3];
reg  valid0[0:3], valid1[0:3];
wire [58:0] tag = readAddress[63:5];
wire [63:0] read0 = way0[index];
wire available0 = (valid0[index] && (tag0[index] == tag));

wire [63:0] read1 = way1[index];
wire available1 = (valid1[index] && (tag1[index] == tag));

//assign readHit = (available0 | available1);
//assign readData = available0 ? read0 : (available1 ? read1 : 0);
assign readHit = (tag0[index] == tag);
assign readData = read0;


wire [58:0] wtag = updateAddress [63:5];
wire [1:0]  windex = updateAddress [4:3];
wire [58:0] wwtag = wUpdateAddress [63:5];
wire [1:0]  wwindex = wUpdateAddress [4:3];
initial begin
    integer i;
    for (i = 0;i < 4;i ++) begin
        valid0 [i] = 0;
        valid1 [i] = 0;
        lastWrite [i] = 0;
    end
end
always @(posedge clk) begin
    if (rst) begin
        integer i;
        for (i = 0;i < 4;i ++) begin
            valid0 [i] <= 0;
            valid1 [i] <= 0;
            lastWrite [i] <= 0;
        end
    end
    else begin
        if (updateData) begin
            tag0 [windex] <= wtag;
            way0 [windex] <= actualData;
            //valid0 [windex] <= 1;
        end
        if (wUpdateData) begin
            valid0 [wwindex] <= 0;
        end
        // if (updateData) begin   //读更新
        //     //$display("r");
        //     if ((lastWrite[windex] || tag0 [windex] == wtag) && tag1 [windex] != wtag) begin
        //         // 那就写0
        //         way0 [windex] <= actualData;
        //         tag0 [windex] <= wtag;
        //         valid0 [windex] <= 1;
        //     end else begin
        //         way1 [windex] <= actualData;
        //         tag1 [windex] <= wtag;
        //         valid1 [windex] <= 1;
        //     end
        //     lastWrite [windex] <= ~lastWrite [windex];
        // end
        // if (wUpdateData) begin
        //    // valid0 [wwindex] <= 0;
        //    // valid1 [wwindex] <= 0;
        //     if ((lastWrite[wwindex] || tag0 [wwindex] == wwtag) && tag1 [wwindex] != wwtag) begin
        //         // 那就写0
        //         tag0 [wwindex] <= wwtag;
        //         way0[wwindex][7: 0] <= wMask[0] ? wActualData [7: 0] : way0 [wwindex][7: 0];
        //         way0[wwindex][15: 8] <= wMask[1] ? wActualData [15: 8] : way0 [wwindex][15: 8];
        //         way0[wwindex][23: 16] <= wMask[2] ? wActualData [23: 16] : way0 [wwindex][23: 16];
        //         way0[wwindex][31: 24] <= wMask[3] ? wActualData [31: 24] : way0 [wwindex][31: 24];
        //         way0[wwindex][39: 32] <= wMask[4] ? wActualData [39: 32] : way0 [wwindex][39: 32];
        //         way0[wwindex][47: 40] <= wMask[5] ? wActualData [47: 40] : way0 [wwindex][47: 40];
        //         way0[wwindex][55: 48] <= wMask[6] ? wActualData [55: 48] : way0 [wwindex][55: 48];
        //         way0[wwindex][63: 56] <= wMask[7] ? wActualData [63: 56] : way0 [wwindex][63: 56];
        //     end else begin
        //         tag1 [wwindex] <= wwtag;
        //         way1[wwindex][7: 0] <= wMask[0] ? wActualData [7: 0] : way1 [wwindex][7: 0];
        //         way1[wwindex][15: 8] <= wMask[1] ? wActualData [15: 8] : way1 [wwindex][15: 8];
        //         way1[wwindex][23: 16] <= wMask[2] ? wActualData [23: 16] : way1 [wwindex][23: 16];
        //         way1[wwindex][31: 24] <= wMask[3] ? wActualData [31: 24] : way1 [wwindex][31: 24];
        //         way1[wwindex][39: 32] <= wMask[4] ? wActualData [39: 32] : way1 [wwindex][39: 32];
        //         way1[wwindex][47: 40] <= wMask[5] ? wActualData [47: 40] : way1 [wwindex][47: 40];
        //         way1[wwindex][55: 48] <= wMask[6] ? wActualData [55: 48] : way1 [wwindex][55: 48];
        //         way1[wwindex][63: 56] <= wMask[7] ? wActualData [63: 56] : way1 [wwindex][63: 56];
        //     end
        //     lastWrite [wwindex] <= ~lastWrite [wwindex];
        // end
    end
end
endmodule