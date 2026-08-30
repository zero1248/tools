module simple_soc #(
    parameter MEM_WORDS = 4096,
    parameter MEM_FILE  = "src/smoke.hex"
) (
    input  wire       clk,
    input  wire       rst_n,
    output reg        tohost_valid,
    output reg [31:0] tohost_data,
    output reg [31:0] gpio_out,
    output wire       trap
);
    localparam TOHOST_ADDR = 32'h1000_0000;
    localparam GPIO_ADDR   = 32'h1000_0004;

    reg [31:0] mem [0:MEM_WORDS-1];
    integer k;

    wire [31:0] imem_addr;
    wire [31:0] imem_rdata;
    wire        dmem_valid;
    wire        dmem_we;
    wire [3:0]  dmem_wstrb;
    wire [31:0] dmem_addr;
    wire [31:0] dmem_wdata;
    reg  [31:0] dmem_rdata;
    wire [31:0] dbg_pc;
    wire [31:0] dbg_instr;
    wire [31:0] trap_pc;

    initial begin
        for (k = 0; k < MEM_WORDS; k = k + 1)
            mem[k] = 32'h0000_0013;
        $readmemh(MEM_FILE, mem);
    end

    assign imem_rdata = (imem_addr[31:2] < MEM_WORDS) ?
                        mem[imem_addr[31:2]] : 32'h0000_0013;

    always @* begin
        if (dmem_addr[31:2] < MEM_WORDS)
            dmem_rdata = mem[dmem_addr[31:2]];
        else if (dmem_addr == GPIO_ADDR)
            dmem_rdata = gpio_out;
        else
            dmem_rdata = 32'b0;
    end

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            tohost_valid <= 1'b0;
            tohost_data  <= 32'b0;
            gpio_out     <= 32'b0;
        end else if (dmem_valid && dmem_we) begin
            if (dmem_addr[31:2] < MEM_WORDS) begin
                if (dmem_wstrb[0]) mem[dmem_addr[31:2]][7:0]   <= dmem_wdata[7:0];
                if (dmem_wstrb[1]) mem[dmem_addr[31:2]][15:8]  <= dmem_wdata[15:8];
                if (dmem_wstrb[2]) mem[dmem_addr[31:2]][23:16] <= dmem_wdata[23:16];
                if (dmem_wstrb[3]) mem[dmem_addr[31:2]][31:24] <= dmem_wdata[31:24];
            end else if (dmem_addr == TOHOST_ADDR) begin
                tohost_valid <= 1'b1;
                tohost_data  <= dmem_wdata;
            end else if (dmem_addr == GPIO_ADDR) begin
                if (dmem_wstrb[0]) gpio_out[7:0]   <= dmem_wdata[7:0];
                if (dmem_wstrb[1]) gpio_out[15:8]  <= dmem_wdata[15:8];
                if (dmem_wstrb[2]) gpio_out[23:16] <= dmem_wdata[23:16];
                if (dmem_wstrb[3]) gpio_out[31:24] <= dmem_wdata[31:24];
            end
        end
    end

    rv32_core_singlecycle u_core (
        .clk(clk), .rst_n(rst_n),
        .imem_addr(imem_addr), .imem_rdata(imem_rdata),
        .dmem_valid(dmem_valid), .dmem_we(dmem_we), .dmem_wstrb(dmem_wstrb),
        .dmem_addr(dmem_addr), .dmem_wdata(dmem_wdata), .dmem_rdata(dmem_rdata),
        .trap(trap), .trap_pc(trap_pc), .dbg_pc(dbg_pc), .dbg_instr(dbg_instr)
    );
endmodule
