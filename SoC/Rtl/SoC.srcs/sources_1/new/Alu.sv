`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/11/2023 07:23:10 AM
// Design Name: 
// Module Name: ALU
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

module ALU import SoC::*; (
    `ifdef DEBUG
    input clk,
    `endif

    input ALU_OP op,
    input wire [31:0] in1,
    input wire [31:0] in2,

    output reg [31:0] out,
    output wire EQ,
    output wire LT,
    output wire LTU
);

    always_comb
        case(op)
            ALU_ADD: out = in1 + in2;
            ALU_SUB: out = in1 - in2;
            ALU_SLL: out = in1 << in2;
            ALU_SLT: out = $signed(in1) < $signed(in2);
            ALU_SLTU: out = in1 < in2;
            ALU_XOR: out = in1 ^ in2;
            ALU_SRL: out = in1 >> in2;
            ALU_SRA: out = in1 >>> in2;
            ALU_OR: out = in1 | in2;
            ALU_AND: out = in1 & in2;
            default: out = 0;
        endcase

    //Flags
    assign EQ = in1 == in2;
    assign LT = $signed(in1) < $signed(in2);
    assign LTU = in1 < in2;

`ifdef DEBUG
    alu_vio alu_vio (
        .clk(clk),              // input wire clk
        .probe_in0(op),  // input wire [3 : 0] probe_in0
        .probe_in1(in1),  // input wire [31 : 0] probe_in1
        .probe_in2(in2),  // input wire [31 : 0] probe_in2
        .probe_in3(out),  // input wire [31 : 0] probe_in3
        .probe_in4(EQ),  // input wire [0 : 0] probe_in4
        .probe_in5(LT),  // input wire [0 : 0] probe_in5
        .probe_in6(LTU)  // input wire [0 : 0] probe_in6
    );
`endif

endmodule
