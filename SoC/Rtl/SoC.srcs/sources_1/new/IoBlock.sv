`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/17/2023 11:30:17 PM
// Design Name: 
// Module Name: BoardIO
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


module IoBlock #(parameter ADDRESS)(
    //Memory interface
    input cpu_clk,
    input reset,
    input [31:2] address,
    input [31:0] dataIn,
    output [31:0] dataOut,
    input [3:0] write,

    //IO
    output [15:0] displayOut,
    output [15:0] ledsOut,
    input [15:0] switchesIn
);

    //Config
    //0: [X, X, Led Display]
    //4: [X, X, Led Bar]
    //8: [X, X, Switches]
    localparam IO_DISPLAY = 0;
    localparam IO_BAR = 1;
    localparam IO_SWITCHES = 2;
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
                MEM[i] = 0;
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
