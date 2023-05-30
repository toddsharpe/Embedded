`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/23/2023 08:31:08 PM
// Design Name: 
// Module Name: Package
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


package SoC;
    typedef enum logic [3:0]
    {
        ALU_ADD,
        ALU_SUB,
        ALU_SLL,
        ALU_SLT,
        ALU_SLTU,
        ALU_XOR,
        ALU_SRL,
        ALU_SRA,
        ALU_OR,
        ALU_AND
    } ALU_OP;

    typedef enum logic [2:0]
    {
        BRANCH_NONE,
        BRANCH_EQ,
        BRANCH_NE,
        BRANCH_LT,
        BRANCH_GE,
        BRANCH_LTU,
        BRANCH_GEU
    } BRANCH_OP;

    typedef enum logic [1:0]
    {
        PC_CREL, //Conditional (branch)
        PC_REL,
        PC_ABS,
        PC_INC
    } PC_OP;

    typedef enum logic [1:0]
    {
        MEM_NONE,
        MEM_BYTE,
        MEM_HALF,
        MEM_WORD
    } MEM_SIZE;

    typedef enum logic [1:0]
    {
        MEM_IDLE,
        MEM_LOAD,
        MEM_STORE
    } MEM_OP;

    typedef enum logic [2:0]
    {
        REG_PC4,
        REG_PCIMM,
        REG_IMM,
        REG_MEM,
        REG_ALU
    } REG_OP;
endpackage
