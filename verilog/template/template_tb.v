`timescale 1ns/1ps


module tb_template;

    // Parameters
    localparam integer ADDR_WIDTH = 12;
    localparam integer DATA_WIDTH = 32;

    // Ports
    reg clk;
    reg rst_n;
    reg [DATA_WIDTH - 1: 0] data_in;
    reg [ADDR_WIDTH - 1: 0] addr_in;
    wire [DATA_WIDTH - 1: 0] data_out;


    // 时钟生成
    initial begin
        clk = 0;
        forever #5 clk = ~clk;  // 10ns 周期 -> 100MHz
    end


    // // 复位初始化
    // initial begin
    //     rst_n = 0;
    //     #2000 rst_n = 1;            // 复位
    // end


    // 显示状态机名称
    reg [63: 0] wstate_r;
    always @(*) begin
        case(ali_dmod_inst.inst_control_s_axi.wstate)  // 可以访问 module 实例化后的某个内部信号，且可嵌套
            2'd0:       wstate_r = "WR_IDLE ";
            2'd1:       wstate_r = "WR_DATA ";
            2'd2:       wstate_r = "WR_RESP ";
            2'd3:       wstate_r = "WR_RST  ";
        endcase
    end


    // 测试主程序
    initial begin
        // 初始化信号
        initialize_signals();

        // 生成复位
        generate_reset();

        // 开始测试
        $display("----- TEST STARTED -----");



        $display("----- TEST COMPLETED -----");
        #100;
        $finish;


    end


    // 任务: 初始化信号
    task initialize_signals;
    begin
        clk = 0;
        rst_n = 0;
        s_axis_tdata = 0;
        s_axis_tvalid = 0;
        s_axis_tlast = 0;
        s_axis_tkeep = 8'hFF;  // 默认所有字节有效
    end
    endtask


    // 任务: 生成复位
    task generate_reset;
    begin
        #20;        // 等待初始稳定
        rst_n = 0;  // 断言复位
        #2000;      // 有些 IP 需要较长的复位时间，这里设置长一些
        rst_n = 1;  // 解除复位
        #20;
    end
    endtask

endmodule
