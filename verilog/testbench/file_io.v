`timescale 1ns / 1ps

module tb_gzip_ip #(
        parameter integer AXIS_TDATA_WIDTH	= 64
    )();

    localparam CLK_PERIOD = 10;

    reg  clk = 0;
    reg  rst_n = 0;

    // AXI-Stream 输入接口
    reg [AXIS_TDATA_WIDTH-1: 0] inStream_TDATA;
    reg [((AXIS_TDATA_WIDTH/8)-1) : 0] inStream_TKEEP;
    reg [((AXIS_TDATA_WIDTH/8)-1) : 0] inStream_TSTRB;
    reg         inStream_TVALID;
    wire        inStream_TREADY;
    reg         inStream_TLAST;

    // AXI-Stream 输出接口
    wire [AXIS_TDATA_WIDTH-1: 0] outStream_TDATA;
    wire [((AXIS_TDATA_WIDTH/8)-1) : 0] outStream_TKEEP;
    wire [((AXIS_TDATA_WIDTH/8)-1) : 0] outStream_TSTRB;
    wire        outStream_TVALID;
    reg         outStream_TREADY;
    wire        outStream_TLAST;
    wire [31: 0]       outStream_TUSER;

    // 从文件中读写相关变量
    integer file_in;
    integer file_out;
    integer file_compress;
    integer i;
    integer num_data = 0;
    integer char_num;         // $fread 读出的字符个数
    integer data_empty = 1;   // 用于判断是否需要读取新的数据
    integer file_length = 0;  // 用于统计输入文件长度
    integer read_cnt = 0;     // 用于记录读取数据的累计长度
    reg [AXIS_TDATA_WIDTH-1: 0] input_data;  // 缓存从文件读取的数据，用于大端变小端
    reg [7: 0] compress_byte; // 用于按字节写入压缩文件时缓存字节数据


    // 将输入的 0-8 的数字转换成 bitmap 式数据，即 5 转换成 00011111
    // 用移位运算更简单
    function [7:0] flatten_ones(integer num);
        reg [7:0] result;
        integer i;
        begin
            if((num>=0) && (num<=8)) begin
                result = 8'b0;
                for (i = 0; i < num; i = i + 1)
                    result[i] = 1;
                flatten_ones = result;
            end
            else begin
                $fatal("Error data length from input file");
                flatten_ones = 8'b0;
            end
        end
    endfunction

    // 统计有多少个 1, 用 flatten_ones 相反
    function automatic integer count_ones(input [7: 0] num_in);
        integer result;
        begin
            result = 0;
            while(num_in != 8'h00) begin 
                num_in = num_in >> 1;
                result = result + 1;
            end
            count_ones = result;
        end
    endfunction

    // 大小端转换
    function [AXIS_TDATA_WIDTH-1: 0] endian_trans(input [AXIS_TDATA_WIDTH-1: 0] data);
        integer i;
        reg [7: 0] tmp;
        begin
            i = 0;
            while(i < (AXIS_TDATA_WIDTH)/8/2) begin
                tmp = data[(i*8)+: 8];   
                data[(i*8)+: 8] = data[(AXIS_TDATA_WIDTH-1 -i*8)-: 8];
                data[(AXIS_TDATA_WIDTH-1 -i*8)-: 8] = tmp;
                i = i + 1;
            end
            endian_trans = data;
        end
    endfunction

    // 时钟
    initial begin
        clk = 1;
        forever
            #(CLK_PERIOD/2)
             clk = ~clk;
    end


    initial begin

        inStream_TDATA = {{AXIS_TDATA_WIDTH}{1'b0}};
        inStream_TKEEP = {(AXIS_TDATA_WIDTH/8){1'b0}};
        inStream_TSTRB = {{AXIS_TDATA_WIDTH/8}{1'b0}};
        inStream_TVALID = 1'b0;
        inStream_TLAST = 1'b0;

        outStream_TREADY = 1'b1;


        // file_in = $fopen("D:/vitis2021_mpsoc_code/bd/parsing_full_compress/parsing_full_compress.sim/sim_1/behav/test_in.txt", "r");
        $display("Open input file ");
        file_in = $fopen("../test_in.txt", "r+b");
        if (file_in == 0) begin    // judge file handle
            $fatal("Unable to open input file");
            $finish;
        end
        $display("Open input file done");

        // file_out = $fopen("D:/vitis2021_mpsoc_code/bd/parsing_full_compress/parsing_full_compress.sim/sim_1/behav/test_out.txt", "w");
        $display("Open output file ");
        file_out = $fopen("../test_out.txt", "w+b"); // 这里要写 +b，否则在向文件中写入 0x0a 时会自动在前面加上 0x0d
        if (file_out == 0) begin    // judge file handle
            $fatal("Unable to open output file");
            $finish;
        end
        $display("Open output file done");

        $display("Open compression file ");
        file_compress = $fopen("../test_in.gz", "w+b");
        if (file_compress == 0) begin    // judge file handle
            $fatal("Unable to open compression file");
            $finish;
        end
        $display("Open compression file done");


        // 统计输入文件长度
        while($signed($fgetc(file_in)) != -1) begin
            file_length = file_length + 1;
        end
        $display("Input file length: ", file_length);
        $fseek(file_in, 0, 0);  //重置文件指针到起始位置

        rst_n = 0;
        #500;
        rst_n = 1;
        #5;

    
        // 用 fread 从文件里读取数据
        while (read_cnt < file_length) begin
            // fread 是按第一个参数的长度读取数据，适用于紧密编码的数据
            if(data_empty) begin
                char_num = $fread(input_data, file_in);   // 读出来的 input_data 是大端模式
                inStream_TDATA = endian_trans(input_data) >> (AXIS_TDATA_WIDTH - char_num*8); // 如果读出数据不是全部有效，大小端转换后需要移位
                data_empty = 0;
                read_cnt = read_cnt + char_num;
                $display("Data In: %h, %d nums", inStream_TDATA, char_num);
                $fdisplay(file_out, "Data In: %h, %d nums", inStream_TDATA, char_num);
            end
            inStream_TVALID = 1'b1;
            inStream_TKEEP = flatten_ones(char_num);   // 这里也可以用移位运算
            inStream_TSTRB = flatten_ones(char_num);
            if(read_cnt >= file_length) inStream_TLAST = 1'b1;

            #10;

            if(inStream_TREADY) begin
                data_empty = 1;
                if(inStream_TLAST) begin
                    inStream_TVALID = 1'b0;
                    inStream_TLAST = 1'b0;
                    inStream_TKEEP = 8'h00;
                    inStream_TSTRB = 8'h00;
                    data_empty = 0;
                end
            end
        end

        // 关闭文件
        $fclose(file_in);
        

        // 输出读取的数据量到 console 和 输出文件
        $fdisplay(file_out, "Total data read from input file: %d", read_cnt);
        $display("Total data read from input file: %d", read_cnt);

        // // 等待一段时间以确保所有数据被处理
        // #10000000;

        // !处理输出数据!!!!!!!!!!!
        read_cnt = 0;
        while(1) begin
            #10;
            if(outStream_TVALID) begin
                char_num = count_ones(outStream_TKEEP);
                read_cnt = read_cnt + char_num; 
                $display("Data out: %h, %d nums", outStream_TDATA, char_num);
                $fdisplay(file_out, "Data out: %h, %d nums", outStream_TDATA, char_num);
                i = 0;
                while(i < char_num) begin
                    compress_byte = outStream_TDATA[(8*(i+1)-1)-: 8];
                    $fwrite(file_compress, "%c", compress_byte);
                    // $display("write to gz file: %c", compress_byte);
                    i = i + 1;
                end


                if(outStream_TLAST) begin
                    // 输出接收到的数据量到 console 和 输出文件
                    $fdisplay(file_out, "Total data read from output wave: %d", read_cnt);
                    $display("Total data read from output wave: %d", read_cnt);
                    $fclose(file_out);
                    $fclose(file_compress);
                    $finish;  // 结束仿真
                end
            end
        end

        // $finish;
    end

    // 例化 IP
    gzip_0 inst_gzip (
               .inStream_TVALID(inStream_TVALID),    // input wire inStream_inStream_TVALID
               .inStream_TREADY(inStream_TREADY),    // output wire inStream_TREADY
               .inStream_TDATA(inStream_TDATA),      // input wire [63 : 0] inStream_TDATA
               .inStream_TKEEP(inStream_TKEEP),      // input wire [7 : 0] inStream_TKEEP
               .inStream_TSTRB(inStream_TSTRB),      // input wire [7 : 0] inStream_TSTRB
               .inStream_TLAST(inStream_TLAST),      // input wire [0 : 0] inStream_TLAST

               .outStream_TVALID(outStream_TVALID),  // output wire outStream_inStream_TVALID
               .outStream_TREADY(outStream_TREADY),  // input wire outStream_TREADY
               .outStream_TDATA(outStream_TDATA),    // output wire [63 : 0] outStream_TDATA
               .outStream_TKEEP(outStream_TKEEP),    // output wire [7 : 0] outStream_TKEEP
               .outStream_TSTRB(outStream_TSTRB),    // output wire [7 : 0] outStream_TSTRB
               .outStream_TUSER(outStream_TUSER),    // output wire [31 : 0] outStream_TUSER
               .outStream_TLAST(outStream_TLAST),    // output wire [0 : 0] outStream_TLAST

               .ap_clk(clk),                      // input wire ap_clk
               .ap_rst_n(rst_n)                  // input wire ap_rst_n
           );


endmodule
