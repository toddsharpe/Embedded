`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/09/2023 09:11:55 PM
// Design Name: 
// Module Name: Decoder
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

//SPEC: Docs\RiscV\riscv-spec-20191213.pdf
module Decoder(
    input [31:0] instr,

    //Instructions
    output isLUI,
    output isAUIPC,
    output isJAL,
    output isJALR,
    output isBranch,
    output isLoad,
    output isStore,
    output isALUimm,
    output isALUreg,
    output isSYSTEM,

    //Immediates
    output [31:0] Uimm,
    output [31:0] Iimm,
    output [31:0] Simm,
    output [31:0] Bimm,
    output [31:0] Jimm,

    //Register selects
    output [4:0] rs1Id,
    output [4:0] rs2Id,
    output [4:0] rdId,

    //Functions
    output [2:0] funct3,
    output [6:0] funct7
);

    //SPEC: P130. The 10 RISC-V instructions
    wire [6:0] opcode = instr[6:0];
    assign isLUI     =  (opcode == 7'b0110111); // rd <- Uimm
    assign isAUIPC   =  (opcode == 7'b0010111); // rd <- PC + Uimm
    assign isJAL     =  (opcode == 7'b1101111); // rd <- PC+4; PC<-PC+Jimm
    assign isJALR    =  (opcode == 7'b1100111); // rd <- PC+4; PC<-rs1+Iimm
    assign isBranch  =  (opcode == 7'b1100011); // if(rs1 OP rs2) PC<-PC+Bimm
    assign isLoad    =  (opcode == 7'b0000011); // rd <- mem[rs1+Iimm]
    assign isStore   =  (opcode == 7'b0100011); // mem[rs1+Simm] <- rs2
    assign isALUimm  =  (opcode == 7'b0010011); // rd <- rs1 OP Iimm
    assign isALUreg  =  (opcode == 7'b0110011); // rd <- rs1 OP rs2
    assign isSYSTEM  =  (opcode == 7'b1110011); // special

    // The 5 immediate formats
    assign Uimm={    instr[31],   instr[30:12], {12{1'b0}}};
    assign Iimm={{21{instr[31]}}, instr[30:20]};
    assign Simm={{21{instr[31]}}, instr[30:25],instr[11:7]};
    assign Bimm={{20{instr[31]}}, instr[7],instr[30:25],instr[11:8],1'b0};
    assign Jimm={{12{instr[31]}}, instr[19:12],instr[20],instr[30:21],1'b0};

    //SPEC: P130. Register selects
    assign rs1Id = instr[19:15];
    assign rs2Id = instr[24:20];
    assign rdId  = instr[11:7];

    //SPEC: P130. Function3/7 selects
    assign funct3 = instr[14:12];
    assign funct7 = instr[31:25];

endmodule
