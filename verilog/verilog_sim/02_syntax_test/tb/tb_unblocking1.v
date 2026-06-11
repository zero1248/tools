`timescale 1ns / 1ps

module tb_unblocking1();

    // Ports
    reg a = 0;
    reg b = 0;
    reg c = 0;
    wire out1;
    wire out2;
    reg clk = 0;

    initial begin
        $monitor("[%0t]: a=%0b b=%0b c=%0b out1=%0b out2=%0b", $time, a, b, c, out1, out2);
    end

    initial begin
        $dumpfile("wave/tb_unblocking1.vcd");
        $dumpvars(0, tb_unblocking1);
    end

    unblocking1
        inst_unblocking1 (
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
            #30;
            a = 1;
            b = 1;
            c = 1;
            #50;
            a = 0;
            b = 0;
            c = 0;
            #50;
            $finish;
        end
    end

    always
        #5  clk = ! clk ;

endmodule