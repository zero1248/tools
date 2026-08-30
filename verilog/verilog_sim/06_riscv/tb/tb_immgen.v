`timescale 1ns/1ps
`include "rv32_defs.vh"

module tb_immgen;
    reg [31:0] instr;
    reg [2:0] imm_sel;
    wire [31:0] imm;
    integer errors;

    rv32_immgen dut (.instr(instr), .imm_sel(imm_sel), .imm(imm));

    task check;
        input [31:0] t_instr;
        input [2:0]  t_sel;
        input [31:0] expected;
        begin
            instr = t_instr; imm_sel = t_sel; #1;
            if (imm !== expected) begin
                $display("IMM FAIL instr=%h got=%h expected=%h", t_instr, imm, expected);
                errors = errors + 1;
            end
        end
    endtask

    initial begin
        errors = 0;
        check(32'hfff0_0093, `RV32_IMM_I, 32'hffff_ffff); // addi x1,x0,-1
        check(32'h0031_2623, `RV32_IMM_S, 32'd12);        // sw x3,12(x2)
        check(32'h0241_9063, `RV32_IMM_B, 32'd32);        // bne x3,x4,+32
        check(32'h1234_52b7, `RV32_IMM_U, 32'h1234_5000); // lui x5,0x12345
        check(32'hffdf_f06f, `RV32_IMM_J, 32'hffff_fffc); // jal x0,-4
        if (errors == 0) $display("TB_IMMGEN PASS");
        else $fatal(1, "TB_IMMGEN FAIL: %0d errors", errors);
        $finish;
    end
endmodule
