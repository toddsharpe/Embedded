`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/18/2023 09:21:49 AM
// Design Name: 
// Module Name: GpioBlock
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


module GpioBlock #(parameter ADDRESS)(
    //Memory interface
    input cpu_clk,
    input reset,
    input [31:2] address,
    input [31:0] dataIn,
    output [31:0] dataOut,
    input [3:0] write,

    //IO
    inout [3:0] devices
);

    //The direction is 0 for input, 1 for output.
    localparam IO_INPUT = 0;
    localparam IO_OUTPUT = 1;
    localparam IO_DIR = 2;
    localparam IO_WORDS = 3;
    localparam IO_ADDR_SIZE = $clog2(IO_WORDS);

    reg [31:0] MEM [0:(IO_WORDS - 1)];
    wire enabled = ((address >= ADDRESS[31:2]) && (address < (ADDRESS[31:2] + IO_WORDS)));
    wire [IO_ADDR_SIZE-1:0] wordAddress = address[IO_ADDR_SIZE+1:2];

    always_ff @(posedge cpu_clk)
    begin
        if (reset)
        begin
            integer i;
            for (i = 0; i < IO_WORDS; i = i + 1) begin
                MEM[i] <= 0;
            end
        end
        else if (enabled)
        begin
            //Memory writes
            if(write[0]) MEM[wordAddress][7:0] <= dataIn[7:0];
            if(write[1]) MEM[wordAddress][15:8] <= dataIn[15:8];
            if(write[2]) MEM[wordAddress][23:16] <= dataIn[23:16];
            if(write[3]) MEM[wordAddress][31:24] <= dataIn[31:24];
        end

        //Read inputs
        MEM[IO_INPUT][0] <= !MEM[IO_DIR][0] ? devices[0] : 1'b0;
        MEM[IO_INPUT][1] <= !MEM[IO_DIR][1] ? devices[1] : 1'b0;
        MEM[IO_INPUT][2] <= !MEM[IO_DIR][2] ? devices[2] : 1'b0;
        MEM[IO_INPUT][3] <= !MEM[IO_DIR][3] ? devices[3] : 1'b0;
        MEM[IO_INPUT][31:4] <= 28'h0000000;
    end

    //Write outputs
    assign devices[0] = MEM[IO_DIR][0] ? MEM[IO_OUTPUT][0] : 1'bz;
    assign devices[1] = MEM[IO_DIR][1] ? MEM[IO_OUTPUT][1] : 1'bz;
    assign devices[2] = MEM[IO_DIR][2] ? MEM[IO_OUTPUT][2] : 1'bz;
    assign devices[3] = MEM[IO_DIR][3] ? MEM[IO_OUTPUT][3] : 1'bz;

    //Write to memory bus
    assign dataOut = enabled ? MEM[wordAddress] : 32'hzzzzzzzz;

endmodule
