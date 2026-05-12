module tb_monitor_topmodule();

reg clk;
reg [31:0] data;

initial begin
    clk = 0;
    forever #5
        clk = ~clk;
end

tb_monitor_submodule1 sub1(
    .clk(clk),
    .data(data)
);

tb_monitor_submodule2 sub2(
    .clk(clk),
    .data(data)
);

initial begin
    #10;
    data = 10;
    #10;
    data = 20;
    #10;
    data = 30;
    #10;
    data = 40;
    #10;
    data = 50;
    #10;
    data = 60;
    #10;
    data = 70;
end

endmodule