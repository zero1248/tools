`include "rv32_defs.vh"

module rv32_decoder (
    input  wire [31:0] instr,
    output reg         reg_write,
    output reg         alu_src_pc,
    output reg         alu_src_imm,
    output reg  [3:0]  alu_op,
    output reg  [1:0]  wb_sel,
    output reg         mem_read,
    output reg         mem_write,
    output reg         branch,
    output reg         jump,
    output reg         jalr,
    output reg  [2:0]  imm_sel,
    output reg         illegal
);
    wire [6:0] opcode = instr[6:0];
    wire [2:0] funct3 = instr[14:12];
    wire [6:0] funct7 = instr[31:25];

    always @* begin
        reg_write  = 1'b0;
        alu_src_pc = 1'b0;
        alu_src_imm= 1'b0;
        alu_op     = `RV32_ALU_ADD;
        wb_sel     = `RV32_WB_ALU;
        mem_read   = 1'b0;
        mem_write  = 1'b0;
        branch     = 1'b0;
        jump       = 1'b0;
        jalr       = 1'b0;
        imm_sel    = `RV32_IMM_I;
        illegal    = 1'b0;

        case (opcode)
            `RV32_OP_LUI: begin
                reg_write   = 1'b1;
                alu_src_imm = 1'b1;
                imm_sel     = `RV32_IMM_U;
            end
            `RV32_OP_AUIPC: begin
                reg_write   = 1'b1;
                alu_src_pc  = 1'b1;
                alu_src_imm = 1'b1;
                imm_sel     = `RV32_IMM_U;
            end
            `RV32_OP_JAL: begin
                reg_write = 1'b1;
                wb_sel    = `RV32_WB_PC4;
                jump      = 1'b1;
                imm_sel   = `RV32_IMM_J;
            end
            `RV32_OP_JALR: begin
                reg_write = 1'b1;
                wb_sel    = `RV32_WB_PC4;
                jump      = 1'b1;
                jalr      = 1'b1;
                imm_sel   = `RV32_IMM_I;
                if (funct3 != 3'b000)
                    illegal = 1'b1;
            end
            `RV32_OP_BRANCH: begin
                branch   = 1'b1;
                imm_sel  = `RV32_IMM_B;
                if (!((funct3 == 3'b000) || (funct3 == 3'b001) ||
                      (funct3 == 3'b100) || (funct3 == 3'b101) ||
                      (funct3 == 3'b110) || (funct3 == 3'b111)))
                    illegal = 1'b1;
            end
            `RV32_OP_LOAD: begin
                reg_write   = 1'b1;
                alu_src_imm = 1'b1;
                wb_sel      = `RV32_WB_MEM;
                mem_read    = 1'b1;
                imm_sel     = `RV32_IMM_I;
                if (!((funct3 == 3'b000) || (funct3 == 3'b001) ||
                      (funct3 == 3'b010) || (funct3 == 3'b100) ||
                      (funct3 == 3'b101)))
                    illegal = 1'b1;
            end
            `RV32_OP_STORE: begin
                alu_src_imm = 1'b1;
                mem_write   = 1'b1;
                imm_sel     = `RV32_IMM_S;
                if (!((funct3 == 3'b000) || (funct3 == 3'b001) ||
                      (funct3 == 3'b010)))
                    illegal = 1'b1;
            end
            `RV32_OP_OPIMM: begin
                reg_write   = 1'b1;
                alu_src_imm = 1'b1;
                imm_sel     = `RV32_IMM_I;
                case (funct3)
                    3'b000: alu_op = `RV32_ALU_ADD;
                    3'b010: alu_op = `RV32_ALU_SLT;
                    3'b011: alu_op = `RV32_ALU_SLTU;
                    3'b100: alu_op = `RV32_ALU_XOR;
                    3'b110: alu_op = `RV32_ALU_OR;
                    3'b111: alu_op = `RV32_ALU_AND;
                    3'b001: begin
                        alu_op = `RV32_ALU_SLL;
                        if (funct7 != 7'b0000000) illegal = 1'b1;
                    end
                    3'b101: begin
                        if (funct7 == 7'b0000000)
                            alu_op = `RV32_ALU_SRL;
                        else if (funct7 == 7'b0100000)
                            alu_op = `RV32_ALU_SRA;
                        else
                            illegal = 1'b1;
                    end
                    default: illegal = 1'b1;
                endcase
            end
            `RV32_OP_OP: begin
                reg_write = 1'b1;
                case (funct3)
                    3'b000: begin
                        if (funct7 == 7'b0000000) alu_op = `RV32_ALU_ADD;
                        else if (funct7 == 7'b0100000) alu_op = `RV32_ALU_SUB;
                        else illegal = 1'b1;
                    end
                    3'b001: begin alu_op = `RV32_ALU_SLL;  if (funct7 != 0) illegal = 1'b1; end
                    3'b010: begin alu_op = `RV32_ALU_SLT;  if (funct7 != 0) illegal = 1'b1; end
                    3'b011: begin alu_op = `RV32_ALU_SLTU; if (funct7 != 0) illegal = 1'b1; end
                    3'b100: begin alu_op = `RV32_ALU_XOR;  if (funct7 != 0) illegal = 1'b1; end
                    3'b101: begin
                        if (funct7 == 7'b0000000) alu_op = `RV32_ALU_SRL;
                        else if (funct7 == 7'b0100000) alu_op = `RV32_ALU_SRA;
                        else illegal = 1'b1;
                    end
                    3'b110: begin alu_op = `RV32_ALU_OR;   if (funct7 != 0) illegal = 1'b1; end
                    3'b111: begin alu_op = `RV32_ALU_AND;  if (funct7 != 0) illegal = 1'b1; end
                    default: illegal = 1'b1;
                endcase
            end
            `RV32_OP_MISC: begin
                if (!((funct3 == 3'b000) || (funct3 == 3'b001)))
                    illegal = 1'b1;
            end
            `RV32_OP_SYSTEM: begin
                // ECALL/EBREAK/CSR are added in the privileged-architecture stage.
                illegal = 1'b1;
            end
            default: illegal = 1'b1;
        endcase
    end
endmodule
