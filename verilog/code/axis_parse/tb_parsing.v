`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/06/14 21:05:26
// Design Name:
// Module Name: tb_parsing
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


module tb_parsing #(
        C_S_AXIS_TDATA_WIDTH = 128,
        C_M_AXIS_TDATA_WIDTH = 128,
        REG_ADDR_WIDTH = 10,
        REG_DATA_WIDTH = 32
    )
    (
    );

    reg clk;
    reg rst_n;

    wire saxis_tready;
    reg saxis_tvalid;
    reg saxis_tlast;
    reg    [C_S_AXIS_TDATA_WIDTH-1 : 0] saxis_tdata;



    reg  ready_from_algo;
    wire [C_S_AXIS_TDATA_WIDTH-1 : 0] data_to_algo;
    wire valid_to_algo;
    wire last_to_algo;
    wire calc_start;
    wire calc_pm_wr;
    wire calc_pm_rd;
    reg  calc_done;

    wire [REG_ADDR_WIDTH-1 : 0]  reg_addr;
    wire [REG_DATA_WIDTH-1 : 0] data_to_reg;
    wire reg_rd;
    wire reg_wr;
    reg  reg_rd_done;
    reg  reg_wr_done;

    localparam CLK_PERIOD = 10;

    initial begin
        clk = 1;
        forever #(CLK_PERIOD/2)
            clk = ~clk;
    end


    initial begin
        rst_n = 0;
        #50;
        rst_n = 1;
    end

    initial begin
        saxis_tvalid = 1'b0;
        saxis_tlast = 1'b0;
        saxis_tdata = {128{1'b0}};
        #50;
        saxis_tvalid = 1'b1;
        saxis_tlast = 1'b0;

        // 帧头：
        // saxis_tdata = {8'h01, 8'h03, 8'h05, 8'h00, 64'h0000_0000_0000_0000, 32'h0004};
        saxis_tdata = {32'h0004, 64'h0000_0000_0000_0000, 8'h00, 8'h05, 8'h03, 8'h01};
        #10;
        // 第二个周期不变或者全 0
        saxis_tdata = {128{1'b0}};
        #10;
        // 数据：
        saxis_tdata = {32{4'h1}};
        #10;
        saxis_tdata = {32{4'h2}};
        #10;
        saxis_tdata = {32{4'h4}};
        #10;
        saxis_tdata = {32{4'h8}};
        saxis_tlast = 1'b1;
        #10;
        saxis_tdata = {128{1'b0}};
        saxis_tvalid = 1'b0;
        saxis_tlast = 1'b0;
        #10;
        $finish;


    end






    parsing
        #(
            .C_S_AXIS_TDATA_WIDTH(C_S_AXIS_TDATA_WIDTH ),
            .C_M_AXIS_TDATA_WIDTH(C_M_AXIS_TDATA_WIDTH ),
            .REG_ADDR_WIDTH(REG_ADDR_WIDTH ),
            .REG_DATA_WIDTH (REG_DATA_WIDTH )
        )
        parsing_dut (
            .clk (clk ),
            .rst_n (rst_n ),

            .saxis_tready (saxis_tready ),
            .saxis_tvalid (saxis_tvalid ),
            .saxis_tlast (saxis_tlast ),
            .saxis_tdata (saxis_tdata ),

            .ready_from_algo (ready_from_algo ),
            .data_to_algo (data_to_algo ),
            .valid_to_algo (valid_to_algo ),
            .last_to_algo (last_to_algo ),
            .calc_start (calc_start ),
            .calc_pm_wr (calc_pm_wr ),
            .calc_pm_rd (calc_pm_rd ),
            .calc_done (calc_done ),

            .reg_addr (reg_addr ),
            .data_to_reg (data_to_reg ),
            .reg_rd (reg_rd ),
            .reg_wr (reg_wr ),
            .reg_rd_done (reg_rd_done ),
            .reg_wr_done  ( reg_wr_done)
        );







endmodule
