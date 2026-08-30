`timescale 1ns/1ps

module tb_regfile;
    reg clk = 1'b0;
    reg rst_n = 1'b0;
    reg [4:0] rs1_addr = 0;
    reg [4:0] rs2_addr = 0;
    wire [31:0] rs1_data;
    wire [31:0] rs2_data;
    reg rd_we = 0;
    reg [4:0] rd_addr = 0;
    reg [31:0] rd_data = 0;

    always #5 clk = ~clk;

    rv32_regfile dut (
        .clk(clk), .rst_n(rst_n), .rs1_addr(rs1_addr), .rs2_addr(rs2_addr),
        .rs1_data(rs1_data), .rs2_data(rs2_data), .rd_we(rd_we),
        .rd_addr(rd_addr), .rd_data(rd_data)
    );

    initial begin
        repeat (2) @(posedge clk);
        rst_n <= 1'b1;
        @(posedge clk);
        rd_we <= 1'b1; rd_addr <= 5'd3; rd_data <= 32'h1234_5678;
        @(posedge clk);
        rd_we <= 1'b0; rs1_addr <= 5'd3;
        #1;
        if (rs1_data !== 32'h1234_5678) $fatal(1, "x3 write/read failed");

        @(posedge clk);
        rd_we <= 1'b1; rd_addr <= 5'd0; rd_data <= 32'hffff_ffff;
        @(posedge clk);
        rd_we <= 1'b0; rs1_addr <= 5'd0;
        #1;
        if (rs1_data !== 32'b0) $fatal(1, "x0 is not hard-wired to zero");

        $display("TB_REGFILE PASS");
        $finish;
    end
endmodule
