`timescale 1 ns/1 ns  

module adder4b_half(  
    input clk     ,  
    input rst_n   ,


    input       [3 : 0]  a  ,  
    input       [3 : 0]  b  ,
    output reg  [4 : 0]  out 
);

    always@(posedge clk or negedge rst_n) begin 
        if(rst_n==1'b0)
            out <= 4'd0;  
        else 
            out <= a + b;  
    end


endmodule