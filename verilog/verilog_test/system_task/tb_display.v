`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/09 16:52:38
// Design Name: 
// Module Name: tb_sys_task
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


module tb_display();

reg [31: 0] in1;
reg [31: 0] in2;
reg [31: 0] out;
reg clk;
wire wire_sgn;

assign wire_sgn = out;

initial begin
    clk = 0;
    forever #5 clk = ~clk;
end

initial begin

    in1 = 32'd33;
    in2 = 32'd34;
    out = 32'd35;
    
    $display("in1 = %b, in2 = %b and out = %b", in1, in2, out);
    $display("in1 = %o, in2 = %o and out = %o", in1, in2, out);
    $display("in1 = %d, in2 = %d and out = %d", in1, in2, out);
    $display("in1 = %h, in2 = %h and out = %h", in1, in2, out);
    $display("in1 = %c, in2 = %c and out = %c", in1, in2, out);
    $display("in1 = %e, in2 = %e and out = %e", in1, in2, out);
    $display("in1 = %f, in2 = %f and out = %f", in1, in2, out);
    $display("in1 = %g, in2 = %g and out = %g", in1, in2, out);
    $display("%m");
    $display("wire signal strength = %m", wire_sgn);

    $display("\n \t \\ \" \043 %%");

    $display("cur time = %t", $time);
    $write("cur time = %t", $time);

    forever @(negedge clk)
        $strobe ("At time %d, data is %h",$time,data);

    $finish;
end

endmodule
