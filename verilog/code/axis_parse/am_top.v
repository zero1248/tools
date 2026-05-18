`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/06/14 09:41:28
// Design Name:
// Module Name: top
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



module am_top #(
        parameter integer AXIS_TDATA_WIDTH	= 128,
        parameter integer REG_ADDR_WIDTH	= 10,
        parameter integer REG_DATA_WIDTH	= 32
    )
    (
        input wire clk,
        input wire rst_n,

        // AXI-Stream Slave Interface
        output wire  S_AXIS_TREADY,
        input wire [AXIS_TDATA_WIDTH-1 : 0] S_AXIS_TDATA,
        // input wire [(AXIS_TDATA_WIDTH/8)-1 : 0] S_AXIS_TSTRB,
        input wire [(AXIS_TDATA_WIDTH/8)-1 : 0] S_AXIS_TKEEP,
        input wire  S_AXIS_TLAST,
        input wire  S_AXIS_TVALID,

        // AXI-Stream Master Interface
        output wire  M_AXIS_TVALID,
        output wire [AXIS_TDATA_WIDTH-1 : 0] M_AXIS_TDATA,
        // output wire [(AXIS_TDATA_WIDTH/8)-1 : 0] M_AXIS_TSTRB,
        output wire [(AXIS_TDATA_WIDTH/8)-1 : 0] M_AXIS_TKEEP,
        output wire  M_AXIS_TLAST,
        input wire  M_AXIS_TREADY
    );

    wire saxis_tready;
    wire saxis_tvalid;
    wire saxis_tlast;
    wire [AXIS_TDATA_WIDTH-1 : 0] saxis_tdata;

    wire ready_algo_to_parsing;
    wire [AXIS_TDATA_WIDTH-1 : 0] data_parsing_to_algo;
    wire valid_parsing_to_algo;
    wire last_parsing_to_algo;
    wire calc_start;
    wire calc_pm_wr;
    wire calc_pm_rd;
    wire trans_continue;
    wire calc_done;

    wire [7: 0] src_parsing_to_algo;
    wire [7: 0] opt_parsing_to_algo;
    wire [7: 0] task_parsing_to_algo;
    wire [63: 0] addr_parsing_to_algo;
    wire [31: 0] len_parsing_to_algo;


    wire [REG_ADDR_WIDTH-1 : 0] reg_addr_par;
    wire [REG_DATA_WIDTH-1 : 0] data_to_reg_par;
    wire reg_rd_par;
    wire reg_wr_par;
    wire reg_rd_done_par;
    wire reg_wr_done_par;



    wire [REG_ADDR_WIDTH-1 : 0] reg_addr_algo;
    wire [REG_DATA_WIDTH-1 : 0] data_to_reg_algo;
    wire [REG_DATA_WIDTH-1 : 0] data_from_reg_algo;
    wire reg_rd_algo;
    wire reg_wr_algo;
    wire reg_rd_done_algo;
    wire reg_wr_done_algo;



    wire [AXIS_TDATA_WIDTH-1 : 0] data_algo_to_framing;
    wire valid_algo_to_framing;
    wire last_algo_to_framing;
    wire ready_framing_to_algo;

    wire [7 : 0]   dest_algo_to_framing;
    wire [7 : 0]   opt_algo_to_framing;
    wire [7 : 0]   task_algo_to_framing;
    wire [63 : 0]  addr_algo_to_framing;  
    wire [31: 0]   len_algo_to_framing; 




    // wire maxis_tready;
    wire maxis_tready_to_saxis;
    wire maxis_tvalid;
    wire maxis_tlast;
    wire [AXIS_TDATA_WIDTH-1 : 0] maxis_tdata;



    axis_slave_intr
        #(
            .AXIS_TDATA_WIDTH (
                AXIS_TDATA_WIDTH )
        )
        axis_slave_intr_inst (

            // Interface between SAXIS and Parsing.
            .saxis_tready_from_maxis (maxis_tready_to_saxis ),
            // .saxis_tready (saxis_tready ),
            .saxis_tvalid (saxis_tvalid ),
            .saxis_tlast (saxis_tlast ),
            .saxis_tdata (saxis_tdata ),

            // AXI Stream slave Interface(to external)
            .S_AXIS_ACLK (clk ),
            .S_AXIS_ARESETN (rst_n ),

            .S_AXIS_TREADY (S_AXIS_TREADY ),
            .S_AXIS_TDATA (S_AXIS_TDATA ),
            .S_AXIS_TLAST (S_AXIS_TLAST ),
            .S_AXIS_TVALID  ( S_AXIS_TVALID),
            .S_AXIS_TKEEP  ( S_AXIS_TKEEP)
        );


    parsing
        #(
            .AXIS_TDATA_WIDTH (AXIS_TDATA_WIDTH ),
            .REG_ADDR_WIDTH (REG_ADDR_WIDTH ),
            .REG_DATA_WIDTH (REG_DATA_WIDTH )
        )
        parsing_inst (

            .clk (clk ),
            .rst_n (rst_n ),


            // Interface between SAXIS and Algo.
            .saxis_tready (saxis_tready ),
            .saxis_tvalid (saxis_tvalid ),
            .saxis_tlast (saxis_tlast ),
            .saxis_tdata (saxis_tdata ),


            // Interface between Parsing and Algo.
            // .ready_from_algo (ready_algo_to_parsing ),
            .data_to_algo (data_parsing_to_algo ),
            .valid_to_algo (valid_parsing_to_algo ),
            .last_to_algo (last_parsing_to_algo ),

            .calc_start (calc_start ),
            .calc_pm_wr (calc_pm_wr ),
            .calc_pm_rd (calc_pm_rd ),
            .trans_continue (trans_continue ),
            .calc_done (calc_done ),

            .src_to_algo( src_parsing_to_algo ),
            .opt_to_algo( opt_parsing_to_algo ),
            .task_to_algo( task_parsing_to_algo ),
            .addr_to_algo( addr_parsing_to_algo ),
            .len_to_algo( len_parsing_to_algo ),


            // Interface between Parsing and Reg_ctrl.
            .reg_addr (reg_addr_par ),
            .data_to_reg (data_to_reg_par ),
            .reg_rd (reg_rd_par ),
            .reg_wr (reg_wr_par ),
            .reg_rd_done (reg_rd_done_par ),
            .reg_wr_done  ( reg_wr_done_par )
        );


    algo_module
        #(
            .AXIS_TDATA_WIDTH (AXIS_TDATA_WIDTH ),
            .REG_ADDR_WIDTH (REG_ADDR_WIDTH ),
            .REG_DATA_WIDTH (REG_DATA_WIDTH )
        )
        algo_module_inst (

            .clk (clk ),
            .rst_n (rst_n ),

            // Interface between Parsing and Algo.
            // .ready_to_parsing (ready_algo_to_parsing ),
            .data_from_parsing (data_parsing_to_algo ),
            .valid_from_parsing (valid_parsing_to_algo ),
            .last_from_parsing (last_parsing_to_algo ),

            .calc_start (calc_start ),
            .calc_pm_wr (calc_pm_wr ),
            .calc_pm_rd (calc_pm_rd ),
            .trans_continue (trans_continue ),
            .calc_done (calc_done ),

            .src_from_parsing (src_parsing_to_algo ),
            .opt_from_parsing (opt_parsing_to_algo ),
            .task_from_parsing (task_parsing_to_algo ),
            .addr_from_parsing (addr_parsing_to_algo ),
            .len_from_parsing (len_parsing_to_algo ),


            // Interface between Parsing and Reg_ctrl.
            .reg_addr (reg_addr_algo ),
            .data_to_reg (data_to_reg_algo ),
            .data_from_reg (data_from_reg_algo ),
            .rd_reg (rd_reg_algo ),
            .wr_reg (wr_reg_algo ),
            .rd_reg_done (rd_reg_done_algo ),
            .wr_reg_done (wr_reg_done_algo ),


            // Interface between Algo. and Framing
            .data_to_framing (data_algo_to_framing ),
            .valid_to_framing (valid_algo_to_framing ),
            .last_to_framing (last_algo_to_framing ),
            // .ready_from_framing  ( ready_framing_to_algo),

            .dest_to_framing (dest_algo_to_framing),
            .opt_to_framing (opt_algo_to_framing),
            .task_to_framing (task_algo_to_framing),
            .addr_to_framing (addr_algo_to_framing),
            .len_to_framing (len_algo_to_framing)
        );



    framing
        #(
            .AXIS_TDATA_WIDTH( AXIS_TDATA_WIDTH ),
            .REG_ADDR_WIDTH( REG_ADDR_WIDTH ),
            .REG_DATA_WIDTH ( REG_DATA_WIDTH )
        )
        framing_inst (

            .clk (clk ),
            .rst_n (rst_n ),

            // Interface between Algo. and Framing
            .dest_algo (dest_algo_to_framing ),
            .opt_algo (opt_algo_to_framing ),
            .task_algo (task_algo_to_framing ),
            .addr_algo (addr_algo_to_framing ),
            .len_algo (len_algo_to_framing ),

            .data_from_algo (data_algo_to_framing ),
            .valid_from_algo (valid_algo_to_framing ),
            .last_from_algo (last_algo_to_framing ),
            // .ready_to_algo (ready_framing_to_algo ),


            // Interface between REG_ctrl. and Framing
            // .dest_reg (dest_reg ),
            // .opt_reg (opt_reg ),
            // .task_reg (task_reg ),
            // .data_from_reg (data_from_reg ),
            // .valid_from_reg (valid_from_reg ),


            // Interface between MAXIS and Framing
            // .maxis_tready (maxis_tready ),
            .maxis_tvalid (maxis_tvalid ),
            .maxis_tlast (maxis_tlast ),
            .maxis_tdata  ( maxis_tdata)
        );




        axis_master_intr 
        #(
          .AXIS_TDATA_WIDTH ( AXIS_TDATA_WIDTH )
        )
        axis_master_intr_inst (

        //   .maxis_tready (maxis_tready ),
          .maxis_tready_to_saxis (maxis_tready_to_saxis ),
          .maxis_tvalid (maxis_tvalid ),
          .maxis_tlast (maxis_tlast ),
          .maxis_tdata (maxis_tdata ),

          .M_AXIS_ACLK (clk ),
          .M_AXIS_ARESETN (rst_n ),

          .M_AXIS_TVALID (M_AXIS_TVALID ),
          .M_AXIS_TDATA (M_AXIS_TDATA ),
          .M_AXIS_TLAST (M_AXIS_TLAST ),
          .M_AXIS_TREADY  ( M_AXIS_TREADY),
          .M_AXIS_TKEEP  ( M_AXIS_TKEEP)
        );
      






endmodule
