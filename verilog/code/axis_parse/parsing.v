`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/05/22 23:53:06
// Design Name:
// Module Name: frame_parsing
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


// todo: 每个状态修改过的寄存器需要考虑是否需要在某一步清零或者赋初值
// todo: 如果解析出错，是否需要报告给 PC，还是默认解析不会出错？

module parsing # (
        parameter integer AXIS_TDATA_WIDTH	= 128,
        parameter integer REG_ADDR_WIDTH	= 10,
        parameter integer REG_DATA_WIDTH	= 32
    )
    ( 
        input  wire   clk,
        input  wire   rst_n,


        // Interface between SAXIS and Algo.
        // output reg    saxis_tready,
        input  wire   saxis_tvalid,
        input  wire   saxis_tlast,
        input  wire   [AXIS_TDATA_WIDTH-1 : 0] saxis_tdata,


        // Algo module
        // ! 以下信号待定
        // input wire ready_from_algo,
        output reg [AXIS_TDATA_WIDTH-1 : 0] data_to_algo,
        output reg valid_to_algo,
        output reg last_to_algo,

        output reg calc_start,
        output reg calc_pm_wr,
        output reg calc_pm_rd,
        output reg trans_continue,
        input wire calc_done,

        output wire [7 : 0]   src_to_algo,
        output wire [7 : 0]   opt_to_algo,
        output wire [7 : 0]   task_to_algo,
        output wire [63 : 0]  addr_to_algo,   //! 使用DDR时采用, 流式算法用来指示剩余数据的总量
        output wire [31: 0]   len_to_algo,


        // reg module
        // 暂定每次读写 4B
        output reg [REG_ADDR_WIDTH-1 : 0] reg_addr,
        // input wire [REG_DATA_WIDTH-1 : 0] data_from_reg, // ! 暂时不需要
        output reg [REG_DATA_WIDTH-1 : 0] data_to_reg,
        output reg reg_rd,
        output reg reg_wr,
        input wire reg_rd_done,
        input wire reg_wr_done


    );

    /* *** state machine *** */
    // 空闲 —— 拉高 tready 等待 tvalid 拉高
    // 解包
    // 访存 —— 读/写
    // 计算开始
    // 计算流（流式算法）
    // 读取的 DDR 数据
    reg 	[5:0]	current_state, next_state;       // status reg

    localparam  IDLE 		 = 6'b000000; // idle
    localparam  PARSING		 = 6'b1; // frame parsing
    localparam  CALC_START   = 6'b10; // calculating
    localparam  CALC_STREAM  = 6'b100; // calculating
    localparam  RDREG        = 6'b1000; // read out user reg
    localparam  WRREG        = 6'b10000; // read out user reg
    localparam  RDDDR        = 6'b100000; // read ddr



    /* *** parse state *** */
// 数据帧格式
// |            128b                     | 
// | len | addr | task | opt | dst | src |
// | 4B  | 8B   | 1B   | 1B  |  1B | 1B  | 
// | 128b |
// | rsv  |
// | 16B  |



    // 帧头定义
    localparam FR_SRC  = 8;
    localparam FR_DST  = FR_SRC + 8;
    localparam FR_OPT  = FR_DST + 8;
    localparam FR_TASK = FR_OPT + 8;
    localparam FR_ADDR = FR_TASK + 64;
    localparam FR_LEN  = FR_ADDR + 32;

    // 帧地址分配
    localparam src_s = 0;
    localparam src_e = FR_SRC-1;
    localparam dst_s = FR_SRC;
    localparam dst_e = FR_DST-1;
    localparam opt_s = FR_DST;
    localparam opt_e = FR_OPT-1;
    localparam task_s = FR_OPT;
    localparam task_e = FR_TASK-1;
    localparam addr_s = FR_TASK;
    localparam addr_e = FR_ADDR-1;
    localparam len_s = FR_ADDR;
    localparam len_e = FR_LEN-1;

    // 暂存解析的数据
    reg [FR_SRC-1: 0]  fr_src;
    reg [FR_DST-FR_SRC-1: 0]  fr_dst;
    reg [FR_OPT-FR_DST-1: 0]  fr_opt;
    reg [FR_TASK-FR_OPT-1: 0]  fr_task;
    reg [FR_ADDR-FR_TASK-1: 0] fr_addr;
    reg [FR_LEN-FR_ADDR-1: 0]  fr_len;

    // 源模块序号
    localparam MOD_PM = 1;
    localparam MOD_DM = 2;
    // 目的模块序号（应为本模块 AM）
    // 暂时按单个算法模块处理，后续可能支持多个算法模块
    localparam MOD_AM = 3;

    // 操作序号
    localparam OPT_PM_WR_DM = 1;
    localparam OPT_AM_WR_DM = 2;
    localparam OPT_AM_RD_DM = 3;
    localparam OPT_PM_RD_DM = 4;
    localparam OPT_PM_WR_AM = 5;
    localparam OPT_PM_RD_AM = 6;
    localparam OPT_AM_START = 7;
    localparam OPT_AM_END   = 8;
    localparam OPT_PM_WR_REG = 9;
    localparam OPT_PM_RD_REG = 10;

    reg parse_done;
    reg parse_cnt;  // 用于 parsing 计数，128b 数据宽度时，需要两拍，256b 时只要一拍
    reg parse_err;  // 解包错误，回到 IDLE

    // todo: 这里直接将解析出来的参数用作回传的参数
    // 因为差分算法确实是这样
    // 不同的算法应该在算法模块里有不同的处理
    // 对于来自 DDR 的数据包，dest 不应该直接用解析出来的，这个还需要再做具体处理
    assign src_to_algo = fr_src;  // source 作为 dest
    assign opt_to_algo  = fr_opt;
    assign task_to_algo = fr_task;
    assign addr_to_algo = fr_addr;
    assign len_to_algo  = fr_len;

    // todo:这里的信号需要置零
    reg fr_pm_wr_am;
    reg fr_pm_rd_am;
    reg fr_am_begin;
    reg fr_pm_wr_reg;
    reg fr_pm_rd_reg;
    reg fr_am_rd_dm;


    /* *** CALC_START state *** */


    /* *** CALC_STREAM state *** */
    
    wire rd_ddr;
    wire wr_ddr;
    reg saxis_tlast_1;

    always @(posedge clk) begin
        saxis_tlast_1 <= saxis_tlast;
    end

    /* *** readout reg state *** */



    /* *** DDR opt *** */
    // wire wr_ddr_done;
    reg rd_ddr_done;


    /* *** REG state *** */
    reg reg_rd_cnt;
    reg reg_wr_cnt;





    always @ (posedge clk)  // sync reset 
        if(!rst_n)
            current_state <= IDLE;
        else
            current_state <= next_state;


    always @ (*) begin   // level trigger
        next_state = IDLE;  //init next state to ensure a correct state after sys reset
        case(current_state)
            IDLE:               // saxis_tvalid 拉高就进入 PARSING 状态
                if( saxis_tvalid ) 
                    next_state = PARSING;  
                else
                    next_state = IDLE;
            PARSING:            // parsing_done 则进入对于处理流程的状态
                if(parse_done) begin
                    if(fr_pm_wr_am)   // 读和写都进入 CALC_START 状态
                        next_state = CALC_STREAM;
                    else if(fr_pm_rd_am)
                        next_state = CALC_STREAM;
                    else if(fr_am_begin)
                        next_state = CALC_START;
                    else if(fr_pm_wr_reg)
                        next_state = WRREG;
                    else if(fr_pm_rd_reg)
                        next_state = RDREG;
                    else if(fr_am_rd_dm)
                        next_state = RDDDR;
                    else begin
                        next_state = IDLE;
                    end
                    
                end
                else if(parse_err)
                    next_state = IDLE;
                else
                    next_state = PARSING;


            CALC_START:
                next_state = IDLE;


            CALC_STREAM:
            // ! 未必是真的计算完了，也可以是算法模块允许继续解包。只要一个包发送完，就可以继续解包。
                if(calc_done || (!saxis_tlast & saxis_tlast_1)) 
                    next_state = IDLE;
                else
                    next_state = CALC_STREAM;



            RDREG:  // reg_rd_done 包含了从 REG 读出且通过组帧发出
                if(reg_rd_done)
                    next_state = IDLE;
                else
                    next_state = RDREG;

            WRREG:
                if(reg_wr_done)
                    next_state = IDLE;
                else
                    next_state = WRREG;

            RDDDR:
                if(rd_ddr_done)
                    next_state = IDLE;
                else
                    next_state = RDDDR;

            default:
                next_state = IDLE;

        endcase
    end


    always @ (posedge clk) begin
        if(!rst_n) begin
            // saxis_tready <= 1'b1;
            parse_done <= 1'b0;
            parse_cnt <= 1'b0;
        end            
        else begin
            case(next_state)
                IDLE: begin
                    // saxis_tready <= 1'b1;

                    // 解析控制信号复位
                    parse_err <= 1'b0;
                    parse_done <= 1'b0;
                    parse_cnt <= 1'b0;

                    // 帧头解析内容复位
                    fr_pm_wr_am <= 1'b0;
                    fr_pm_rd_am <= 1'b0;
                    fr_am_begin <= 1'b0;
                    fr_pm_wr_reg <= 1'b0;
                    fr_pm_rd_reg <= 1'b0;
                    fr_am_rd_dm <= 1'b0;

                    // algo module 相关信号复位
                    calc_start <= 1'b0;
                    valid_to_algo <= 1'b0;
                    last_to_algo <= 1'b0;


                end

                PARSING: begin            // 目前是按 AXIS 的宽度是 128b 写的
                    if(!parse_cnt) begin  // 前 16B
                        if(saxis_tdata[dst_e : dst_s] != MOD_AM)      // 目的模块不是 AM 就直接退出解析
                            parse_err <= 1'b1;
                        else begin
                            fr_src  <= saxis_tdata[src_e : src_s];
                            fr_dst  <= saxis_tdata[dst_e : dst_s];
                            fr_opt  <= saxis_tdata[opt_e : opt_s];
                            fr_task <= saxis_tdata[task_e : task_s];
                            fr_addr <= saxis_tdata[addr_e : addr_s];
                            fr_len  <= saxis_tdata[len_e : len_s];

                            if(saxis_tdata[src_e : src_s] == MOD_PM) begin  // 源模块是 PM
                                if(saxis_tdata[opt_e : opt_s] == OPT_PM_WR_AM) begin      // PM 直接写 AM
                                    // PM 数据给 AM
                                    fr_pm_wr_am <= 1'b1;
                                    calc_pm_wr <= 1'b1;                                  
                                end
                                else if (saxis_tdata[opt_e : opt_s] == OPT_PM_RD_AM) begin // PM 直接读 AM
                                    // 通知 AM 发送结果数据
                                    // 响应帧的 OPT 相同
                                    fr_pm_rd_am <= 1'b1;
                                    calc_pm_rd <= 1'b1;
                                end
                                else if (saxis_tdata[opt_e : opt_s] == OPT_AM_START) begin  // PM 通知 AM 开始计算
                                    // 通知 AM 开始
                                    // 一个信号即可
                                    fr_am_begin <= 1'b1;
                                end
                                else if (saxis_tdata[opt_e : opt_s] == OPT_PM_WR_REG) begin // PM 写寄存器
                                    // 写入 reg_ctrl
                                    fr_pm_wr_reg <= 1'b1;
                                end
                                else if (saxis_tdata[opt_e : opt_s] == OPT_PM_RD_REG) begin // PM 读寄存器
                                    // 读出 reg_ctrl
                                    fr_pm_rd_reg <= 1'b1;
                                end                            
                            end
                            else if (saxis_tdata[src_e : src_s] == MOD_DM) begin  // 源模块是 DM
                                if(saxis_tdata[opt_e : opt_s] == OPT_AM_RD_DM) begin  // AM 读 DM
                                    // DM 数据给 AM
                                    fr_am_rd_dm <= 1'b1;
                                end
                            end
                            else begin
                                parse_err <= 1'b1;
                            end
                            parse_cnt <= 1'b1;
                        end                            
                    end
                    else begin            // 后 16B，数据为帧头保留项

                        parse_done <= 1'b1;
                        parse_cnt <= 1'b0;
                    end
                end
                    

                CALC_START:  begin   // 通知 AM 开始计算
                    calc_start <= 1'b1;
                end 
                    

                CALC_STREAM:  begin   // 计算流程
                    if(fr_pm_wr_am) begin   // PM wr AM
                        valid_to_algo <= 1'b1;
                        data_to_algo <= saxis_tdata;
                        last_to_algo <= saxis_tlast;

                    end
                    else begin   // PM rd AM
                        // todo: 确认一下 XDMA 用 AXI-strem 的时候，读具体怎么用
                        
                    end
                end


                RDREG: begin   // 是否应该拉低 tready 暂时不接收?
                    if(!reg_rd_cnt) begin
                        reg_addr <= fr_addr[REG_ADDR_WIDTH-1 : 0];
                        reg_rd <= 1'b1;
                        reg_rd_cnt <= 1'b1;
                        // todo: 组帧需要的信息全局发送
                    end
                    else begin
                        if(reg_rd_done)
                            reg_rd_cnt <= 1'b0; // ! 组帧由 reg_ctrl 发起
                        else
                            reg_rd_cnt <= 1'b1;
                    end
                   


                end

                WRREG:  begin
                    if(!reg_wr_cnt) begin
                        reg_addr <= fr_addr[REG_ADDR_WIDTH-1 : 0];
                        data_to_reg <= saxis_tdata[REG_DATA_WIDTH-1 : 0]; 
                        reg_wr <= 1'b1;
                        reg_wr_cnt <= 1'b1;
                    end
                    else begin
                        if(reg_wr_done)
                            reg_wr_cnt <= 1'b0;
                        else
                            reg_wr_cnt <= 1'b1;
                    end
                  
                end


                RDDDR:  begin  // 从 DDR 读数据的返回帧
                    // ! 可能需要判断 AM 是否做好准备接收
                    valid_to_algo <= 1'b1;
                    data_to_algo <= saxis_tdata;
                    if(saxis_tlast)
                        rd_ddr_done <= 1'b1;
                    else
                        rd_ddr_done <= 1'b0;

                    

                end





                default: begin  //default的作用是免除综合工具综合出锁存器。
                    // saxis_tready <= 1'b0;    // 这里属于错误状态，实际可能不会进来
                end
            endcase
        end
    end





endmodule
