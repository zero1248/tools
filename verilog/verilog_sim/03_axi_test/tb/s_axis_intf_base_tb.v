`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/06/08 09:56:24
// Design Name:
// Module Name: s_axis_intf_base_tb
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


module s_axis_intf_base_tb;

    // Parameters
    localparam integer S_AXIS_TDATA_WIDTH = 128;
    parameter clk_period = 10; // 10ns

    // Ports
    reg  tready_down = 0;
    wire tvalid_down;
    wire tlast_down;
    wire [S_AXIS_TDATA_WIDTH-1 : 0] tdata_down;
    wire  tready_up;
    reg  tvalid_up = 0;
    reg  tlast_up = 0;
    reg [S_AXIS_TDATA_WIDTH-1 : 0] tdata_up;
    reg  S_AXIS_ACLK = 0;
    reg  S_AXIS_ARESETN = 0;


    initial begin
        S_AXIS_ACLK = 0;
        forever
            #(clk_period/2) S_AXIS_ACLK = ~S_AXIS_ACLK;
    end

    initial begin
        S_AXIS_ARESETN = 0;
        #20;
        S_AXIS_ARESETN = 1;
    end

    initial begin
        tready_down = 0;
        tvalid_up = 0;
        tlast_up = 0;
        tdata_up = 0;
        #20;
        // case 1: valid before ready handshake
        tvalid_up = 1;
        tlast_up = 0;
        tdata_up = 'b1000;
        #10;
        tready_down = 1;
        #10;
        tdata_up = 'b0100;
        #10;
        tdata_up = 'b0010;
        #10;
        tdata_up = 'b0001;
        tlast_up = 1;
        #10;
        tlast_up = 0;
        tvalid_up = 0;
        tdata_up = 'b0000;
        #30;
        $finish;
        



        // case 2: ready after valid handshake




        // case 3: valid with ready handshake

    end






    s_axis_intf_base
    #(
        .S_AXIS_TDATA_WIDTH (
            S_AXIS_TDATA_WIDTH )
    )
    s_axis_intf_base_dut (
        .tready_down (tready_down ),
        .tvalid_down (tvalid_down ),
        .tlast_down (tlast_down ),
        .tdata_down (tdata_down ),
        .tready_up (tready_up ),
        .tvalid_up (tvalid_up ),
        .tlast_up (tlast_up ),
        .tdata_up (tdata_up ),
        .S_AXIS_ACLK (S_AXIS_ACLK ),
        .S_AXIS_ARESETN  ( S_AXIS_ARESETN)
    );


endmodule

