`timescale 1ns / 1ps

module tb_value_plusargs();
reg [8*32: 1] testname;
real frequency;

initial begin
    if($value$plusargs("TESTNAME=%0s", testname)) 
        $display("TESTNAME = %0s", testname);
    if (!($value$plusargs("FREQ+%0F", frequency)))
        frequency = 8.33333; // 166 MHz
    $display("frequency = %f", frequency);
end

endmodule