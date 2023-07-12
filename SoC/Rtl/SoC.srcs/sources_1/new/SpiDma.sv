`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 07/11/2023 01:04:43 PM
// Design Name: 
// Module Name: SpiDma
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


module SpiDma #(parameter ADDRESS)(
    //Memory interface
    input cpu_clk,
    input reset,
    input [31:2] address,
    input [31:0] dataIn,
    output [31:0] dataOut,
    input [3:0] write
);

    //Memory Map Interface
    //0x00: Configuration register
    //0x04: Number of elements
    //0x08: Peripheral Address
    //0x0C: Memory Address

    //8: [X, X, Switches]
    localparam DMA_CONFIG = 0;
    localparam DMA_COUNT = 1;
    localparam DMA_PERIPH = 2;
    localparam DMA_MEM = 3;
    localparam DMA_WORDS = 4;
    localparam DMA_ADDR_SIZE = $clog2(DMA_WORDS);

    reg [31:0] MEM [0:(DMA_WORDS - 1)];
    wire enabled = ((address >= ADDRESS[31:2]) && (address < (ADDRESS[31:2] + DMA_WORDS)));

    wire [DMA_ADDR_SIZE-1:0] wordAddress = address[DMA_ADDR_SIZE+1:2];
    always_ff @(posedge cpu_clk)
    begin
        if (reset)
        begin
            integer i;
            for (i = 0; i < DMA_WORDS; i = i + 1) begin
                MEM[i] <= 0;
            end
        end
        else if (enabled & write)
        begin
            if(write[0]) MEM[wordAddress][7:0] <= dataIn[7:0];
            if(write[1]) MEM[wordAddress][15:8] <= dataIn[15:8];
            if(write[2]) MEM[wordAddress][23:16] <= dataIn[23:16];
            if(write[3]) MEM[wordAddress][31:24] <= dataIn[31:24];
        end

        //Read inputs
        MEM[IO_SWITCHES][15:0] <= switchesIn;
    end

    //IO
    assign displayOut = MEM[IO_DISPLAY][15:0];
    assign ledsOut = MEM[IO_BAR][15:0];

    assign dataOut = enabled ? MEM[wordAddress] : 32'hzzzzzzzz;

endmodule
