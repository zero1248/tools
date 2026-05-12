`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2025/04/17 02:09:16
// Design Name: 
// Module Name: tb_task
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

typedef reg [31: 0] input_t [127: 0];

module tb_task();

    reg [31: 0] test_data [127: 0];
    integer j;


    initial begin
        for(j=0; j<128; j=j+1) begin
            test_data[j] = j;
        end

        test_task(test_data);
    end
    
    
    task test_task;
        input input_t input_data;
        integer i;
    begin
        for(i=0; i<128; i=i+1) begin
            $display("[%0d]: %h", i, input_data[i])
        end
    end
    endtask
endmodule
