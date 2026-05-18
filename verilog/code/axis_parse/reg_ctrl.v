`timescale 1ns / 1ps


// REG 采用真双口 RAM
// A 口连帧解析模块，用于 PM 的访问
// B 口连 AM
// 后面可以考虑用单口 RAM，因为大部分时间不会操作这里

module reg_ctrl #(
        parameter integer REG_ADDR_WIDTH	= 10,
        parameter integer REG_DATA_WIDTH	= 32

    )
    (
        // parsing module interface
        input wire [REG_ADDR_WIDTH-1 : 0] par_addr,
        // input wire [REG_DATA_WIDTH-1 : 0] data_from_reg, // ! 暂时不需要，parsing 模块只写不读，读的数据交给 framing 模块组帧
        input wire [REG_DATA_WIDTH-1 : 0] data_from_par,
        input wire par_rd,
        input wire par_wr,
        output reg par_rd_done,
        output reg par_wr_done,

        // algo module interface
        input wire [REG_ADDR_WIDTH-1 : 0] algo_addr,
        input wire [REG_DATA_WIDTH-1 : 0] data_from_algo,
        input wire [REG_DATA_WIDTH-1 : 0] data_to_algo,
        input wire algo_rd,
        input wire algo_wr,
        output reg algo_rd_done,
        output reg algo_wr_done

        // framing module interface
        

    );







    // 实例化 BRAM 32 x 1024
    blk_mem_gen_0 bram_32x1024 (
        .clka(clka),    // input wire clka
        .ena(ena),      // input wire ena
        .wea(wea),      // input wire [0 : 0] wea
        .addra(addra),  // input wire [9 : 0] addra
        .dina(dina),    // input wire [31 : 0] dina
        .douta(douta),  // output wire [31 : 0] douta

        .clkb(clkb),    // input wire clkb
        .enb(enb),      // input wire enb
        .web(web),      // input wire [0 : 0] web
        .addrb(addrb),  // input wire [9 : 0] addrb
        .dinb(dinb),    // input wire [31 : 0] dinb
        .doutb(doutb)  // output wire [31 : 0] doutb
      );





endmodule
