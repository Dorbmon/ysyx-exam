module top(x,e,y,indicator);
input [7:0] x;
input e;
output reg [2:0] y;
output reg indicator;
integer i;
always @(x or e) begin
  y = 0;
  indicator = 0;
  if (e) begin
    for (i = 0;i <= 7;i ++) begin
      if(x[i] == 1) begin
        y = i[2:0];
      end
    end
    if (y == 3'b000)
      indicator = 0;
    else
      indicator = 1;
  end 
  else begin
    y = 0;
  end
end 
endmodule