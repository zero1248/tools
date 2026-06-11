`timescale 1ns / 1ps

module adder1b_full(
    input a,
    input b,
    input cin,
    output sum,
    output cout
); 

    assign sum = a ^ b ^ cin;
    assign cout = (a & b) | (b & cin) | (a & cin);
    // assign {cout, sum} = a + b + cin;


endmodule


