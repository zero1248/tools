`timescale 1ns/1ps

module tb_soc #(
    parameter MEM_FILE = "src/smoke.hex"
);
    reg clk = 1'b0;
    reg rst_n = 1'b0;
    wire tohost_valid;
    wire [31:0] tohost_data;
    wire [31:0] gpio_out;
    wire trap;
    integer cycles;

    always #5 clk = ~clk;

    simple_soc #(.MEM_FILE(MEM_FILE)) dut (
        .clk(clk), 
        .rst_n(rst_n), 
        .tohost_valid(tohost_valid),
        .tohost_data(tohost_data), 
        .gpio_out(gpio_out), 
        .trap(trap)
    );

    initial begin
        $dumpfile("wave/tb_soc.vcd");
        $dumpvars(0, tb_soc);
        repeat (5) @(posedge clk);
        rst_n <= 1'b1;

        cycles = 0;
        while (!tohost_valid && !trap && cycles < 200) begin
            @(posedge clk);
            cycles = cycles + 1;
        end

        if (trap) $fatal(1, "CPU trapped before program completion");
        if (!tohost_valid) $fatal(1, "timeout waiting for tohost");
        if (tohost_data !== 32'd1)
            $fatal(1, "program failed, tohost=%h", tohost_data);

        $display("TB_SOC PASS in %0d cycles", cycles);
        $finish;
    end
endmodule
