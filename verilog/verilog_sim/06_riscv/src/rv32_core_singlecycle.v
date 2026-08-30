`include "rv32_defs.vh"

module rv32_core_singlecycle #(
    parameter RESET_PC = 32'h0000_0000
) (
    input  wire        clk,
    input  wire        rst_n,

    output wire [31:0] imem_addr,
    input  wire [31:0] imem_rdata,

    output wire        dmem_valid,
    output wire        dmem_we,
    output reg  [3:0]  dmem_wstrb,
    output wire [31:0] dmem_addr,
    output reg  [31:0] dmem_wdata,
    input  wire [31:0] dmem_rdata,

    output reg         trap,
    output reg  [31:0] trap_pc,
    output wire [31:0] dbg_pc,
    output wire [31:0] dbg_instr
);
    reg [31:0] pc;

    wire [4:0] rs1_addr = imem_rdata[19:15];
    wire [4:0] rs2_addr = imem_rdata[24:20];
    wire [4:0] rd_addr  = imem_rdata[11:7];
    wire [2:0] funct3   = imem_rdata[14:12];

    wire        reg_write_dec;
    wire        alu_src_pc;
    wire        alu_src_imm;
    wire [3:0]  alu_op;
    wire [1:0]  wb_sel;
    wire        mem_read;
    wire        mem_write;
    wire        branch;
    wire        jump;
    wire        jalr;
    wire [2:0]  imm_sel;
    wire        illegal_dec;
    wire [31:0] imm;
    wire [31:0] rs1_data;
    wire [31:0] rs2_data;
    wire        is_lui = (imem_rdata[6:0] == `RV32_OP_LUI);
    wire [31:0] alu_a = is_lui ? 32'b0 : (alu_src_pc ? pc : rs1_data);
    wire [31:0] alu_b = alu_src_imm ? imm : rs2_data;
    wire [31:0] alu_y;

    reg         branch_taken;
    reg  [31:0] load_data;
    wire [31:0] shifted_rdata = dmem_rdata >> ({dmem_addr[1:0], 3'b000});
    wire [31:0] pc_plus4 = pc + 32'd4;
    wire [31:0] direct_target = pc + imm;
    wire [31:0] jump_target = jalr ? ((rs1_data + imm) & 32'hffff_fffe)
                                         : direct_target;
    wire [31:0] control_target = jump ? jump_target : direct_target;
    wire        control_taken = jump | (branch & branch_taken);
    wire        instr_misaligned = control_taken && (control_target[1:0] != 2'b00);

    reg mem_misaligned;
    wire fault_now = illegal_dec | mem_misaligned | instr_misaligned;

    reg [31:0] wb_data;
    wire rd_we = reg_write_dec && !fault_now && !trap;

    assign imem_addr = pc;
    assign dmem_addr = alu_y;
    assign dmem_valid = (mem_read | mem_write) && !fault_now && !trap;
    assign dmem_we = mem_write;
    assign dbg_pc = pc;
    assign dbg_instr = imem_rdata;

    rv32_decoder u_decoder (
        .instr(imem_rdata), .reg_write(reg_write_dec),
        .alu_src_pc(alu_src_pc), .alu_src_imm(alu_src_imm), .alu_op(alu_op),
        .wb_sel(wb_sel), .mem_read(mem_read), .mem_write(mem_write),
        .branch(branch), .jump(jump), .jalr(jalr), .imm_sel(imm_sel),
        .illegal(illegal_dec)
    );

    rv32_immgen u_immgen (.instr(imem_rdata), .imm_sel(imm_sel), .imm(imm));
    rv32_alu u_alu (.a(alu_a), .b(alu_b), .op(alu_op), .y(alu_y));
    rv32_regfile u_regfile (
        .clk(clk), .rst_n(rst_n), .rs1_addr(rs1_addr), .rs2_addr(rs2_addr),
        .rs1_data(rs1_data), .rs2_data(rs2_data), .rd_we(rd_we),
        .rd_addr(rd_addr), .rd_data(wb_data)
    );

    always @* begin
        case (funct3)
            3'b000: branch_taken = (rs1_data == rs2_data);                    // BEQ
            3'b001: branch_taken = (rs1_data != rs2_data);                    // BNE
            3'b100: branch_taken = ($signed(rs1_data) < $signed(rs2_data));   // BLT
            3'b101: branch_taken = ($signed(rs1_data) >= $signed(rs2_data));  // BGE
            3'b110: branch_taken = (rs1_data < rs2_data);                     // BLTU
            3'b111: branch_taken = (rs1_data >= rs2_data);                    // BGEU
            default: branch_taken = 1'b0;
        endcase
    end

    always @* begin
        load_data = 32'b0;
        case (funct3)
            3'b000: load_data = {{24{shifted_rdata[7]}}, shifted_rdata[7:0]};
            3'b001: load_data = {{16{shifted_rdata[15]}}, shifted_rdata[15:0]};
            3'b010: load_data = shifted_rdata;
            3'b100: load_data = {24'b0, shifted_rdata[7:0]};
            3'b101: load_data = {16'b0, shifted_rdata[15:0]};
            default: load_data = 32'b0;
        endcase
    end

    always @* begin
        dmem_wstrb = 4'b0000;
        dmem_wdata = 32'b0;
        case (funct3)
            3'b000: begin
                dmem_wstrb = 4'b0001 << dmem_addr[1:0];
                dmem_wdata = {24'b0, rs2_data[7:0]} << ({dmem_addr[1:0], 3'b000});
            end
            3'b001: begin
                dmem_wstrb = 4'b0011 << dmem_addr[1:0];
                dmem_wdata = {16'b0, rs2_data[15:0]} << ({dmem_addr[1:0], 3'b000});
            end
            3'b010: begin
                dmem_wstrb = 4'b1111;
                dmem_wdata = rs2_data;
            end
            default: begin
                dmem_wstrb = 4'b0000;
                dmem_wdata = 32'b0;
            end
        endcase
    end

    always @* begin
        mem_misaligned = 1'b0;
        if (mem_read || mem_write) begin
            case (funct3)
                3'b001, 3'b101: mem_misaligned = dmem_addr[0];
                3'b010:         mem_misaligned = |dmem_addr[1:0];
                default:        mem_misaligned = 1'b0;
            endcase
        end
    end

    always @* begin
        case (wb_sel)
            `RV32_WB_MEM: wb_data = load_data;
            `RV32_WB_PC4: wb_data = pc_plus4;
            default:      wb_data = alu_y;
        endcase
    end

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            pc      <= RESET_PC;
            trap    <= 1'b0;
            trap_pc <= 32'b0;
        end else if (!trap) begin
            if (fault_now) begin
                trap    <= 1'b1;
                trap_pc <= pc;
            end else if (control_taken) begin
                pc <= control_target;
            end else begin
                pc <= pc_plus4;
            end
        end
    end
endmodule
