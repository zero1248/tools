`timescale 1ns / 1ps

module unblocking_ifelse2(
    input a,
    input b,
    input c,
    output out1,
    output out2,
    input clk
);

reg a_r;
reg b_r;
// reg c_r;
reg out1_r;
reg out2_r;


always @(posedge clk) begin
    if(c) begin
        a_r <= a;
        b_r <= b;
    end
    else begin
        a_r <= 1'b0;
        b_r <= 1'b0;        
    end
    out1_r <= a_r | b_r;
end

always @(*) begin
    if(c)
        out2_r = a | b;
    else begin
        out2_r = 1'b0;
    end
end

assign out1 = out1_r;
assign out2 = out2_r;

endmodule
