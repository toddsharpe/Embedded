`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/23/2023 10:14:14 PM
// Design Name: 
// Module Name: ProgramCounter
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


module ProgramCounter import SoC::*;(
    `ifdef DEBUG
    input clk,
    `endif
    input cpu_clk,

    //Branch Calc
    input BRANCH_OP branchOp,
    input wire EQ,
    input wire LT,
    input wire LTU,

    //Pc Calc
    input PC_OP pcOp,
    input wire [31:0] pcImm,
    input wire [31:0] pcAbs,

    //Controls
    input reset,
    input latch,

    //Output
    output wire [31:0] pcPlus4,
    output wire [31:0] pcPlusImm,
    output wire [31:0] out
);

    //Program Counter
    reg [31:0] pc;

    //Branch Op
    logic takeBranch;
    always_comb
        case (branchOp)
            BRANCH_EQ: takeBranch = EQ;
            BRANCH_NE: takeBranch = !EQ;
            BRANCH_LT: takeBranch = LT;
            BRANCH_GE: takeBranch = !LT;
            BRANCH_LTU: takeBranch = LTU;
            BRANCH_GEU: takeBranch = !LTU;
            default: takeBranch = 0;
        endcase

    //Calculate next PC
    logic [31:0] pcNext;
    always_comb
        case(pcOp)
            PC_CREL: pcNext = takeBranch ? pcPlusImm : pcPlus4;
            PC_REL: pcNext = pcPlusImm;
            PC_ABS: pcNext = pcAbs;
            PC_INC: pcNext = pcPlus4;
        endcase

    //Update PC
    always_ff @(posedge cpu_clk)
        if (reset)
            pc <= 0;
        else if (latch)
            pc <= pcNext;

    //Output
    assign pcPlus4 = pc + 4;
    assign pcPlusImm = pc + pcImm;
    assign out = pc;

    //TODO(tsharpe): Needs VIO
endmodule
