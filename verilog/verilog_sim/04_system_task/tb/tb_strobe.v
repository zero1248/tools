`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/09 21:29:23
// Design Name: 
// Module Name: tb_strobe
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


module tb_strobe();

reg [31: 0] data;
reg clk;

initial begin
    clk = 0;
    data = 0;
    forever #5 clk = ~clk;
end

always @(posedge clk) begin
    if(data != 32'h100)
        data = data + 1;
    else
        data = 0;
end

initial begin
    forever @(negedge clk)
        $strobe ("At time %0d, data is %h", $time, data);
end

initial begin
    #100;
    $finish;
end

endmodule

