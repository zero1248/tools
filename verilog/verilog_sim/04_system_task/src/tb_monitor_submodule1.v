`timescale 1ns / 1ps

module tb_monitor_submodule1(
    input wire clk,
    input wire [31: 0] data
);

initial begin
    $monitor("sub1 @ %t: data = %0d", $time, data);
end

endmodule
