`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/04/12 17:16:17
// Design Name:
// Module Name: tb_file_options
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


module tb_file_options();

    integer fd;
    integer err;
    reg [639: 0] str;

    initial begin
        fd = $fopen("data/file_io_test.txt", "a+");
        err = $ferror(fd, str);
        if (!err) begin
            $fdisplay(fd, "fd: %h", fd);
            $fdisplay(fd, "str: %h", str);
            $fdisplay(fd, "err: %h", err);
            $fwrite(fd, "fd: %h   ", fd);
            $fwrite(fd, "str: %h   ", str);
            $fwrite(fd, "err: %h   ", err);
            $fdisplay(fd, "fd: %d", $signed(fd));
        end
        $fclose(fd);
    end

endmodule
