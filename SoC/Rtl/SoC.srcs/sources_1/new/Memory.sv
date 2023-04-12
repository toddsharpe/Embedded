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

module Memory #(parameter WORDS = 32)(
    input cpu_clk,
    input reset,
    input enable,
    input [31:2] address,
    input [31:0] dataIn,
    output [31:0] dataOut,
    input [3:0] write
);

    (* ram_style = "block" *)
    reg [31:0] MEM [0:(WORDS - 1)];

    initial begin
        $display("Loading RAM.");
        $readmemh("fpga.mem", MEM);
    end

    wire [29:0] wordAddress = address[31:2];

    always_ff @(posedge cpu_clk) begin
        if (reset)
        begin
            $readmemh("fpga.mem", MEM);
        end
        else if (enable)
        begin
            if(write[0]) MEM[wordAddress][7:0] <= dataIn[7:0];
            if(write[1]) MEM[wordAddress][15:8] <= dataIn[15:8];
            if(write[2]) MEM[wordAddress][23:16] <= dataIn[23:16];
            if(write[3]) MEM[wordAddress][31:24] <= dataIn[31:24];
        end
    end

    assign dataOut = MEM[wordAddress];

endmodule
