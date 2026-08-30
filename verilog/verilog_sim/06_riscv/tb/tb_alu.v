`timescale 1ns/1ps
`include "rv32_defs.vh"

module tb_alu;
    reg  [31:0] a;
    reg  [31:0] b;
    reg  [3:0]  op;
    wire [31:0] y;
    integer errors;

    initial begin
        //! 这里的当前目录是 makefile 所在目录，所以不需要加 ../
        $dumpfile("wave/tb_alu.vcd");
        $dumpvars(0, tb_alu);
    end

    rv32_alu dut (  .a(a), 
                    .b(b), 
                    .op(op), 
                    .y(y));

    task check;
        input [3:0]  t_op;
        input [31:0] t_a;
        input [31:0] t_b;
        input [31:0] expected;
        begin
            op = t_op; a = t_a; b = t_b; #1;
            if (y !== expected) begin
                $display("ALU FAIL op=%0d a=%h b=%h got=%h expected=%h",
                         t_op, t_a, t_b, y, expected);
                errors = errors + 1;
            end
        end
    endtask

    initial begin
        errors = 0;
        check(`RV32_ALU_ADD,  32'd7, 32'd5, 32'd12);
        check(`RV32_ALU_SUB,  32'd7, 32'd5, 32'd2);
        check(`RV32_ALU_SLL,  32'h1, 32'd31, 32'h8000_0000);
        check(`RV32_ALU_SLT,  32'hffff_ffff, 32'd1, 32'd1);
        check(`RV32_ALU_SLTU, 32'hffff_ffff, 32'd1, 32'd0);
        check(`RV32_ALU_XOR,  32'h55aa_00ff, 32'hffff_0000, 32'haa55_00ff);
        check(`RV32_ALU_SRL,  32'h8000_0000, 32'd4, 32'h0800_0000);
        check(`RV32_ALU_SRA,  32'h8000_0000, 32'd4, 32'hf800_0000);
        check(`RV32_ALU_OR,   32'h5500_00ff, 32'h00aa_ff00, 32'h55aa_ffff);
        check(`RV32_ALU_AND,  32'h55aa_00ff, 32'h0ff0_0ff0, 32'h05a0_00f0);
        if (errors == 0) $display("TB_ALU PASS");
        else $fatal(1, "TB_ALU FAIL: %0d errors", errors);
        $finish;
    end
endmodule
