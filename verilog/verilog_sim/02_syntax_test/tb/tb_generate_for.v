`timescale 1ns / 1ps

module tb_generate_for();

    // Parameters
    localparam  WIDTH = 4;

    //Ports
    reg [WIDTH-1: 0] a;
    reg [WIDTH-1: 0] b;
    reg cin;
    wire [WIDTH-1: 0] sum;
    wire cout;
    
    initial begin
        $dumpfile("wave/tb_generate_for.vcd");
        $dumpvars(0, tb_generate_for);
    end


    initial begin
        $monitor("Time=%0t | A=%b B=%b Cin=%b | Sum=%b Cout=%b", 
                 $time, a, b, cin, sum, cout);
    end

    initial begin
        // 简单的激励生成
        a = 4'b0000; b = 4'b0000; cin = 0;
        
        #10 a = 4'b0001; b = 4'b0001; cin = 0; // 1+1=2
        #10 a = 4'b0111; b = 4'b0001; cin = 0; // 7+1=8
        #10 a = 4'b1111; b = 4'b0001; cin = 1; // 15+1+1=17
        
        #10 $finish;
    end



    // 使用 generate-for 语句例化 4 个 1b 全加器
    adder4b_full # (
        .WIDTH(WIDTH)
    )
    adder4b_full_inst (
        .a(a),
        .b(b),
        .cin(cin),
        .sum(sum),
        .cout(cout)
    );

endmodule