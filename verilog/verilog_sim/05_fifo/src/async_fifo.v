`timescale 1ns / 1ps

module async_fifo #(
    parameter DATA_WIDTH = 8,
    parameter ADDR_WIDTH = 4
)(
    input  wire                  wr_clk,
    input  wire                  wr_rst_n,
    input  wire                  wr_en,
    input  wire [DATA_WIDTH-1:0] wr_data,
    output wire                  full,

    input  wire                  rd_clk,
    input  wire                  rd_rst_n,
    input  wire                  rd_en,
    output reg  [DATA_WIDTH-1:0] rd_data,
    output wire                  empty
);

localparam DEPTH = 1 << ADDR_WIDTH;

reg [DATA_WIDTH-1:0] mem [0:DEPTH-1];

reg [ADDR_WIDTH:0] wr_bin;
reg [ADDR_WIDTH:0] rd_bin;

reg [ADDR_WIDTH:0] wr_gray;
reg [ADDR_WIDTH:0] rd_gray;

reg [ADDR_WIDTH:0] wr_gray_sync1, wr_gray_sync2;
reg [ADDR_WIDTH:0] rd_gray_sync1, rd_gray_sync2;

wire [ADDR_WIDTH:0] wr_bin_next;
wire [ADDR_WIDTH:0] rd_bin_next;

wire [ADDR_WIDTH:0] wr_gray_next;
wire [ADDR_WIDTH:0] rd_gray_next;

assign wr_bin_next  = wr_bin + ((wr_en && !full) ? 1'b1 : 1'b0);
assign rd_bin_next  = rd_bin + ((rd_en && !empty) ? 1'b1 : 1'b0);

assign wr_gray_next = (wr_bin_next >> 1) ^ wr_bin_next;
assign rd_gray_next = (rd_bin_next >> 1) ^ rd_bin_next;

/*
    写指针逻辑
*/
always @(posedge wr_clk or negedge wr_rst_n) begin
    if (!wr_rst_n) begin
        wr_bin  <= 0;
        wr_gray <= 0;
    end else begin
        wr_bin  <= wr_bin_next;
        wr_gray <= wr_gray_next;

        if (wr_en && !full) begin
            mem[wr_bin[ADDR_WIDTH-1:0]] <= wr_data;
        end
    end
end

/*
    读指针逻辑
*/
always @(posedge rd_clk or negedge rd_rst_n) begin
    if (!rd_rst_n) begin
        rd_bin  <= 0;
        rd_gray <= 0;
        rd_data <= 0;
    end else begin
        rd_bin  <= rd_bin_next;
        rd_gray <= rd_gray_next;

        if (rd_en && !empty) begin
            rd_data <= mem[rd_bin[ADDR_WIDTH-1:0]];
        end
    end
end

/*
    写指针同步到读时钟域
*/
always @(posedge rd_clk or negedge rd_rst_n) begin
    if (!rd_rst_n) begin
        wr_gray_sync1 <= 0;
        wr_gray_sync2 <= 0;
    end else begin
        wr_gray_sync1 <= wr_gray;
        wr_gray_sync2 <= wr_gray_sync1;
    end
end

/*
    读指针同步到写时钟域
*/
always @(posedge wr_clk or negedge wr_rst_n) begin
    if (!wr_rst_n) begin
        rd_gray_sync1 <= 0;
        rd_gray_sync2 <= 0;
    end else begin
        rd_gray_sync1 <= rd_gray;
        rd_gray_sync2 <= rd_gray_sync1;
    end
end

/*
    empty 判断：
    读指针 == 同步过来的写指针
*/
assign empty = (rd_gray_next == wr_gray_sync2);

/*
    full 判断：
    写指针即将追上读指针一圈
*/
assign full = (wr_gray_next == {
    ~rd_gray_sync2[ADDR_WIDTH:ADDR_WIDTH-1],
     rd_gray_sync2[ADDR_WIDTH-2:0]
});


endmodule