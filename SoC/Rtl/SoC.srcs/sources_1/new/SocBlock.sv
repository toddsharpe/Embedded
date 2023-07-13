`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/22/2023 07:00:58 PM
// Design Name: 
// Module Name: SocBlock
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

module SocBlock #(parameter ADDRESS)(
    //Memory interface (read-only)
    input cpu_clk,
    input reset,
    input [31:2] address,
    output [31:0] dataOut
);

    //Layout
    //0: Cycles
    //4: Frequency
    localparam SOC_CYCLES = 0;
    localparam SOC_FREQ = 1;
    localparam SOC_WORDS = 2;
    localparam SOC_ADDR_SIZE = $clog2(SOC_WORDS);

    reg [31:0] MEM [0:(SOC_WORDS - 1)];
    wire enabled = ((address >= ADDRESS[31:2]) && (address < (ADDRESS[31:2] + SOC_WORDS)));
    wire [SOC_ADDR_SIZE-1:0] wordAddress = address[SOC_ADDR_SIZE+1:2];

    initial begin
        MEM[SOC_CYCLES] <= 32'h0;
        MEM[SOC_FREQ] <= CPU_FREQ;
    end

    always_ff @(posedge cpu_clk)
    begin
        if (reset)
        begin
            MEM[SOC_CYCLES] <= 32'h0;
        end
        else
        begin
            MEM[SOC_CYCLES] <= MEM[SOC_CYCLES] + 1;
        end
    end

    assign dataOut = enabled ? MEM[wordAddress] : 32'hzzzzzzzz;

endmodule
