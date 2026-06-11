`timescale 1ns / 1ps


module adder4b_full #(parameter WIDTH = 4) (
    input  [WIDTH-1: 0] a,
    input  [WIDTH-1: 0] b,
    input  cin,
    output [WIDTH-1: 0] sum,
    output cout
);
    wire [WIDTH: 0] carry;

    assign carry[0] = cin;
    assign cout = carry[WIDTH];

    // generate for 的循环变量 i 用 genvar 定义
    genvar i;
    generate
        for (i = 0; i < WIDTH; i = i + 1) begin : adder_loop
            adder1b_full inst_adder1b_full (
                .a(a[i]),
                .b(b[i]),
                .cin(carry[i]),
                .sum(sum[i]),
                .cout(carry[i+1])
            );
        end
    endgenerate
endmodule 


