`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/20/2023 06:02:04 PM
// Design Name: 
// Module Name: ALU_test
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


`include "..\\..\\sources_1\\new\\DEFINES.vinc"

module ALU_test();

    reg [3:0] aluOp = ALU_ADD;
    reg [31:0] aluIn1;
    reg [31:0] aluIn2;
    wire [31:0] aluOut;
    wire EQ;
    wire LT;
    wire LTU;
    
    initial begin
    #10; aluOp = ALU_ADD; aluIn1 = 0; aluIn2 = 32;
    #10; aluOp = ALU_SUB; aluIn1 = 0; aluIn2 = 32;
    #10; aluOp = ALU_SLL; aluIn1 = 32; aluIn2 = 1;
    end
    
    ALU alu(
        .op(aluOp),
        .aluIn1(aluIn1),
        .aluIn2(aluIn2),
        .aluOut(aluOut),
        .EQ(EQ),
        .LT(LT),
        .LTU(LTU)
    );
    

endmodule
