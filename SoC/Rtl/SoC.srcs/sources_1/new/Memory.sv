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
    input cpu_clk,
    input reset,

    //PortA
    input [31:2] instrAddress,
    output [31:0] instrOut,

    //PortB
    input [31:2] dataAddress,
    input [31:0] dataIn,
    input [3:0] dataWrite,
    output [31:0] dataOut
);

    localparam MAX_ADDR = 2**ADDR_WIDTH + ADDRESS;
    wire enaA = ((instrAddress >= ADDRESS[31:2]) && (instrAddress < MAX_ADDR));
    wire enaB = ((dataAddress >= ADDRESS[31:2]) && (dataAddress < MAX_ADDR));

    //PortA: Instruction port
    //PortB: Data port
    wire [31:0] doutA;
    wire [31:0] doutB;
    bytewrite_tdp_ram_rf #(.ADDR_WIDTH(ADDR_WIDTH)) block_ram(
        .clkA(cpu_clk),
        .reset(reset),
        .enaA(enaA),
        .weA(4'b0),
        .addrA(instrAddress[ADDR_WIDTH+1:2]),
        .dinA(32'b0),
        .doutA(doutA),
        .clkB(cpu_clk),
        .enaB(enaB),
        .weB(dataWrite),
        .addrB(dataAddress[ADDR_WIDTH+1:2]),
        .dinB(dataIn),
        .doutB(doutB)
    );

    assign instrOut = enaA ? doutA : 32'hzzzzzzzz;
    assign dataOut = enaB ? doutB : 32'hzzzzzzzz;

endmodule
