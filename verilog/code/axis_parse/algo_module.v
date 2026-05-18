`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/06/11 22:32:24
// Design Name:
// Module Name: algo_module
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

// 算法模块有两种类型：流式和非流式，但一个具体的算法只能是其中一种。
// 非流式需要 DM 缓存数据

module algo_module# (
        parameter integer AXIS_TDATA_WIDTH	= 128,
        parameter integer REG_ADDR_WIDTH	= 10,
        parameter integer REG_DATA_WIDTH	= 32
    )
    (

        input wire clk,
        input wire rst_n,

        // parsing module interface
        // 数据及握手信号
        // output wire ready_to_parsing,
        input  wire [AXIS_TDATA_WIDTH-1 : 0] data_from_parsing,
        input  wire valid_from_parsing,
        input  wire last_from_parsing,
        // 来自解析模块的通知信号
        input  wire calc_start,   // 流式算法不需要用到这个信号
        input  wire calc_pm_wr,
        input  wire calc_pm_rd,
        input  wire trans_continue, // 流式算法使用，表明后面还有数据帧
        output wire calc_done,   // 计算结束信号，两种模式都要用到。未必是真的计算完了，也可以是算法模块允许继续解包

        input wire [7 : 0]   src_from_parsing,
        input wire [7 : 0]   opt_from_parsing,
        input wire [7 : 0]   task_from_parsing,
        input wire [63 : 0]  addr_from_parsing,   //! 使用DDR时采用, 流式算法用来指示剩余数据的总量
        input wire [31: 0]   len_from_parsing,  // ! 这里最好改成参数化


        // reg_ctrl module interface
        output wire [REG_ADDR_WIDTH-1 : 0] reg_addr,
        output wire [REG_DATA_WIDTH-1 : 0] data_to_reg,
        output wire [REG_DATA_WIDTH-1 : 0] data_from_reg,
        output wire rd_reg,
        output wire wr_reg,
        input  wire rd_reg_done,
        input  wire wr_reg_done,


        // framing module interface
        output reg [AXIS_TDATA_WIDTH-1 : 0] data_to_framing,
        output reg valid_to_framing,
        output reg last_to_framing,
        // input wire ready_from_framing,

        output wire [7 : 0]   dest_to_framing,
        output wire [7 : 0]   opt_to_framing,
        output wire [7 : 0]   task_to_framing,
        output wire [63 : 0]  addr_to_framing,  //! 使用DDR时采用, 流式算法用来指示剩余数据的总量
        output wire [31: 0]   len_to_framing  // ! 这里最好改成参数化

    );

    reg [15: 0] shift_reg = 16'b0;
    reg last_from_parsing_1;
    // wire handshake_done;

    // reg [AXIS_TDATA_WIDTH-1: 0] sft_diff_vec_i;
    // reg [15: 0] sft_diff_sft_i;
    wire [AXIS_TDATA_WIDTH-1: 0] sft_diff_vec_o;


    
    assign dest_to_framing = src_from_parsing;
    assign opt_to_framing = opt_from_parsing;
    assign task_to_framing = task_from_parsing;
    assign addr_to_framing = addr_from_parsing;
    assign len_to_framing = len_from_parsing;




    // 打一拍取上升沿
    always @(posedge clk) begin
        if (!rst_n)
            last_from_parsing_1 <= 1'b0;
        else
            last_from_parsing_1 <= last_from_parsing;
    end

    
    // ready 信号透传，暂时没什么用
    // assign ready_to_parsing = ready_from_framing;

    // assign handshake_done = valid_from_parsing && ready_from_framing;


    // 移位寄存器逻辑
    always @(posedge clk) begin
        if (!rst_n) begin
            // todo: 复位 shift_reg 的时机还需要再商量一下，应该需要一个信号来复位，用于多个连续的数据包传输一张图像的情况
            shift_reg <= 16'b0;
        end
        else begin
            // if(handshake_done) begin
            if(valid_from_parsing) begin
                shift_reg <= data_from_parsing[AXIS_TDATA_WIDTH-1: AXIS_TDATA_WIDTH-16]; // 缓存高 16bit
            end
            else if(last_from_parsing_1 && !last_from_parsing) begin // 前端数据发送结束后，要把 shift_reg 清零，否则影响下一次
                // 本次算法全部算完才把 shift_reg 清零
                if(trans_continue)
                    shift_reg <= 16'b0;
                else
                    shift_reg <= shift_reg;
            end
            else begin
                shift_reg <= shift_reg;
            end
        end
    end


    // 数据计算
    always @(posedge clk) begin
        if (!rst_n) begin
            valid_to_framing <= 1'b0;
            last_to_framing <= 1'b0;
            data_to_framing <= {AXIS_TDATA_WIDTH{1'b0}};
        end

        // else if(handshake_done) begin
        else if(valid_from_parsing) begin

            data_to_framing <= sft_diff_vec_o;

            valid_to_framing <= 1'b1;
            if(last_from_parsing) begin
                last_to_framing <= 1'b1;
            end
            else begin
                last_to_framing <= 1'b0;
            end
        end

        else begin
            valid_to_framing <= 1'b0;
            last_to_framing <= 1'b0;
            data_to_framing <= {AXIS_TDATA_WIDTH{1'b0}};
        end
    end



    assign clk_o = clk;
    assign rst_n_o = rst_n;

    shift_diff
        #(
            .AXIS_TDATA_WIDTH (
                AXIS_TDATA_WIDTH )
        )
        shift_diff_inst (
            .input_vec (data_from_parsing),
            .input_shift (shift_reg),
            .output_vec  ( sft_diff_vec_o)
        );




endmodule
