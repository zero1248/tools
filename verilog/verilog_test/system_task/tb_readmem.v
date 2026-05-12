`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/14 09:43:02
// Design Name: 
// Module Name: tb_readmem
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


module tb_readmem();

reg [63: 0] mem_1[9: 0];
reg [31: 0] mem_2[9: 0];

initial begin
    #10;
    $readmemh("./test_readmem.hex", mem_1);
    $display("mem_1 read data: %h", mem_1[0]); // 此处不能直接用 mem_1 作为参数
    $display("mem_1 read data: %h", mem_1[1]);
    $display("mem_1 read data: %h", mem_1[2]);
    $display("mem_1 read data: %h", mem_1[3]);
    $display("mem_1 read data: %h", mem_1[4]);
    $display("mem_1 read data: %h", mem_1[5]);

    $readmemh("./test_readmem.hex", mem_2);
    $display("mem_2 read data: %h", mem_2[0]); // 此处不能直接用 mem_2 作为参数
    $display("mem_2 read data: %h", mem_2[1]);
    $display("mem_2 read data: %h", mem_2[2]);
    $display("mem_2 read data: %h", mem_2[3]);
    $display("mem_2 read data: %h", mem_2[4]);
    $display("mem_2 read data: %h", mem_2[5]);

end

endmodule
