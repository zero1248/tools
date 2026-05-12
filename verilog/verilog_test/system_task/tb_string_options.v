`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/04/13 03:06:15
// Design Name:
// Module Name: tb_string_options
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


module tb_string_options();

    reg [299: 0] str_swrite;
    reg [299: 0] str_sformat;
    reg [63: 0] str_temp;
    integer len = 111;

    initial begin
        str_temp = "testStr";

        $swrite(str_swrite, "%s's length is %d", str_temp, len);
        $display("%s", str_swrite);
        $swrite(str_swrite, "abc", , 123);
        $display("%s", str_swrite);

        $sformat(str_sformat, "test: %s", str_temp);
        $display("%s", str_sformat);
        $sformat(str_sformat, "abc %d", 123);
        $display("%s", str_sformat);
        $sformat(str_sformat, "abc");
        $display("%s", str_sformat);
        $sformat(str_sformat, "abc", , 123);
        $display("%s", str_sformat);
    end

endmodule
