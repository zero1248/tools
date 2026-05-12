`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2023/06/05 22:29:11
// Design Name:
// Module Name: tb_dynamic_slice
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


module tb_dynamic_slice #(
        parameter integer AXIS_TDATA_WIDTH	= 64
    )();

    reg [AXIS_TDATA_WIDTH-1: 0] in_data;
    reg [AXIS_TDATA_WIDTH-1: 0] out_data;


    // 大小端转换
    function [AXIS_TDATA_WIDTH-1: 0] endian_trans(input [AXIS_TDATA_WIDTH-1: 0] data);
        integer i;
        reg [7: 0] tmp;
        begin
            i = 0;
            while(i < (AXIS_TDATA_WIDTH)/8/2) begin
                $display("i= %d", i);
                $display("data[(i*8)+: 8]: %h", data[(i*8)+: 8]);
                $display("data[(AXIS_TDATA_WIDTH-1 -i*8)-: 8]: %h", data[(AXIS_TDATA_WIDTH-1 -i*8)-: 8]);
                tmp = data[(i*8)+: 8];
                data[(i*8)+: 8] = data[(AXIS_TDATA_WIDTH-1 -i*8)-: 8];
                data[(AXIS_TDATA_WIDTH-1 -i*8)-: 8] = tmp;
                i = i + 1;
            end
            endian_trans = data;
        end
    endfunction





    initial begin

        in_data = {8'h01, 8'h02, 8'h03, 8'h04, 8'h11, 8'h12, 8'h13, 8'h14};
        $display("in_data[7: 0]: %h", in_data[7: 0]);
        $display("in_data[15: 8]: %h", in_data[15: 8]);
        $display("in_data[23: 16]: %h", in_data[23: 16]);
        $display("in_data[31: 24]: %h", in_data[31: 24]);
        $display("in_data[39: 32]: %h", in_data[39: 32]);
        $display("in_data[47: 40]: %h", in_data[47: 40]);
        $display("in_data[55: 48]: %h", in_data[55: 48]);
        $display("in_data[63: 56]: %h", in_data[63: 56]);

        out_data = endian_trans(in_data);

        $display("out_data[7: 0]: %h", out_data[7: 0]);
        $display("out_data[15: 8]: %h", out_data[15: 8]);
        $display("out_data[23: 16]: %h", out_data[23: 16]);
        $display("out_data[31: 24]: %h", out_data[31: 24]);
        $display("out_data[39: 32]: %h", out_data[39: 32]);
        $display("out_data[47: 40]: %h", out_data[47: 40]);
        $display("out_data[55: 48]: %h", out_data[55: 48]);
        $display("out_data[63: 56]: %h", out_data[63: 56]);

        $finish;

    end


endmodule
