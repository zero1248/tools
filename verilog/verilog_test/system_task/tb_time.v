`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/11 10:03:12
// Design Name: 
// Module Name: tb_time
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


module tb_time();

reg [31: 0] data;

initial begin
    data = 0;
    $display($time, , "display1 data = ", data);
    $display("display2 @ %d, data = %d", $time,  data);
    $monitor($time, , "monitor1 data = ", data);
    $monitor("monitor2 @ %d, data = %d", $time,  data);

    #10;
    data = 10;

    #10;
    $finish;
end

endmodule
