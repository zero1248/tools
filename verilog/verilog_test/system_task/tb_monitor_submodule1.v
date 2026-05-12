`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/10 22:23:18
// Design Name: 
// Module Name: tb_monitor_submodule1
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


module tb_monitor_submodule1(
    input wire clk,
    input wire [31: 0] data
);

initial begin
    $monitor("sub1 @ %t: data = %0d", $time, data);
end

endmodule
