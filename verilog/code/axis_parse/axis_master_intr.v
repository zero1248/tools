`timescale 1 ns / 1 ps

module axis_master_intr #(
        // AXI4Stream sink: Data Width
        parameter integer AXIS_TDATA_WIDTH	= 128
    )
    (
        // tready direct to saxis
        output reg maxis_tready_to_saxis,

        // Interface between algo and MAXIS.
        input wire maxis_tvalid,
        input wire maxis_tlast,
        input wire [AXIS_TDATA_WIDTH-1 : 0] maxis_tdata,
        

        // AXI Stream master Interface
        input wire  M_AXIS_ACLK,
        input wire  M_AXIS_ARESETN,
        
        output reg  M_AXIS_TVALID,
        output reg [AXIS_TDATA_WIDTH-1 : 0] M_AXIS_TDATA,
        // output wire [(AXIS_TDATA_WIDTH/8)-1 : 0] M_AXIS_TSTRB,
        output reg [(AXIS_TDATA_WIDTH/8)-1 : 0] M_AXIS_TKEEP,
        output reg  M_AXIS_TLAST,
        input wire  M_AXIS_TREADY
    );

    always @(posedge M_AXIS_ACLK) begin
        if(!M_AXIS_ARESETN) begin
            maxis_tready_to_saxis <= 0;
            M_AXIS_TVALID        <= 0;
            M_AXIS_TDATA         <= 0;
            M_AXIS_TKEEP         <= {(AXIS_TDATA_WIDTH/8){1'b0}};
            M_AXIS_TLAST         <= 0;
        end

        else begin
            if(M_AXIS_TREADY) begin
                maxis_tready_to_saxis <= 1;
                if(maxis_tvalid) begin
                    M_AXIS_TVALID        <= 1;
                    M_AXIS_TDATA         <= maxis_tdata;
                    M_AXIS_TKEEP         <= {(AXIS_TDATA_WIDTH/8){1'b1}};
                    if(maxis_tlast)
                        M_AXIS_TLAST     <= 1;
                    else
                        M_AXIS_TLAST     <= 0;
                end

                else begin
                    M_AXIS_TVALID        <= 0;
                    M_AXIS_TDATA         <= M_AXIS_TDATA;
                    M_AXIS_TKEEP         <= {(AXIS_TDATA_WIDTH/8){1'b0}};
                    M_AXIS_TLAST         <= 0;
                end
            end

            else begin
                maxis_tready_to_saxis <= 0;
                M_AXIS_TVALID        <= 0;
                M_AXIS_TDATA         <= M_AXIS_TDATA;
                M_AXIS_TKEEP         <= {(AXIS_TDATA_WIDTH/8){1'b0}};
                M_AXIS_TLAST         <= 0;
            end
        end
    end

endmodule
