`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/25/2023 01:37:34 PM
// Design Name: 
// Module Name: MemoryAccess
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

module MemoryAccess
(
    input [31:0] memData,
    input [1:0] address,
    input [1:0] size,
    input signExtend,
    output [31:0] loadData
);

    //Memory access
    wire [15:0] loadHalf = address[1] ? memData[31:16] : memData[15:0];
    wire [7:0] loadByte = address[0] ? loadHalf[15:8] : loadHalf[7:0];

    assign loadData = (size == LS_BYTE) ? {{24{signExtend & loadByte[7]}}, loadByte} :
                    (size == LS_HALF) ? {{16{signExtend & loadHalf[15]}}, loadHalf} : memData;
endmodule
