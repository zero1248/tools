`include "rv32_defs.vh"

module rv32_alu (
    input  wire [31:0] a,
    input  wire [31:0] b,
    input  wire [3:0]  op,
    output reg  [31:0] y
);
    always @* begin
        case (op)
            `RV32_ALU_ADD:  y = a + b;
            `RV32_ALU_SUB:  y = a - b;
            `RV32_ALU_SLL:  y = a << b[4:0];  
            `RV32_ALU_SLT:  y = ($signed(a) < $signed(b)) ? 32'd1 : 32'd0;
            `RV32_ALU_SLTU: y = (a < b) ? 32'd1 : 32'd0;
            `RV32_ALU_XOR:  y = a ^ b;
            `RV32_ALU_SRL:  y = a >> b[4:0];
            `RV32_ALU_SRA:  y = $signed(a) >>> b[4:0];
            `RV32_ALU_OR:   y = a | b;
            `RV32_ALU_AND:  y = a & b;
            default:        y = 32'b0;
        endcase
    end
endmodule
