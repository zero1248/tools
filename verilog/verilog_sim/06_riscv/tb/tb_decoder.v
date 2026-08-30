`timescale 1ns/1ps
`include "rv32_defs.vh"

module tb_decoder;
    reg [31:0] instr;
    wire reg_write, alu_src_pc, alu_src_imm;
    wire [3:0] alu_op;
    wire [1:0] wb_sel;
    wire mem_read, mem_write, branch, jump, jalr;
    wire [2:0] imm_sel;
    wire illegal;

    rv32_decoder dut (
        .instr(instr), 
        .reg_write(reg_write), 
        .alu_src_pc(alu_src_pc),
        .alu_src_imm(alu_src_imm), 
        .alu_op(alu_op), 
        .wb_sel(wb_sel),
        .mem_read(mem_read), 
        .mem_write(mem_write), 
        .branch(branch),
        .jump(jump), 
        .jalr(jalr), 
        .imm_sel(imm_sel), 
        .illegal(illegal)
    );

    initial begin
        instr = 32'h0050_0093; #1; // addi x1,x0,5
        if (illegal || !reg_write || !alu_src_imm || alu_op != `RV32_ALU_ADD)
            $fatal(1, "ADDI decode failed");

        instr = 32'h0030_2023; #1; // sw x3,0(x0)
        if (illegal || !mem_write || reg_write || imm_sel != `RV32_IMM_S)
            $fatal(1, "SW decode failed");

        instr = 32'h0241_9063; #1; // bne
        if (illegal || !branch || imm_sel != `RV32_IMM_B)
            $fatal(1, "BNE decode failed");

        instr = 32'h0200_0033; #1; // mul x0,x0,x0: M is not implemented yet
        if (!illegal) $fatal(1, "unsupported MUL was not marked illegal");

        $display("TB_DECODER PASS");
        $finish;
    end
endmodule
