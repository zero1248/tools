`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/03/23 16:17:42
// Design Name:
// Module Name: unblocking_lock_tb
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

module unblocking_lock_tb;

    // Parameters

    // Ports
    wire out1;
    wire out2;
    reg clk = 0;
    reg rst_n = 0;

    unblocking_lock
        unblocking_lock_dut (
            .out1 (out1 ),
            .out2 (out2 ),
            .clk (clk ),
            .rst_n  ( rst_n)
        );

    initial begin
        rst_n = 0;
        #30;
        rst_n = !rst_n;
        #30;
        rst_n = !rst_n;
        #30;
        rst_n = !rst_n;
        
        $finish;
        
    end

    always
        #5  clk = ! clk ;

endmodule


