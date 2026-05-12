`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/10 02:56:56
// Design Name: 
// Module Name: tb_multi_block_monitor
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module tb_multi_block_monitor();
reg [31: 0] data1;
reg [31: 0] data2;
reg clk;

initial begin
    clk = 0;
    data1 = 0;
    data2 = 0;
    forever #5 clk = ~clk;
end

initial begin
    #10;
    $monitor("monitor 01: At time %0d, data1=%0d", $time, data1);

    #20;
    data1 = 10;

    #30;
    data1 = 20;

    #10;
    data1 = 30;
end

initial begin
    #10;
    $monitor("monitor 02: At time %0d, data2=%0d", $time, data2);

    #20;
    data2 = 10;

    #30;
    data2 = 20;

    #10;
    data2 = 30;

    #30;
    $finish;
end



endmodule
