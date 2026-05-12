`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2023/06/02 19:31:37
// Design Name:
// Module Name: tb_adder_file_rw
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


module tb_adder_file_rw #(
        parameter integer DATA_WIDTH = 32
    );

    localparam CLK_PERIOD = 10;     // 时钟周期

    // dut 接口
    reg  clk = 1;
    reg  rst_n = 0;
    reg [DATA_WIDTH-1: 0] a;
    reg [DATA_WIDTH-1: 0] b;
    wire [DATA_WIDTH-1: 0] sum;

    // 时钟生成
    initial begin
        forever
            #(CLK_PERIOD/2)
             clk = ~clk;
    end

    // 从文件中读写相关变量
    integer file_in;
    integer file_out;
    integer i;
    integer num_data = 0;


    initial begin

        // 初始化 dut 输入数据
        clk = 0;
        rst_n = 0;
        a = {(DATA_WIDTH){1'b0}};
        b = {(DATA_WIDTH){1'b0}};


        file_in = $fopen("../test_in.txt", "r");
        if (file_in == 0) begin    // judge file handle
            $fatal("Unable to open input file");
            $finish;
        end

        file_out = $fopen("../test_out.txt", "w");
        if (file_out == 0) begin    // judge file handle
            $fatal("Unable to open output file");
            $finish;
        end

        #50;
        rst_n = 1;
        #10;

        // // 用 fscanf 从文件里读取数据
        // while (!$feof(file_in)) begin
        //     // fscanf 是按格式化读取数据，每行一个数据
        //     $fscanf(file_in, "%h", a);  // 以 32bit 读出
        //     $fscanf(file_in, "%h", b);
        //     #10;

        //     // 输出数据到仿真波形
        //     $display("Data In: %h + %h, Data Out: %h", a, b, sum);
        //     // 输出数据到输出文件
        //     $fdisplay(file_out, "Data In: %h + %h, Data Out: %h", a, b, sum);

        //     num_data = num_data + 2;
        // end


        // 用 fread 从文件里读取数据
        while (!$feof(file_in)) begin
            // fread 是按第一个参数的长度读取数据，适用于紧密编码的数据
            $fread(a, file_in);
            $fread(b, file_in);
            #10;

            // 输出数据到仿真波形
            $display("Data In: %h + %h, Data Out: %h", a, b, sum);
            $fdisplay(file_out, "Data In: %h + %h, Data Out: %h", a, b, sum);

            num_data = num_data + 2;
        end


        // 关闭文件
        $fclose(file_in);
        $fclose(file_out);

        // 输出读取的数据量
        $display("Total data read: %d", num_data);

        // 等待一段时间以确保所有数据被处理
        #100;

        // 结束仿真
        $finish;

    end

    // 例化 dut
    adder
        #(
            .DATA_WIDTH(DATA_WIDTH)
        )
        dut_adder(
            .a(a),
            .b(b),
            .sum(sum),
            .clk(clk),
            .rst_n(rst_n)
        );


endmodule
