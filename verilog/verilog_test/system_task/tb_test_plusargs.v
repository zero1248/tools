`timescale 1ns / 1ps

module tb_test_plusargs();
reg [8*32: 1] testname;

initial begin
    if($value$plusargs("TESTNAME=%0s", testname)) 
        $display("TESTNAME = %0s", testname);
end

initial begin
    if($test$plusargs("HELLO")) $display("Hello argument found.");
    if($test$plusargs("HE"))   $display("The HE subset string is detected.");
    if($test$plusargs("H"))    $display("Argument starting with H found.");
    if($test$plusargs("HELLO_HERE"))$display("Long argument.");
    if($test$plusargs("HI"))   $display("Simple greeting.");
    if($test$plusargs("LO"))   $display("Does not match.");
end

endmodule

