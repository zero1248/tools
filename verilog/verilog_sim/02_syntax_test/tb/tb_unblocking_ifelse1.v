`timescale 1ns / 1ps

module tb_unblocking_ifelse1;

    // Ports
    reg a = 0;
    reg b = 0;
    reg c = 0;
    wire out1;
    wire out2;
    reg clk = 0;

    initial begin
        $dumpfile("wave/tb_unblocking_ifelse1.vcd");
        $dumpvars(0, tb_unblocking_ifelse1);
    end

    unblocking_ifelse1
        inst_unblocking_ifelse1 (
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
