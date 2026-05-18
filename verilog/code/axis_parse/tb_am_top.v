`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/06/22 23:39:25
// Design Name:
// Module Name: tb_am_top
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

module tb_am_top;

    // Parameters
    localparam integer AXIS_TDATA_WIDTH = 128;
    localparam integer REG_ADDR_WIDTH = 10;
    localparam integer REG_DATA_WIDTH = 32;

    // Ports
    reg  clk = 0;
    reg  rst_n = 0;

    wire  S_AXIS_TREADY;
    reg [AXIS_TDATA_WIDTH-1 : 0] S_AXIS_TDATA;
    reg  S_AXIS_TLAST;
    reg  S_AXIS_TVALID;

    wire  M_AXIS_TVALID;
    wire [AXIS_TDATA_WIDTH-1 : 0] M_AXIS_TDATA;
    wire  M_AXIS_TLAST;
    reg  M_AXIS_TREADY;

    am_top
        #(
            .AXIS_TDATA_WIDTH(AXIS_TDATA_WIDTH ),
            .REG_ADDR_WIDTH(REG_ADDR_WIDTH ),
            .REG_DATA_WIDTH(REG_DATA_WIDTH )
        )
        am_top_dut (
            .clk (clk ),
            .rst_n (rst_n ),

            .S_AXIS_TREADY (S_AXIS_TREADY ),
            .S_AXIS_TDATA (S_AXIS_TDATA ),
            .S_AXIS_TLAST (S_AXIS_TLAST ),
            .S_AXIS_TVALID (S_AXIS_TVALID ),

            .M_AXIS_TVALID (M_AXIS_TVALID ),
            .M_AXIS_TDATA (M_AXIS_TDATA ),
            .M_AXIS_TLAST (M_AXIS_TLAST ),
            .M_AXIS_TREADY  ( M_AXIS_TREADY)
        );

    localparam CLK_PERIOD = 10;

    reg [7: 0] src;
    reg [7: 0] dst;
    reg [7: 0] opt;
    reg [7: 0] tsk;
    reg [63: 0] addr;
    reg [31: 0] len;

    initial begin
        clk = 1;
        forever
            #(CLK_PERIOD/2)
             clk = ~clk;
    end


    initial begin
        rst_n = 0;
        #50;
        rst_n = 1;
    end


    initial begin
        M_AXIS_TREADY = 1'b1;
        S_AXIS_TVALID = 1'b0;
        S_AXIS_TLAST = 1'b0;
        S_AXIS_TDATA = {128{1'b0}};
        #50;
        S_AXIS_TVALID = 1'b1;
        S_AXIS_TLAST = 1'b0;

        // 帧头：
        src = 8'h01;
        dst = 8'h03;
        opt = 8'h05;
        tsk = 8'h00;
        addr = 64'h0000_0000_0000_0000;
        len = 32'h0006;
        // 第一笔
        S_AXIS_TDATA = {len, addr, tsk, opt, dst, src};
        #10;
        // 第二笔，不变或者全 0
        S_AXIS_TDATA = {128{1'b0}};
        #10;

        // 数据：
        S_AXIS_TDATA = 128'h0000_AAAA_8888_6666_4444_3333_2222_1111;
        #10;
        S_AXIS_TDATA = 128'hFFCC_BBAA_8877_6666_5544_3333_3322_2211;
        #10;
        S_AXIS_TDATA = 128'hFFCC_BBAA_8877_6666_5544_3333_3322_2211;
        #10;
        S_AXIS_TDATA = 128'h0000_AAAA_8888_6666_4444_3333_2222_0000;
        #10;
        S_AXIS_TDATA = 128'h0000_AAAA_8888_6666_4444_3333_2222_2222;
        #10;
        S_AXIS_TDATA = 128'h0000_AAAA_8888_6666_4444_3333_2222_1111;
        S_AXIS_TLAST = 1'b1;
        #10;
        S_AXIS_TDATA = {128{1'b0}};
        S_AXIS_TVALID = 1'b0;
        S_AXIS_TLAST = 1'b0;
        #200;
        $finish;
    end


endmodule


