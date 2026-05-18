`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/06/16 00:14:24
// Design Name:
// Module Name: tb_algo_module
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


module tb_algo_module# (
        parameter integer AXIS_TDATA_WIDTH	= 128,
        parameter integer REG_ADDR_WIDTH	= 10,
        parameter integer REG_DATA_WIDTH	= 32
    )();

    reg clk;
    reg rst_n;

    wire ready_to_parsing;
    reg [AXIS_TDATA_WIDTH-1 : 0] data_from_parsing;
    reg valid_from_parsing;
    reg last_from_parsing;

    reg calc_start;
    reg calc_pm_wr;
    reg calc_pm_rd;
    reg trans_continue;
    wire calc_done;

    wire [REG_ADDR_WIDTH-1 : 0] reg_addr;
    wire [REG_DATA_WIDTH-1 : 0] data_to_reg;
    wire [REG_DATA_WIDTH-1 : 0] data_from_reg;
    wire rd_reg;
    wire wr_reg;
    reg rd_reg_done;
    reg wr_reg_done;

    wire [AXIS_TDATA_WIDTH-1 : 0] data_to_framing;
    wire valid_to_framing;
    wire last_to_framing;
    reg ready_from_framing;

    localparam CLK_PERIOD = 10;


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
        valid_from_parsing = 1'b0;
        last_from_parsing = 1'b0;
        data_from_parsing = {128{1'b0}};
        ready_from_framing = 1'b1;
        #50;

        valid_from_parsing = 1'b1;
        last_from_parsing = 1'b0;

        data_from_parsing = 128'h0000_AAAA_8888_6666_4444_3333_2222_1111;
        #10;

        data_from_parsing = 128'hFFCC_BBAA_8877_6666_5544_3333_3322_2211;
        #10;

        data_from_parsing = 128'hFFCC_BBAA_8877_6666_5544_3333_3322_2211;
        last_from_parsing = 1'b1;
        #10;

        data_from_parsing = {128{1'b1}};
        valid_from_parsing = 1'b0;
        last_from_parsing = 1'b0;
        #10;
        $finish;

    end





    algo_module
        #(
            .AXIS_TDATA_WIDTH(AXIS_TDATA_WIDTH ),
            .REG_ADDR_WIDTH(REG_ADDR_WIDTH ),
            .REG_DATA_WIDTH (REG_DATA_WIDTH )
        )
        algo_module_dut (
            .clk (clk ),
            .rst_n (rst_n ),
            .ready_to_parsing (ready_to_parsing ),
            .data_from_parsing (data_from_parsing ),
            .valid_from_parsing (valid_from_parsing ),
            .last_from_parsing (last_from_parsing ),
            .calc_start (calc_start ),
            .calc_pm_wr (calc_pm_wr ),
            .calc_pm_rd (calc_pm_rd ),
            .trans_continue (trans_continue ),
            .calc_done (calc_done ),
            .reg_addr (reg_addr ),
            .data_to_reg (data_to_reg ),
            .data_from_reg (data_from_reg ),
            .rd_reg (rd_reg ),
            .wr_reg (wr_reg ),
            .rd_reg_done (rd_reg_done ),
            .wr_reg_done (wr_reg_done ),
            .data_to_framing (data_to_framing ),
            .valid_to_framing (valid_to_framing ),
            .last_to_framing (last_to_framing ),
            .ready_from_framing  ( ready_from_framing)
        );



endmodule
