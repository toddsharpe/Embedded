`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/24/2023 08:57:40 PM
// Design Name: 
// Module Name: RegisterMux
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


module RegisterMux import _SoC::*; (
    `ifdef DEBUG
    input clk,
    `endif

    input REG_OP regOp,
    input wire [31:0] pcPlus4,
    input wire [31:0] pcPlusImm,
    input wire [31:0] regImm,
    input wire [31:0] memData,
    input wire [31:0] aluOut,

    output reg [31:0] writeData
);

    always_comb
        case (regOp)
            REG_PC4: writeData = pcPlus4;
            REG_PCIMM: writeData = pcPlusImm;
            REG_IMM: writeData = regImm;
            REG_MEM: writeData = memData;
            REG_ALU: writeData = aluOut;
            default: writeData = 0;
        endcase

`ifdef DEBUG
    regmux_vio regmux_vio (
        .clk(clk),              // input wire clk
        .probe_in0(regOp),  // input wire [2 : 0] probe_in0
        .probe_in1(pcPlus4),  // input wire [31 : 0] probe_in1
        .probe_in2(pcPlusImm),  // input wire [31 : 0] probe_in2
        .probe_in3(regImm),  // input wire [31 : 0] probe_in3
        .probe_in4(memData),  // input wire [31 : 0] probe_in4
        .probe_in5(aluOut),  // input wire [31 : 0] probe_in5
        .probe_in6(writeData)  // input wire [31 : 0] probe_in6
    );
`endif
endmodule
