`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/06/15 22:16:28
// Design Name:
// Module Name: shift_diff
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


module shift_diff# (
        parameter integer AXIS_TDATA_WIDTH	= 128
    )(
        input wire [AXIS_TDATA_WIDTH-1: 0] input_vec,
        input wire [15 : 0] input_shift,
        output wire [AXIS_TDATA_WIDTH-1: 0] output_vec
    );

    genvar i;
    generate
        for (i=0; i < AXIS_TDATA_WIDTH/16; i=i+1) begin: calc_loop
            if(i==0)
                assign output_vec[(i+1)*16-1: i*16] = input_vec[(i+1)*16-1: i*16] - input_shift[15: 0];
            else
                assign output_vec[(i+1)*16-1: i*16] = input_vec[(i+1)*16-1: i*16] - input_vec[i*16-1: (i-1)*16];
        end
    endgenerate
endmodule
