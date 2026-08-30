`timescale 1ns / 1ps

module tb_async_fifo;

parameter DATA_WIDTH = 8;
parameter ADDR_WIDTH = 8;

reg wr_clk;
reg rd_clk;
reg wr_rst_n;
reg rd_rst_n;

reg wr_en;
reg [DATA_WIDTH-1:0] wr_data;
wire full;

reg rd_en;
wire [DATA_WIDTH-1:0] rd_data;
wire empty;

async_fifo #(
    .DATA_WIDTH(DATA_WIDTH),
    .ADDR_WIDTH(ADDR_WIDTH)
) u_fifo (
    .wr_clk   (wr_clk),
    .wr_rst_n (wr_rst_n),
    .wr_en    (wr_en),
    .wr_data  (wr_data),
    .full     (full),

    .rd_clk   (rd_clk),
    .rd_rst_n (rd_rst_n),
    .rd_en    (rd_en),
    .rd_data  (rd_data),
    .empty    (empty)
);


    /*
        写时钟：10ns 周期
    */
    initial begin
        wr_clk = 0;
        forever #5 wr_clk = ~wr_clk;
    end

    /*
        读时钟：14ns 周期
    */
    initial begin
        rd_clk = 0;
        forever #7 rd_clk = ~rd_clk;
    end

    /*
        复位
    */
    initial begin
        wr_rst_n = 0;
        rd_rst_n = 0;
        wr_en = 0;
        rd_en = 0;
        wr_data = 0;

        #30;
        wr_rst_n = 1;
        rd_rst_n = 1;
    end

    /*
        写数据
    */
    // initial begin
    //     wait(wr_rst_n == 1);

    //     repeat (30) begin
    //         @(posedge wr_clk);
    //         if (!full) begin
    //             wr_en   <= 1;
    //             wr_data <= wr_data + 1;
    //         end else begin
    //             wr_en <= 0;
    //         end
    //     end

    //     @(posedge wr_clk);
    //     wr_en <= 0;
    // end
    integer wr_cnt;

    initial begin
        wait(wr_rst_n == 1);

        wr_cnt = 0;
        while (wr_cnt < 30) begin
            @(posedge wr_clk);
            if (!full) begin
                wr_en   <= 1;
                wr_data <= wr_cnt;
                wr_cnt  <= wr_cnt + 1;
            end else begin
                wr_en <= 0;
            end
        end

        @(posedge wr_clk);
        wr_en <= 0;
    end

    /*
        读数据
    */
    // initial begin
    //     wait(rd_rst_n == 1);

    //     #80;

    //     repeat (30) begin
    //         @(posedge rd_clk);
    //         if (!empty) begin
    //             rd_en <= 1;
    //         end else begin
    //             rd_en <= 0;
    //         end
    //     end

    //     @(posedge rd_clk);
    //     rd_en <= 0;
    // end
    integer rd_cnt;

    initial begin
        wait(rd_rst_n == 1);

        #80;
        rd_cnt = 0;

        while (rd_cnt < 30) begin
            @(posedge rd_clk);
            if (!empty) begin
                rd_en  <= 1;
                rd_cnt <= rd_cnt + 1;
            end else begin
                rd_en <= 0;
            end
        end

        @(posedge rd_clk);
        rd_en <= 0;

        #100;
        $finish;
    end

    /*
        打印读出数据
    */
    // always @(posedge rd_clk) begin
    //     if (rd_en && !empty) begin
    //         $display("[%0t] read data = %0d", $time, rd_data);
    //     end
    // end
    always @(posedge rd_clk) begin
        if (rd_en && !empty) begin
            #1;
            $display("[%0t] read data = %0d", $time, rd_data);
        end
    end

    initial begin
        $dumpfile("wave/tb_async_fifo.vcd");
        $dumpvars(0, tb_async_fifo);

        #1000;
        $finish;
    end



endmodule