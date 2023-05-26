`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/21/2023 10:14:13 PM
// Design Name: 
// Module Name: ControlUnit
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

//Modifies decoder signals into control signals
module ControlUnit import SoC::*; (
    `ifdef DEBUG
    input clk,
    `endif

    input wire [31:0] instr,

    //ALU outputs
    output ALU_OP aluOp,
    output wire aluIn2Mux,
    output wire [31:0] aluImm,

    //Registers
    output wire [4:0] rs1Id,
    output wire [4:0] rs2Id,
    output wire [4:0] rdId,
    output REG_OP regOp,
    output wire regWrite,
    output wire [31:0] regImm,

    //Program counter
    output BRANCH_OP branchOp,
    output PC_OP pcOp,
    output wire [31:0] pcImm,

    //Memory
    output MEM_OP memOp,
    output MEM_SIZE memSize,
    output wire [31:0] memImm,
    output wire memSigned,

    //Halt
    output halt
);

    //Decoder
    wire isLUI;
    wire isAUIPC;
    wire isJAL;
    wire isJALR;
    wire isBranch;
    wire isLoad;
    wire isStore;
    wire isALUimm;
    wire isALUreg;
    wire isSYSTEM;
    wire [31:0] Uimm;
    wire [31:0] Iimm;
    wire [31:0] Simm;
    wire [31:0] Bimm;
    wire [31:0] Jimm;
    wire [2:0] funct3;
    wire [6:0] funct7;

    Decoder decoder(
        `ifdef DEBUG
        .clk(clk),
        `endif

        .instr(instr),

        //Instructions
        .isLUI(isLUI),
        .isAUIPC(isAUIPC),
        .isJAL(isJAL),
        .isJALR(isJALR),
        .isBranch(isBranch),
        .isLoad(isLoad),
        .isStore(isStore),
        .isALUimm(isALUimm),
        .isALUreg(isALUreg),
        .isSYSTEM(isSYSTEM),

        //Immediates
        .Uimm(Uimm),
        .Iimm(Iimm),
        .Simm(Simm),
        .Bimm(Bimm),
        .Jimm(Jimm),

        //Register selects
        .rs1Id(rs1Id),
        .rs2Id(rs2Id),
        .rdId(rdId),

        //Functions
        .funct3(funct3),
        .funct7(funct7)
    );

    //Alu Signals
    //isSub: funct7[5] selects add/sub, instr[5] ensures this is unsigned (vs ADDI which is signed).
    //isA: is arithmetic (for shifts)
    wire isSub = funct7[5] & instr[5] &!isJALR;
    wire isA = funct7[5];
    always_comb
        case (funct3)
            3'b000: aluOp = isSub ? ALU_SUB : ALU_ADD;
            3'b001: aluOp = ALU_SLL;
            3'b010: aluOp = ALU_SLT;
            3'b011: aluOp = ALU_SLTU;
            3'b100: aluOp = ALU_XOR;
            3'b101: aluOp = isA ? ALU_SRA : ALU_SRL;
            3'b110: aluOp = ALU_OR;
            3'b111: aluOp = ALU_AND;
        endcase
    assign aluIn2Mux = isALUreg | isBranch;
    assign aluImm = Iimm;

    //Branch OP: SPEC: Page 130.
    always_comb
        case (funct3)
            3'b000: branchOp = BRANCH_EQ;
            3'b001: branchOp = BRANCH_NE;
            3'b100: branchOp = BRANCH_LT;
            3'b101: branchOp = BRANCH_GE;
            3'b110: branchOp = BRANCH_LTU;
            3'b111: branchOp = BRANCH_GEU;
            default: branchOp = BRANCH_NONE;
        endcase

    //PC Op
    always_comb
        if (isBranch)
            pcOp = PC_CREL;
        else if (isJAL)
            pcOp = PC_REL;
        else if (isJALR)
            pcOp = PC_ABS;
        else
            pcOp = PC_INC;

    //Pc Imm
    assign pcImm = isJAL ? Jimm :
            isAUIPC ? Uimm :
            Bimm;

    //Registers
    assign regWrite = !(isBranch || isStore || isSYSTEM);
    always_comb
        if (isJAL || isJALR)
            regOp = REG_PC4;
        else if (isAUIPC)
            regOp = REG_PCIMM;
        else if (isLUI)
            regOp = REG_IMM;
        else if (isLoad)
            regOp = REG_MEM;
        else
            regOp = REG_ALU;
    assign regImm = Uimm;

    //Mem Imm
    assign memImm = (isStore ? Simm : Iimm);

    //Mem size
    always_comb
        case (funct3[1:0])
            2'b00: memSize = MEM_BYTE;
            2'b01: memSize = MEM_HALF;
            2'b10: memSize = MEM_WORD;
            default: memSize = MEM_NONE;
        endcase

    //Mem op
    always_comb
        if (isLoad)
            memOp = MEM_LOAD;
        else if (isStore)
            memOp = MEM_STORE;
        else
            memOp = MEM_IDLE;

    //Mem signed
    assign memSigned = funct3[2];

    assign halt = isSYSTEM;

endmodule
