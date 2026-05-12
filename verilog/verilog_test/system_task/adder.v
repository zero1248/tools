`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2023/06/02 19:25:52
// Design Name:
// Module Name: adder
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


module adder #(
                 parameter integer DATA_WIDTH = 32
                )
    (
        input wire clk,
        input wire rst_n,
        input wire [DATA_WIDTH-1: 0] a,
        input wire [DATA_WIDTH-1: 0] b,
        output reg [DATA_WIDTH-1: 0]sum
    );

    always @(posedge clk) begin
        if(!rst_n) begin
            sum <= {(DATA_WIDTH){1'b0}};
        end

        else begin
            sum <= a + b;
        end
    end

endmodule
