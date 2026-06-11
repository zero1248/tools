module unblocking_ifelse0(
    input a,
    input b,
    input c,
    output out1,
    output out2,
    input clk
);

reg out1_r;
reg out2_r;

// 非阻塞
always @(posedge clk) begin
    if(c)
        out1_r <= a | b;
    else begin
        out1_r <= 1'b0;
    end
end
// 阻塞
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