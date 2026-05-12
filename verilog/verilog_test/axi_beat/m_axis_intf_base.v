`timescale 1 ns / 1 ps

// AXIS-Stream master interface buffer.

//       algo.                            axis-strem                          
//                |--------------------|
//     tvalid_up -|>                  -|> tvalid_down
//      tdata_up -|>                  -|> tdata_down
//      tlast_up -|>                  -|> tlast_down
//     tready_up <|-                  <|- tready_down
//                |--------------------|


module m_axis_intf_base #(
        // AXI4Stream sink: Data Width
        parameter integer C_M_AXIS_TDATA_WIDTH	= 32
    )
    (
        // Interface between algo and MAXIS.
        input wire [C_M_AXIS_TDATA_WIDTH-1 : 0] data_algo_to_maxis,
        input wire tvalid_algo_to_maxis,
        input wire tlast_algo_to_maxis,
        output reg tready_maxis_to_algo,

        // AXI Stream master Interface
        input wire  M_AXIS_ACLK,
        input wire  M_AXIS_ARESETN,
        output reg  M_AXIS_TVALID,
        output reg [C_M_AXIS_TDATA_WIDTH-1 : 0] M_AXIS_TDATA,
        // output wire [(C_M_AXIS_TDATA_WIDTH/8)-1 : 0] M_AXIS_TSTRB,
        output reg [(C_M_AXIS_TDATA_WIDTH/8)-1 : 0] M_AXIS_TKEEP,
        output reg  M_AXIS_TLAST,
        input wire  M_AXIS_TREADY
    );

    always @(posedge M_AXIS_ACLK or negedge M_AXIS_ARESETN) begin
        if(!M_AXIS_ARESETN) begin
            tready_maxis_to_algo <= 0;
            M_AXIS_TVALID        <= 0;
            M_AXIS_TDATA         <= 0;
            M_AXIS_TKEEP         <= 4'b0000;
            M_AXIS_TLAST         <= 0;
        end

        else begin
            if(M_AXIS_TREADY) begin
                tready_maxis_to_algo <= 1;
                if(tvalid_algo_to_maxis) begin
                    M_AXIS_TVALID        <= 1;
                    M_AXIS_TDATA         <= data_algo_to_maxis;
                    M_AXIS_TKEEP         <= 4'b1111;
                    if(tlast_algo_to_maxis)
                        M_AXIS_TLAST     <= 1;
                    else
                        M_AXIS_TLAST     <= 0;
                end

                else begin
                    M_AXIS_TVALID        <= 0;
                    M_AXIS_TDATA         <= M_AXIS_TDATA;
                    M_AXIS_TKEEP         <= 4'b0000;
                    M_AXIS_TLAST         <= 0;
                end
            end

            else begin
                tready_maxis_to_algo <= 0;
                M_AXIS_TVALID        <= 0;
                M_AXIS_TDATA         <= M_AXIS_TDATA;
                M_AXIS_TKEEP         <= 4'b0000;
                M_AXIS_TLAST         <= 0;
            end
        end
    end

endmodule
