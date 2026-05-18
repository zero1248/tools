`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/06/17 03:35:30
// Design Name:
// Module Name: tb_framing
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

module tb_framing;

    // Parameters
    localparam integer AXIS_TDATA_WIDTH = 128;
    localparam integer REG_ADDR_WIDTH = 10;
    localparam integer REG_DATA_WIDTH = 32;

    // Ports
    reg  clk = 0;
    reg  rst_n = 0;

    reg [7 : 0] dest_algo;
    reg [7 : 0] opt_algo;
    reg [7 : 0] task_algo;
    reg [63 : 0] addr_algo;
    reg [31: 0] len_algo;
    reg [AXIS_TDATA_WIDTH-1 : 0] data_from_algo;
    reg  valid_from_algo = 0;
    reg  last_from_algo = 0;
    wire  ready_to_algo;

    reg [7 : 0] dest_reg;
    reg [7 : 0] opt_reg;
    reg [7 : 0] task_reg;
    reg [REG_DATA_WIDTH-1 : 0] data_from_reg;
    reg  valid_from_reg = 0;

    reg  maxis_tready = 0;
    wire  maxis_tvalid;
    wire  maxis_tlast;
    wire [AXIS_TDATA_WIDTH-1 : 0] maxis_tdata;

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
        
        data_from_algo = {128{1'b0}};
        valid_from_algo = 1'b0;
        last_from_algo = 1'b0;
        #50;
        dest_algo = 8'h01; // PM
        opt_algo = 8'h04;   // OPT_PM_RD_DM
        task_algo = 8'h0;
        addr_algo = 64'h0;
        len_algo = 32'h4;
        data_from_algo = {32{4'h1}};  // data1
        valid_from_algo = 1'b1;
        #10;
        data_from_algo = {32{4'h2}};  // data2
        #10;
        data_from_algo = {32{4'h4}};  // data3
        #10;
        data_from_algo = {32{4'h8}};  // data4
        last_from_algo = 1'b1;
        #10;
        data_from_algo = {128{1'b0}};
        last_from_algo = 1'b0;
        valid_from_algo = 1'b0;

        #40;
        $finish;

    end



    framing
        #(
            .AXIS_TDATA_WIDTH(AXIS_TDATA_WIDTH ),
            .REG_ADDR_WIDTH(REG_ADDR_WIDTH ),
            .REG_DATA_WIDTH (REG_DATA_WIDTH )
        )
        framing_dut (
            .clk (clk ),
            .rst_n (rst_n ),
            .dest_algo (dest_algo ),
            .opt_algo (opt_algo ),
            .task_algo (task_algo ),
            .addr_algo (addr_algo ),
            .len_algo (len_algo ),
            .data_from_algo (data_from_algo ),
            .valid_from_algo (valid_from_algo ),
            .last_from_algo (last_from_algo ),
            .ready_to_algo (ready_to_algo ),
            .dest_reg (dest_reg ),
            .opt_reg (opt_reg ),
            .task_reg (task_reg ),
            .data_from_reg (data_from_reg ),
            .valid_from_reg (valid_from_reg ),
            .maxis_tready (maxis_tready ),
            .maxis_tvalid (maxis_tvalid ),
            .maxis_tlast (maxis_tlast ),
            .maxis_tdata  ( maxis_tdata)
        );

    

endmodule



