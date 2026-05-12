`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/06/05 11:30:20
// Design Name: 
// Module Name: tb_fgetc
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


module tb_fgetc();

    // 从文件中读写相关变量
    integer file_in;
    integer file_length = 0;  // 用于统计输入文件长度

    initial begin      
        $display("Open input file ");
        file_in = $fopen("../test_in.txt", "r");
        if (file_in == 0) begin    // judge file handle
            $fatal("Unable to open input file");
            $finish;
        end
        $display("Open input file done");

        // fgetc 的返回值是 32 位，用 8 位 reg 去接收，就得到低 8 位
        // $display("d: %d.", $signed($fgetc(file_in)));
        // $display("h: %h.", $signed($fgetc(file_in)));
        // $display("d: %d.", $fgetc(file_in));
        // $display("h: %h.", $fgetc(file_in));

        while($signed($fgetc(file_in)) != -1) begin
            file_length = file_length + 1;
        end

        $display("The file length: %d", file_length);

        $finish;
    end

endmodule
