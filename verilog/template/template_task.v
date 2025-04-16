// task  通过参数传递结果
// task 可以直接访问 module 中的其他寄存器，不需要传参
// task 比 function 更通用
// task 的典型应用场景式时序控制、复杂过程

task task_template;
    input integer input_param;    // 输入参数
    input [31: 0] input_data;     // 输入数据
    reg [64:0] tmp;               // 内部变量
    output [31: 0] output_data;
begin
       
end
endtask



//--------------------------------------------------------------
// AXI-Lite 写入任务（封装 AW/W/B 通道操作）
//--------------------------------------------------------------
task axi_write;
input [31: 0] addr;
input [31: 0] data;
input [3: 0]  strb;

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




