`timescale 1ns / 1ps

module unblocking1(
        input a,
        input b,
        input c,
        output out1,
        output out2,
        input clk
    );

    reg out1_r;
    reg out2_r;

    reg a_r;
    reg b_r;

    always @(posedge clk) begin
        a_r <= a;
        b_r <= b;
        out1_r <= a_r & b_r;
    end

    always @(*) begin
        out2_r = b & c;
    end

    assign out1 = out1_r;
    assign out2 = out2_r;

endmodule