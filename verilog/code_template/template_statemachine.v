// 三段式状态机


module state_machine # (

    ) (
        input wire clk,
        input wire rst_n,

        // other interface signals
        input wire [63: 0] input_data,
        output wire [63: 0] output_data
    );


    // 定义存放状态机的现态和次态的寄存器
    reg 	[5: 0]	current_state, next_state;       

    // 定义状态名称及其编码，状态不多可以用独热码
    localparam  IDLE 		 = 6'b000000; // idle
    localparam  STATE0		 = 6'b1; // frame parsing
    localparam  STATE1       = 6'b10; // calculating
    localparam  STATE2       = 6'b100; // calculating
    localparam  STATE3       = 6'b1000; // read out user reg
    localparam  STATE4       = 6'b10000; // read out user reg
    localparam  STATE5       = 6'b100000; // read ddr


    // 三段式状态机第一段
    // 实现状态转移
    // 使用非阻塞赋值
    always @ (posedge clk)  // 同步复位
    // always @ (posedge clk or negedge rst_n)  // 异步复位 
        if(!rst_n)
            current_state <= IDLE;
        else
            current_state <= next_state;

    // 三段式状态机第二段
    // 组合逻辑块描述状态转移条件
    // 使用阻塞赋值
    always @ (*) begin   // level trigger
        next_state = IDLE;  //init next state to ensure a correct state after sys reset
        case(current_state)
            
            IDLE:
                // tvalid_i 拉高就进入 PARSING 状态
                // 不需要关注 ready 信号，在时序逻辑中考虑 ready 信号      
                if( ... ) 
                    next_state = ...;  
                else
                    next_state = IDLE;

            STATE0:            // parsing_done 则进入对于处理流程的状态
                if(...) begin
                    if(...)                 // 读和写都进入 CALC_START 状态
                        next_state = STATE0;
                    else if(...)            // 读和写都进入 CALC_START 状态
                        next_state = STATE1;
                    else if(...)
                        next_state = STATE2;
                    else begin
                        next_state = IDLE;
                    end                    
                end
                else if(...)
                    next_state = ...;
                else
                    next_state = ...;


            STATE1:    
                ...

            ...:

            default:
                next_state = IDLE;

        endcase
    end


    // 三段式状态机第三段
    // 时序逻辑块 - 格式化描述次态寄存器输出
    // 使用阻塞赋值
    always @ (posedge clk) begin
        if(!rst_n) begin
            // 信号复位
            ... <= 1'b0;
            ... <= 1'b0;
            ... <= 1'b0;
        end            
        else begin
            case(next_state)
                IDLE: begin

                    // 解析控制信号复位
                    ... <= 1'b0;
                    ... <= 1'b0;
                    ... <= 1'b0;

                end

                STATE0: begin            // 目前是按 AXIS 的宽度是 128b 写的
                    if(!...) begin  // 前 16B
                        ...                        
                    end
                    else if(...)begin   // 后 16B，数据为帧头保留项
                        ...
                    end
                    else begin
                        ...
                    end
                end 

                ...

                default: begin  // 照搬 IDLE            
                    parse_err <= 1'b0;
                    parse_done <= 1'b0;
                    parse_cnt <= 1'b0;
                end
            endcase
        end
    end

endmodule


