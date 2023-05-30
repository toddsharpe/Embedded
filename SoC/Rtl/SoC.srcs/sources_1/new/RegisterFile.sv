`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/10/2023 07:46:45 PM
// Design Name: 
// Module Name: RegisterFile
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

module RegisterFile(
    `ifdef DEBUG
    input clk,
    `endif
    input cpu_clk,
    input reset,
    input [4:0] rs1Id,
    input [4:0] rs2Id,
    input [4:0] rdId,
    input read,
    input latch,
    input [31:0] dataIn,
    output reg [31:0] rs1,
    output reg [31:0] rs2
);
    //X0-X32. X0 is always 0
    reg [31:0] REGISTERS [0:31];
    integer i;

    //Initialize
    initial
        for (i = 0; i < 32; i = i + 1)
            REGISTERS[i] = 0;

    //Writeback
    always_ff @(posedge cpu_clk) begin
        if (reset)
            for (i = 0; i < 32; i = i + 1)
                REGISTERS[i] = 0;
        else if (read)
        begin
            rs1 <= REGISTERS[rs1Id];
            rs2 <= REGISTERS[rs2Id];
        end
        else if (latch && (rdId != 4'b0))
            REGISTERS[rdId] <= dataIn;
    end

`ifdef DEBUG
    registerfile_vio registerfile_vio (
        .clk(clk),                // input wire clk
        .probe_in0(REGISTERS[0]),    // input wire [31 : 0] probe_in0
        .probe_in1(REGISTERS[1]),    // input wire [31 : 0] probe_in1
        .probe_in2(REGISTERS[2]),    // input wire [31 : 0] probe_in2
        .probe_in3(REGISTERS[3]),    // input wire [31 : 0] probe_in3
        .probe_in4(REGISTERS[4]),    // input wire [31 : 0] probe_in4
        .probe_in5(REGISTERS[5]),    // input wire [31 : 0] probe_in5
        .probe_in6(REGISTERS[6]),    // input wire [31 : 0] probe_in6
        .probe_in7(REGISTERS[7]),    // input wire [31 : 0] probe_in7
        .probe_in8(REGISTERS[8]),    // input wire [31 : 0] probe_in8
        .probe_in9(REGISTERS[9]),    // input wire [31 : 0] probe_in9
        .probe_in10(REGISTERS[10]),  // input wire [31 : 0] probe_in10
        .probe_in11(REGISTERS[11]),  // input wire [31 : 0] probe_in11
        .probe_in12(REGISTERS[12]),  // input wire [31 : 0] probe_in12
        .probe_in13(REGISTERS[13]),  // input wire [31 : 0] probe_in13
        .probe_in14(REGISTERS[14]),  // input wire [31 : 0] probe_in14
        .probe_in15(REGISTERS[15]),  // input wire [31 : 0] probe_in15
        .probe_in16(REGISTERS[16]),  // input wire [31 : 0] probe_in16
        .probe_in17(REGISTERS[17]),  // input wire [31 : 0] probe_in17
        .probe_in18(REGISTERS[18]),  // input wire [31 : 0] probe_in18
        .probe_in19(REGISTERS[19]),  // input wire [31 : 0] probe_in19
        .probe_in20(REGISTERS[20]),  // input wire [31 : 0] probe_in20
        .probe_in21(REGISTERS[21]),  // input wire [31 : 0] probe_in21
        .probe_in22(REGISTERS[22]),  // input wire [31 : 0] probe_in22
        .probe_in23(REGISTERS[23]),  // input wire [31 : 0] probe_in23
        .probe_in24(REGISTERS[24]),  // input wire [31 : 0] probe_in24
        .probe_in25(REGISTERS[25]),  // input wire [31 : 0] probe_in25
        .probe_in26(REGISTERS[26]),  // input wire [31 : 0] probe_in26
        .probe_in27(REGISTERS[27]),  // input wire [31 : 0] probe_in27
        .probe_in28(REGISTERS[28]),  // input wire [31 : 0] probe_in28
        .probe_in29(REGISTERS[29]),  // input wire [31 : 0] probe_in29
        .probe_in30(REGISTERS[30]),  // input wire [31 : 0] probe_in30
        .probe_in31(REGISTERS[31]),  // input wire [31 : 0] probe_in31
        .probe_in32(read),  // input wire [0 : 0] probe_in32
        .probe_in33(latch)  // input wire [0 : 0] probe_in33
    );
`endif
endmodule
