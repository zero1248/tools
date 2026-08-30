`timescale 1 ns/1 ns  

module tb_delay();  
    reg                        clk   ;//系统时钟，默认100MHz；  
    reg                        rst_n ;//系统复位，默认低电平有效；  
    reg         [3 : 0]        a;  
    reg         [3 : 0]        b;
    wire        [4 : 0]        out  ;  
    
    adder4b_half  dut_adder4b_half (  
        .clk   ( clk       ),  
        .rst_n ( rst_n     ),  
        .a     ( a         ),  
        .b     ( b         ),  
        .out   ( out       )  
    );  

    initial begin  
        clk = 1;  
        forever #5 clk=~clk;  
    end
    // always #5 clk = ~clk;

    initial begin  
        rst_n = 0;//开始时复位10个时钟；  
        #50;  
        rst_n = 1;  
    end  

    initial begin
        $dumpfile("wave/tb_delay.vcd");
        $dumpvars(0, tb_delay);
    end

    initial begin  
        a = 0; 
        b = 0; 
        
        // 使用 #10 延时 
        #100;
        repeat(10) begin
            #10;  
            a = {$random} % 16;  
            b = {$random} % 16;  
        end
        // 表现出组合逻辑的效果：输出与输入是对齐的
        // 原因是输入值改变发生在时钟上升沿，触发器在上升沿采样到了新值，立即更新输出  

        // 使用 #10 延时，且整体延时 1ns
        #10;
        a = 0; 
        b = 0; 
        #50;
        #1;
        repeat(10) begin
            #10;  
            a = {$random} % 16;  
            b = {$random} % 16;  
        end
        // 表现出时序逻辑的效果：输出比输入落后一个周期
        // 这样其实类似于在下降沿改变数据，保证了充足的

        // 使用 @(posedge clk)，放在 repeat 后
        #9;
        a = 0; 
        b = 0; 
        #50;
        repeat(10) @(posedge clk) begin
            a = {$random} % 16;  
            b = {$random} % 16;  
        end 
        // 表现出组合逻辑的效果：输出与输入是对齐的

        // 使用 @(posedge clk)，放在循环体内
        #10;
        a = 0; 
        b = 0; 
        #50;
        repeat(10) begin
            @(posedge clk);
            a = {$random} % 16;  
            b = {$random} % 16;  
        end 
        // 表现出组合逻辑的效果：输出与输入是对齐的

        // 使用 @(posedge clk)，放在循环体内
        // 使用非阻塞赋值
        #10;
        a = 0; 
        b = 0; 
        #50;
        repeat(10) begin
            @(posedge clk);
            a <= {$random} % 16;  
            b <= {$random} % 16;  
        end 
        // 表现出时序逻辑的效果：输出比输入落后一个周期
        

        #50;
        $finish;//停止仿真；  
    end


endmodule