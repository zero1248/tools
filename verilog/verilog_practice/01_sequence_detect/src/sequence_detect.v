`include "timescale.v"

module sequence_detect (
    input wire din,
    output reg dout,

    input wire clk,
    input wire rst_n
);

    // sequence to be detect: 1011

    localparam IDLE = 5'b00001;
    localparam S0   = 5'b00010;   // 1
    localparam S1   = 5'b00100;   // 10
    localparam S2   = 5'b01000;   // 101
    localparam S3   = 5'b10000;   // 101

    reg [4: 0] state;
    reg [4: 0] next_state;

    always @(posedge clk) begin
        if(!rst_n) begin
            state <= IDLE;
        end
        else begin
            state <= next_state;
        end
    end

    always @(*) begin
        next_state = state;

        case(state)
            IDLE: begin
                if(din) begin
                    next_state = S0;
                end
                else begin
                    next_state = IDLE;
                end
            end

            S0: begin // 1
                if(din) begin
                    next_state = S0;
                end
                else begin
                    next_state = S1;
                end
            end

            S1: begin  // 10
                if(din) begin
                    next_state = S2;
                end
                else begin
                    next_state = IDLE;
                end
            end

            S2: begin  // 101
                if(din) begin
                    next_state = S3;
                end
                else begin
                    next_state = S1;
                end
            end

            S3: begin
                if(din) begin
                    next_state = S0;
                end
                else begin
                    next_state = S1;
                end

            end
            
            default: begin
                next_state = IDLE;
            end

        endcase
    end

    always @(*) begin
        dout = 1'b0;
        case(state)

            S3: begin
                dout = 1'b1;
            end

            default: begin
                dout = 1'b0;
            end
        endcase
    end


endmodule