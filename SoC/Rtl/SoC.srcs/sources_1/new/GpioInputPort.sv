`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/23/2023 10:07:38 PM
// Design Name: 
// Module Name: GpioInputPort
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


module GpioInputPort(
    //input clk,
    //input reset,
    output [31:0] dataOut,
    input [31:0] device
);
    assign dataOut = device;

endmodule