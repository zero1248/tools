`timescale 1 ns / 1 ps

// AXIS-Stream slave interface buffer.

//      axis-stream                          algo.
//                |--------------------|
//     tvalid_up -|>                  -|> tvalid_down
//      tdata_up -|>                  -|> tdata_down
//      tlast_up -|>                  -|> tlast_down
//     tready_up <|-                  <|- tready_down
//                |--------------------|

// todo: testbench for this

module s_axis_intf_base #
    (
        // AXI4Stream sink: Data Width
        parameter integer S_AXIS_TDATA_WIDTH	= 128
    )
    (
        // Interface between AXIS-Slave and Algo. module
        input  wire tready_down,
        output reg  tvalid_down,
        output reg  tlast_down,
        output reg [S_AXIS_TDATA_WIDTH-1 : 0] tdata_down,


        // AXI Stream slave Interface
        output wire  tready_up,
        input wire  tvalid_up,
        input wire  tlast_up,
        input wire [S_AXIS_TDATA_WIDTH-1 : 0] tdata_up,
        
        input wire  S_AXIS_ACLK,
        input wire  S_AXIS_ARESETN
    );



    wire handshake;

    assign handshake = tready_up && tvalid_up;


    // up to down
    always @(posedge S_AXIS_ACLK) begin // async reset 
        if(!S_AXIS_ARESETN)
            tvalid_down <= 1'b0;
        else
            tvalid_down <= handshake ? tvalid_up : tvalid_down;
    end

    always @(posedge S_AXIS_ACLK) begin // async reset  
        if(!S_AXIS_ARESETN)
            tdata_down <= {(S_AXIS_TDATA_WIDTH){1'b0}};
        else
            tdata_down <= handshake ? tdata_up : tdata_down;
    end

    // the same with tdata_down
    always @(posedge S_AXIS_ACLK) begin // async reset
        if(!S_AXIS_ARESETN)
            tlast_down <= 1'b0;
        else
            tlast_down <= handshake ? tlast_up : tlast_down;
    end

    // down to up
    assign tready_up = tready_down;

endmodule
