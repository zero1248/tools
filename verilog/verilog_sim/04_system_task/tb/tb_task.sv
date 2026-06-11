`timescale 1ns / 1ps

module tb_task();

    reg [31:0] test_data [0:127];
    integer j;

    initial begin
        for (j = 0; j < 128; j = j + 1) begin
            test_data[j] = j;
        end

        test_task();
    end

    task test_task;
        integer i;
        begin
            for (i = 0; i < 128; i = i + 1) begin
                $display("[%0d]: %h", i, test_data[i]);
            end
        end
    endtask

endmodule