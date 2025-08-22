`timescale 1ns / 1ps

module ali_dmod_tb;

// Parameters
localparam integer C_S_AXI_CONTROL_ADDR_WIDTH = 12;
localparam integer C_S_AXI_CONTROL_DATA_WIDTH = 32;
localparam integer C_OUT_TDATA_WIDTH = 64;
localparam integer C_IN_TDATA_WIDTH = 64;
localparam integer C_TUSER_WIDTH = 8;

//Ports
reg  ap_clk;
reg  ap_rst_n;

reg  s_axi_control_awvalid;
wire  s_axi_control_awready;
reg [C_S_AXI_CONTROL_ADDR_WIDTH-1:0] s_axi_control_awaddr;

// 读写 AXI BRAM Controller 时，必须加上 wlast 信号，才能收到 B 通道的 bvalid 信号
reg  s_axi_control_wvalid;
wire  s_axi_control_wready;
reg [C_S_AXI_CONTROL_DATA_WIDTH-1:0] s_axi_control_wdata;
reg [C_S_AXI_CONTROL_DATA_WIDTH/8-1:0] s_axi_control_wstrb;

reg  s_axi_control_arvalid;
wire  s_axi_control_arready;
reg [C_S_AXI_CONTROL_ADDR_WIDTH-1:0] s_axi_control_araddr;

wire  s_axi_control_rvalid;
reg  s_axi_control_rready;
wire [C_S_AXI_CONTROL_DATA_WIDTH-1:0] s_axi_control_rdata;
wire [2-1:0] s_axi_control_rresp;

wire  s_axi_control_bvalid;
reg  s_axi_control_bready;
wire [2-1:0] s_axi_control_bresp;

ali_dmod # (
  .C_S_AXI_CONTROL_ADDR_WIDTH(C_S_AXI_CONTROL_ADDR_WIDTH),
  .C_S_AXI_CONTROL_DATA_WIDTH(C_S_AXI_CONTROL_DATA_WIDTH),
  .C_OUT_TDATA_WIDTH(C_OUT_TDATA_WIDTH),
  .C_IN_TDATA_WIDTH(C_IN_TDATA_WIDTH),
  .C_TUSER_WIDTH(C_TUSER_WIDTH)
)
    ali_dmod_inst (
    .ap_clk(ap_clk),
    .ap_rst_n(ap_rst_n),

    .s_axi_control_awvalid(s_axi_control_awvalid),
    .s_axi_control_awready(s_axi_control_awready),
    .s_axi_control_awaddr(s_axi_control_awaddr),

    .s_axi_control_wvalid(s_axi_control_wvalid),
    .s_axi_control_wready(s_axi_control_wready),
    .s_axi_control_wdata(s_axi_control_wdata),
    .s_axi_control_wstrb(s_axi_control_wstrb),

    .s_axi_control_arvalid(s_axi_control_arvalid),
    .s_axi_control_arready(s_axi_control_arready),
    .s_axi_control_araddr(s_axi_control_araddr),

    .s_axi_control_rvalid(s_axi_control_rvalid),
    .s_axi_control_rready(s_axi_control_rready),
    .s_axi_control_rdata(s_axi_control_rdata),
    .s_axi_control_rresp(s_axi_control_rresp),
    
    .s_axi_control_bvalid(s_axi_control_bvalid),
    .s_axi_control_bready(s_axi_control_bready),
    .s_axi_control_bresp(s_axi_control_bresp)
    );

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

    // 测试主程序
    initial begin

        // 接口初始化
        s_axi_control_awaddr = 0;
        s_axi_control_awvalid = 0;
        s_axi_control_wdata = 0;
        s_axi_control_wstrb = 0;
        s_axi_control_wvalid = 0;
        s_axi_control_bready = 0;
        s_axi_control_araddr = 0;
        s_axi_control_arvalid = 0;
        s_axi_control_rready = 0;

    
        // 等待复位完成
        wait(ap_rst_n);

        #1000;


        // 测试1: 写入数据到地址 h0000_0010
        axi_write(12'h010, 32'h1111_1111, 4'b1111);
        axi_write(12'h018, 32'h2222_2222, 4'b1111);
        axi_write(12'h020, 32'h3333_3333, 4'b1111);
    
        // 测试2: 从地址 h0000_0010 读取数据
        axi_read(12'h010);
        // 检查读取~数据是否与写入一致
        if (s_axi_control_rdata === 32'h1111_1111) begin
            $display("[PASS] 读数据匹配");
        end else begin
            $display("[FAIL] 期望值 0x1111_1111, 实际值 0x%h", s_axi_control_rdata);
        end

        axi_read(12'h018);
        // 检查读取~数据是否与写入一致
        if (s_axi_control_rdata === 32'h2222_2222) begin
            $display("[PASS] 读数据匹配");
        end else begin
            $display("[FAIL] 期望值 0x2222_2222, 实际值 0x%h", s_axi_control_rdata);
        end

        axi_read(12'h020);
        // 检查读取~数据是否与写入一致
        if (s_axi_control_rdata === 32'h3333_3333) begin
            $display("[PASS] 读数据匹配");
        end else begin
            $display("[FAIL] 期望值 0x3333_3333, 实际值 0x%h", s_axi_control_rdata);
        end



        #100;
        $finish;
    end

    //--------------------------------------------------------------
    // AXI-Lite 写入任务（封装 AW/W/B 通道操作）
    //--------------------------------------------------------------
    task axi_write;
        input [11:0] addr;
        input [31:0] data;
        input [3:0]  strb;
        
        begin
            // AW 通道发送地址
            @(posedge ap_clk);
            s_axi_control_awaddr <= addr;
            s_axi_control_awvalid <= 1'b1;
            // 等待从机就绪
            wait(s_axi_control_awready); 
            @(posedge ap_clk);
            s_axi_control_awvalid <= 1'b0;

            // #20;

            // W 通道发送数据
            @(posedge ap_clk);
            s_axi_control_wdata <= data;
            s_axi_control_wstrb <= strb;
            s_axi_control_wvalid <= 1'b1;
            // 等待从机就绪
            wait(s_axi_control_wready); 
            @(posedge ap_clk);
            s_axi_control_wvalid <= 1'b0;

            // #20;

            // B 通道接收写响应
            s_axi_control_bready <= 1'b1;
            wait(s_axi_control_bvalid); // 等待响应
            @(posedge ap_clk);
            s_axi_control_bready <= 1'b0;

            // 检查响应是否 OKAY
            if (s_axi_control_bresp !== 2'b00) begin
                $display("[ERROR] 写入响应错误: 0x%h", s_axi_control_bresp);
            end
            else begin
                $display("[SUCCESS] 数据 0x%h 写入地址 0x%h 成功", data, addr); 
            end
        end
    endtask


    //--------------------------------------------------------------
    // AXI-Lite 读取任务（封装 AR/R 通道操作）    
    //--------------------------------------------------------------
    task axi_read;
        input [11: 0] addr;
        begin
            // AR 通道发送地址
            @(posedge ap_clk);
            s_axi_control_araddr <= addr;
            s_axi_control_arvalid <= 1'b1;
            // 等待从机就绪
            wait(s_axi_control_arready); 
            @(posedge ap_clk);
            s_axi_control_arvalid <= 1'b0;

            // R 通道接收响应及读数据
            s_axi_control_rready <= 1'b1;
            wait(s_axi_control_rvalid); // 等待数据
            @(posedge ap_clk);
            s_axi_control_rready <= 1'b0;

            // 检查响应是否 OKAY
            if (s_axi_control_rresp !== 2'b00) begin
                $display("[ERROR] 读取响应错误: 0x%h", s_axi_control_rresp);
            end
        end
    endtask

  

    // 显示状态机名称
    reg [63: 0] wstate_r;
    always @(*) begin
        case(ali_dmod_inst.inst_control_s_axi.wstate)
            2'd0:       wstate_r = "WR_IDLE ";
            2'd1:       wstate_r = "WR_DATA ";
            2'd2:       wstate_r = "WR_RESP ";
            2'd3:       wstate_r = "WR_RST  ";
        endcase
    end

    // // 仿真波形记录
    // initial begin
    //     $dumpfile("wave.vcd");
    //     $dumpvars(0, axi_lite_tb);
    // end

endmodule









