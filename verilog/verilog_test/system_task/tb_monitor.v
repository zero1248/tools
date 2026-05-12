`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/09 22:02:03
// Design Name: 
// Module Name: tb_monitor
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module tb_monitor();

//     reg [31: 0] data1;
//     reg [31: 0] data2;
//     reg clk;
    
//     initial begin
//         clk = 0;
//         data1 = 0;
//         data2 = 0;
//         forever #5 clk = ~clk;
//     end
    
//     initial begin
//         #10;
//         $monitor("At time %0t, data1=%0d, data2=%0d", $time, data1, data2);
        
//         #20;
//         data1 = 10;

//         #30;
//         data2 = 20;

//         #10;
//         data1 = 30;
//         $monitoroff;

//         #10;
//         data1 = 40;

//         #10;
//         data2 = 50;
//         $monitoron;

//         #10;
//         data1 = 60;
        
//         #10;
//         $monitoroff;
        
//         #10;
//         data2 = 70;
//         $monitor("new task: At time %0t, data1=%0d, data2=%0d", $time, data1, data2);
        
//         #10;
//         data1 = 80;
        
//         #10;
//         data2 = 90;
//         $monitoron;
        
//         #10;
//         data1 = 100;
        
//         #10;
//         data2 = 110;
        
//         #10;
//         data1 = 120;

//         $finish;
//     end
// endmodule

reg a_monitor;
reg b_monitor;

initial begin
    a_monitor=1;
    b_monitor=0;
    $monitor($time, , "a= %b", a_monitor);
    $monitor($time, , "b= %b", b_monitor);
    //$monitor($realtime,,"a=%b,b=%b",a_monitor,b_monitor);
    #1
    a_monitor=0;
    #1
    b_monitor=1;
    #1
    a_monitor=1;
    b_monitor=0;
    #10
    $stop;
end
endmodule

