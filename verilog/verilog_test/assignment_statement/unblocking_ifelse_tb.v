`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/03/23 09:33:57
// Design Name:
// Module Name: unblocking_ifelse_tb
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


module unblocking_ifelse_tb;

    // Ports
    reg a = 0;
    reg b = 0;
    reg c = 0;
    wire out1;
    wire out2;
    reg clk = 0;

    unblocking_ifelse
        unblocking_ifelse_dut (
            .a (a ),
            .b (b ),
            .c (c ),
            .out1 (out1 ),
            .out2 (out2 ),
            .clk  ( clk)
        );

    initial begin
        begin
            a = 0;
            b = 0;
            c = 0;
            #20;
            a = 1;
            b = 0;
            c = 1;
            #20;
            a = 0;
            b = 0;
            c = 0;
            #20;
            a = 0;
            b = 1;
            c = 1;
            #20;      
            $finish;
        end
    end

    always
        #5  clk = ! clk ;

endmodule
