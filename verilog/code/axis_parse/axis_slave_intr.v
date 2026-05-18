`timescale 1 ns / 1 ps

module axis_slave_intr #
    (
        // AXI4Stream sink: Data Width
        parameter integer AXIS_TDATA_WIDTH	= 128
    )
    (
        // tready from axis_master_intf
        // input  wire saxis_tready,
        input  wire saxis_tready_from_maxis,

        // Interface between SAXIS and Algo.
        output reg saxis_tvalid,
        output reg saxis_tlast,
        output reg [AXIS_TDATA_WIDTH-1 : 0] saxis_tdata,


        // AXI Stream slave Interface
        input wire  S_AXIS_ACLK,
        input wire  S_AXIS_ARESETN,
        output reg  S_AXIS_TREADY,
        input wire [AXIS_TDATA_WIDTH-1 : 0] S_AXIS_TDATA,
        // input wire [(AXIS_TDATA_WIDTH/8)-1 : 0] S_AXIS_TSTRB,
        input wire [(AXIS_TDATA_WIDTH/8)-1 : 0] S_AXIS_TKEEP,
        input wire  S_AXIS_TLAST,
        input wire  S_AXIS_TVALID
    );



    always @(posedge S_AXIS_ACLK) begin
        if(!S_AXIS_ARESETN) begin
            S_AXIS_TREADY  <= 0;
            saxis_tvalid   <= 0;
            saxis_tdata    <= 0;
            saxis_tlast    <= 0;
        end
        else begin
            if(saxis_tready_from_maxis) begin // READY 拉高的情况下才判断 VALID
                S_AXIS_TREADY <= 1;
                if(S_AXIS_TVALID) begin
                    if (S_AXIS_TKEEP == {(AXIS_TDATA_WIDTH/8){1'b0}}) begin
                        saxis_tvalid  <= 0;
                        saxis_tdata   <= saxis_tdata;
                        saxis_tlast   <= 0;
                    end
                    else begin
                        saxis_tvalid  <= 1;
                        saxis_tdata   <= S_AXIS_TDATA;
                        if(S_AXIS_TLAST)
                            saxis_tlast <= 1;
                        else
                            saxis_tlast <= 0;
                    end
                end
                else begin
                    saxis_tvalid <= 0;
                    saxis_tdata   <= saxis_tdata;
                    saxis_tlast  <= 0;
                end
            end
            else begin
                S_AXIS_TREADY        <= 0;
                saxis_tvalid <= 0;
                saxis_tdata   <= saxis_tdata;
                saxis_tlast  <= 0;
            end
        end
    end

endmodule

