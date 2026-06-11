module unblocking_ifelse1(
    input a,
    input b,
    input c,
    output out1,
    output out2,
    input clk
);

reg out1_r;
reg out2_r;
reg c_r;

// 非阻塞
always @(posedge clk) begin
    c_r <= c;
end

always @(posedge clk) begin
    if(c_r)
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