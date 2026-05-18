`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2022/05/22 23:53:06
// Design Name:
// Module Name: framing
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


module framing #(
        parameter integer AXIS_TDATA_WIDTH	= 128,
        parameter integer REG_ADDR_WIDTH	= 10,
        parameter integer REG_DATA_WIDTH	= 32
    )
    (

        input wire clk,
        input wire rst_n,

        // Algo module interface
        input wire [7 : 0]   dest_algo,
        input wire [7 : 0]   opt_algo,
        input wire [7 : 0]   task_algo,
        input wire [63 : 0]  addr_algo,  //! 使用DDR时采用, 流式算法用来指示剩余数据的总量
        input wire [31: 0]   len_algo,  // ! 这里最好改成参数化


        input wire [AXIS_TDATA_WIDTH-1 : 0] data_from_algo,
        input wire valid_from_algo,
        input wire last_from_algo,
        // output wire ready_to_algo,


        // reg_ctrl module interface
        input wire [7 : 0] dest_reg,
        input wire [7 : 0] opt_reg,
        input wire [7 : 0] task_reg,
        // input wire [REG_ADDR_WIDTH-1 : 0] addr_reg,
        // 每次都是只读一个数据，地址和长度都不需要，设为 1 就行。
        input wire [REG_DATA_WIDTH-1 : 0] data_from_reg, // ! 默认这个数据会一直输出，就不打拍了
        input wire valid_from_reg,


        // AXI-S Master module interface
        // input wire maxis_tready,
        output reg maxis_tvalid,
        output reg maxis_tlast,
        output reg [AXIS_TDATA_WIDTH-1 : 0] maxis_tdata
    );

    // todo: 1. 实现帧头组装和数据打拍
    // todo: 2. 实现仲裁功能

    localparam fr_src = 8'h03;  // 本模块发出的帧的源地址固定为 0x03（AM 模块）

    reg [AXIS_TDATA_WIDTH-1 : 0] data_from_algo_1;
    reg [AXIS_TDATA_WIDTH-1 : 0] data_from_algo_2;
    reg last_from_algo_1;
    reg last_from_algo_2;
    reg valid_from_algo_1;
    reg valid_from_algo_2;




    /* *** state machine *** */
    // IDLE - 空闲
    // FRAMING_HEAD1 - 帧头第一个 transfer
    // FRAMING_HEAD2 - 帧头第二个 transfer
    // FRAMING_DATA  - 算法数据
    // FRAMING_REG   - REG 数据（就一个 transfer）
    reg 	[3:0]	current_state, next_state;       // status reg

    localparam  IDLE 		  = 4'b0000; // idle
    localparam  FRAMING_HEAD1 = 4'b1; // frame parsing
    localparam  FRAMING_HEAD2 = 4'b10; // calculating
    localparam  FRAMING_DATA  = 4'b100; // calculating
    localparam  FRAMING_REG   = 4'b1000; // read out user reg


    /* *** state machine *** */
    always @ (posedge clk)  // sync reset
        if(!rst_n)
            current_state <= IDLE;
        else
            current_state <= next_state;

    /* *** state machine *** */
    // todo: 这里暂时没有考虑 algo 和 reg 冲突的情况
    always @ (*) begin   // level trigger
        next_state = IDLE;  //init next state to ensure a correct state after sys reset
        case(current_state)
            IDLE:
                if(valid_from_algo || valid_from_reg)
                    next_state = FRAMING_HEAD1;
                else
                    next_state = IDLE;

            FRAMING_HEAD1:
                next_state = FRAMING_HEAD2;

            FRAMING_HEAD2:
                if(valid_from_algo)
                    next_state = FRAMING_DATA;
                else
                    next_state = FRAMING_REG;

            FRAMING_DATA:
                // if(last_from_algo_2 & ~last_from_algo_1) // 捕获到 last 信号的上升沿
                if(maxis_tlast == 1'b1) // 捕获到 last 信号的上升沿
                    next_state = IDLE;
                else
                    next_state = FRAMING_DATA;

            FRAMING_REG:
                next_state = IDLE;

            default:
                next_state = IDLE;

        endcase
    end


    /* *** state machine *** */
    always @(posedge clk) begin
        if(!rst_n) begin
            maxis_tdata <= {AXIS_TDATA_WIDTH{1'b0}};
            maxis_tvalid <= 1'b0;
            maxis_tlast <= 1'b0;
            
        end

        else begin
            case(next_state)
            IDLE: begin
                maxis_tdata <= {AXIS_TDATA_WIDTH{1'b0}};
                maxis_tvalid <= 1'b0;
                maxis_tlast <= 1'b0;
            end

            FRAMING_HEAD1: begin
                maxis_tvalid <= 1'b1;
                if(valid_from_algo)                    
                    maxis_tdata <= {len_algo, addr_algo, task_algo, opt_algo, dest_algo, fr_src};
                else
                    maxis_tdata <= {32'h1, 64'h0, task_reg, opt_reg, dest_reg, fr_src};
            end
        
            FRAMING_HEAD2: // 全填 0
                maxis_tdata <= {AXIS_TDATA_WIDTH{1'b0}};

            FRAMING_DATA: begin
                maxis_tdata <= data_from_algo_2;
                if(last_from_algo_2 & ~last_from_algo_1)    // 捕获到 last 信号的上升沿
                    maxis_tlast <= 1'b1;
                else 
                    maxis_tlast <= 1'b0;
            end

            FRAMING_REG: begin
                maxis_tdata <= data_from_reg;
                maxis_tlast <= 1'b1;
            end

            default: begin
                maxis_tdata <= {AXIS_TDATA_WIDTH{1'b0}};
                maxis_tvalid <= 1'b0;
                maxis_tlast <= 1'b0;
            end

            endcase
                
        end
      
    end


    // assign ready_to_algo = maxis_tready; // 暂时没啥用，只是透传，后面反压可能要用

    // assign conflict_algo_reg = valid_from_algo & valid_from_reg; // 算法模块优先级高，REG 模块优先级低

    // 数据和 last 打两拍
    always @(posedge clk) begin
        if(!rst_n) begin
            data_from_algo_1 <= {AXIS_TDATA_WIDTH{1'b0}};
            data_from_algo_2 <= {AXIS_TDATA_WIDTH{1'b0}};
            last_from_algo_1 <= 1'b0;
            last_from_algo_2 <= 1'b0;
            valid_from_algo_1 <= 1'b0;
            valid_from_algo_2 <= 1'b0;
        end
        else begin
            data_from_algo_1 <= data_from_algo;
            data_from_algo_2 <= data_from_algo_1;
            last_from_algo_1 <= last_from_algo;
            last_from_algo_2 <= last_from_algo_1;
            valid_from_algo_1 <= valid_from_algo;
            valid_from_algo_2 <= valid_from_algo_1;
        end
    end



























endmodule
