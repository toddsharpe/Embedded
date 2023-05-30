`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/08/2023 06:11:25 AM
// Design Name: 
// Module Name: Memory
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

`include "DEFINES.vinc"

module Memory #(parameter ADDRESS, parameter ADDR_WIDTH) (
    //Memory interface
    input cpu_clk,
    input reset,
    input [31:2] address,
    input [31:0] dataIn,
    output [31:0] dataOut,
    input [3:0] write
);

    localparam MAX_ADDR = 2**ADDR_WIDTH + ADDRESS;
    wire enabled = ((address >= ADDRESS[31:2]) && (address < MAX_ADDR));

    wire [31:0] bramDataOut;
    bytewrite_tdp_ram_rf #(.ADDR_WIDTH(ADDR_WIDTH)) block_ram(
        .clkA(cpu_clk),
        .reset(reset),
        .enaA(enabled),
        .weA(write),
        .addrA(address[ADDR_WIDTH+1:2]),
        .dinA(dataIn),
        .doutA(bramDataOut)
        //.clkB(),
        //.enaB(),
        //.weB(),
        //.addrB(),
        //.dinB(),
        //.doutB()
    );

    assign dataOut = enabled ? bramDataOut : 32'hzzzzzzzz;

endmodule
