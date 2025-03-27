`timescale 1ns/1ps


module tb_template;

    // Parameters
    localparam integer ADDR_WIDTH = 12;
    localparam integer DATA_WIDTH = 32;

    // Ports
    reg ap_clk;
    reg ap_rst_n;
    reg [DATA_WIDTH - 1: 0] data_in;
    reg [ADDR_WIDTH - 1: 0] addr_in;
    wire [DATA_WIDTH - 1: 0] data_out;

    // 时钟生成
    initial begin
        ap_clk = 0;
        forever #5 ap_clk = ~ap_clk;  // 10ns 周期 -> 100MHz
    end

    // 复位初始化
    initial begin
        ap_rst_n = 0;
        #2000 ap_rst_n = 1;            // 复位
    end


endmodule
