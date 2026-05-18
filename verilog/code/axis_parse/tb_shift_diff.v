`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/06/15 22:53:53
// Design Name:
// Module Name: tb_shift_diff
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


module tb_shift_diff# (
        parameter integer AXIS_TDATA_WIDTH	= 128
    )();





    reg [AXIS_TDATA_WIDTH-1: 0] input_vec;
    reg [15: 0] input_shift;
    wire [AXIS_TDATA_WIDTH-1: 0] output_vec;


    initial begin
        #10;
        input_vec = 128'hCCCC_AAAA_8888_6666_4444_3333_2222_1111;
        input_shift = 16'h1100;
        #10;
        input_vec = 128'hFFCC_BBAA_8877_6666_5544_3333_3322_2211;
        input_shift = 16'h0011;
        #20;
        $finish;
    end

    shift_diff
        #(
            .AXIS_TDATA_WIDTH (
                AXIS_TDATA_WIDTH )
        )
        shift_diff_dut (
            .input_vec (input_vec ),
            .input_shift (input_shift),
            .output_vec  ( output_vec)
        );

endmodule
