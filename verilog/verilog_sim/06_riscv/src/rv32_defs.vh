`ifndef RV32_DEFS_VH
`define RV32_DEFS_VH

`define RV32_ALU_ADD   4'd0
`define RV32_ALU_SUB   4'd1
`define RV32_ALU_SLL   4'd2   // 逻辑左移
`define RV32_ALU_SLT   4'd3   // 有符号数小于比较，若 a<b 则输出1
`define RV32_ALU_SLTU  4'd4   // 无符号数小于比较，若 a<b 则输出1
`define RV32_ALU_XOR   4'd5
`define RV32_ALU_SRL   4'd6   // 逻辑右移
`define RV32_ALU_SRA   4'd7   // 算术右移
`define RV32_ALU_OR    4'd8
`define RV32_ALU_AND   4'd9

`define RV32_IMM_I     3'd0
`define RV32_IMM_S     3'd1
`define RV32_IMM_B     3'd2
`define RV32_IMM_U     3'd3
`define RV32_IMM_J     3'd4

`define RV32_WB_ALU    2'd0
`define RV32_WB_MEM    2'd1
`define RV32_WB_PC4    2'd2

`define RV32_OP_LOAD    7'b0000011
`define RV32_OP_MISC    7'b0001111
`define RV32_OP_OPIMM   7'b0010011
`define RV32_OP_AUIPC   7'b0010111
`define RV32_OP_STORE   7'b0100011
`define RV32_OP_OP      7'b0110011
`define RV32_OP_LUI     7'b0110111
`define RV32_OP_BRANCH  7'b1100011
`define RV32_OP_JALR    7'b1100111
`define RV32_OP_JAL     7'b1101111
`define RV32_OP_SYSTEM  7'b1110011

`endif
