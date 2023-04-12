`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/20/2023 10:55:39 PM
// Design Name: 
// Module Name: GpioOutputPort
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


module GpioOutputPort(
    input cpu_clk,
    input reset,
    input enable,
    input [31:0] dataIn,
    input [3:0] write,
    output [31:0] device
);

    reg [31:0] MEM;

    always_ff @(posedge cpu_clk)
    begin
        if (reset)
        begin
            MEM <= 32'h00000000;
        end
        else if (enable)
        begin
            if(write[0]) MEM[7:0] <= dataIn[7:0];
            if(write[1]) MEM[15:8] <= dataIn[15:8];
            if(write[2]) MEM[23:16] <= dataIn[23:16];
            if(write[3]) MEM[31:24] <= dataIn[31:24];
        end
    end

    assign device = MEM;

endmodule
