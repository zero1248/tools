`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/03/23 16:11:35
// Design Name: 
// Module Name: unblocking_lock
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

// 阻塞赋值与非阻塞赋值生成的电路相同，应该是 vivado 做了优化

module unblocking_lock(
    output reg out1,
    output reg out2,
    input clk,
    input rst_n
);

always @(posedge clk) begin
    if(!rst_n)
        out1 = 1'b0;
    else
        out1 = out2;
end

always @(posedge clk) begin
    if(!rst_n)
        out2 = 1'b1;
    else
        out2 = out1;
end

endmodule
