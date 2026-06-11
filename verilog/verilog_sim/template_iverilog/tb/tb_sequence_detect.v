`include "timescale.v"


module tb_sequence_detect ();

    reg [0: 0] din;
    wire [0: 0] dout;

    reg clk;
    reg rst_n;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("wave/tb_sequence_detect.vcd");
        $dumpvars(0, tb_sequence_detect);
    end

    task send_bit;
        input bit_in;
        begin
            @(negedge clk);
            din = bit_in;
        end
    endtask

    initial begin
        rst_n = 0;
        din = 0;
        #100;
        rst_n = 1;

        @(negedge clk);

        send_bit(1);
        send_bit(0);
        send_bit(1);
        send_bit(1);
        
        send_bit(1);
        send_bit(0);
        send_bit(1);
        send_bit(0);
        
        send_bit(1);
        send_bit(1);
        send_bit(1);
        send_bit(0);
        send_bit(1);
        send_bit(1);

        $finish;

    end


    sequence_detect  sequence_detect_inst (
        .din(din),
        .dout(dout),
        .clk(clk),
        .rst_n(rst_n)
    );

    // 显示状态机名称
    reg [63: 0] wstate_r;
    always @(*) begin
        case(sequence_detect_inst.next_state)  // 可以访问 module 实例化后的某个内部信号，且可嵌套
            5'b00001:       wstate_r = "IDLE ";
            5'b00010:       wstate_r = "S0_1";
            5'b00100:       wstate_r = "S1_10";
            5'b01000:       wstate_r = "S2_101";
            5'b10000:       wstate_r = "S3_1011";
        endcase
    end


endmodule