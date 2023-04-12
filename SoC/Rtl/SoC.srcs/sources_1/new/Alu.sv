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

module ALU(
    input [3:0] op,
    input [31:0] aluIn1,
    input [31:0] aluIn2,
    output reg [31:0] aluOut,
    output EQ,
    output LT,
    output LTU
);

    //SPEC: Page 130.
    //Func3
    //000: ADD/SUB,ADDI
    //001: SLL,SLLI
    //010: SLT,SLTI
    //011: SLTU,SLTIU
    //100: XOR,XORI
    //101: SRL/SRA,SRLI/SRAI
    //110: OR,ORI
    //111: AND,ANDI

    wire [32:0] aluMinus = {1'b1, ~aluIn2} + {1'b0,aluIn1} + 33'b1;
    assign LT  = (aluIn1[31] ^ aluIn2[31]) ? aluIn1[31] : aluMinus[32];
    assign LTU = aluMinus[32];
    assign EQ  = (aluMinus[31:0] == 0);

    always_comb
        case(op)
            ALU_ADD:
                aluOut = aluIn1 + aluIn2;
            ALU_SUB:
                aluOut = aluMinus;
            ALU_SLL:
                aluOut = aluIn1 << aluIn2;
            ALU_SLT:
                aluOut = {31'b0, LT};
            ALU_SLTU:
                aluOut = {31'b0, LTU};
            ALU_XOR:
                aluOut = aluIn1 ^ aluIn2;
            ALU_SRL:
                aluOut = aluIn1 >> aluIn2;
            ALU_SRA:
                aluOut = aluIn1 >>> aluIn2;
            ALU_OR:
                aluOut = aluIn1 | aluIn2;
            ALU_AND:
                aluOut = aluIn1 & aluIn2;
            default:
                aluOut = 0;
        endcase

endmodule
