`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/04/19 10:02:26
// Design Name:
// Module Name: generate_for
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


module generate_for # (
        parameter N = 32
    )

    (
        output [N-1: 0] out,
        input  [N-1: 0]  i0,
        input  [N-1: 0]  i1
    );

    genvar j;

    generate
        for(j=0; j<N; j=j+1) begin : xor_loop
            xor g1(out[j], i0[j], i1[j]);
        end
    endgenerate

endmodule
