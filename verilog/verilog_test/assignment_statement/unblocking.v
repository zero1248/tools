`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/03/22 21:13:58
// Design Name:
// Module Name: blocking
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


module unblocking(
        input a,
        input b,
        // input c,
        output out1,
        // output out2,
        input rst_n,
        input clk
    );

    reg out1_r;
    // reg out2_r;
    reg a_r;
    reg b_r;
    reg c_r;


    always @(posedge clk) begin
        if(!rst_n) begin
            a_r <= 0;
            b_r <= 0;
        end
        else begin
            a_r <= a;
            b_r <= b;
        end
    end

    always @(*) begin

        out1_r = a_r | b_r;
        
    end


    assign out1 = out1_r;











    // always @(posedge clk) begin
    //     a_r <= a;
    //     b_r <= a_r;
    //     c_r <= b_r;
    //     out1_r <= a_r & b_r & c_r;
    // end

    // always @(posedge clk) begin
    //     a_r <= a;
    //     b_r <= b;
    //     out1_r <= a_r & b_r;
    // end






    // always @(*) begin
    //     out2_r = b & c;
    // end

    // assign out1 = out1_r;
    // assign out2 = out2_r;

endmodule
