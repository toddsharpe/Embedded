`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/10/2023 10:26:41 AM
// Design Name: 
// Module Name: Processor
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

module Processor import SoC::*; (
    `ifdef DEBUG
    input clk,
    `endif
    input cpu_clk,
    input reset,
    output halt,

    //Memory
    output [31:0] memAddr,
    input [31:0] memDataR,
    output [31:0] memDataW,
    output [3:0] memWrite,
    output memRead
);
    //State
    reg [31:0] instr;

    //Alu controls
    ALU_OP aluOp;
    wire aluIn2Mux;
    wire [31:0] aluImm;

    //Register controls
    wire [4:0] rs1Id;
    wire [4:0] rs2Id;
    wire [4:0] rdId;
    REG_OP regOp;
    wire regWrite;
    wire [31:0] regImm;

    //Program counter
    BRANCH_OP branchOp;
    PC_OP pcOp;
    wire [31:0] pcImm;

    //Memory access
    MEM_OP memOp;
    MEM_SIZE memSize;
    wire [31:0] memImm;
    wire memSigned;

    ControlUnit controlUnit(
        `ifdef DEBUG
        .clk(clk),
        `endif

        .instr(instr),

        .aluOp(aluOp),
        .aluIn2Mux(aluIn2Mux),
        .aluImm(aluImm),

        .rs1Id(rs1Id),
        .rs2Id(rs2Id),
        .rdId(rdId),
        .regOp(regOp),
        .regWrite(regWrite),
        .regImm(regImm),

        .branchOp(branchOp),
        .pcOp(pcOp),
        .pcImm(pcImm),

        .memOp(memOp),
        .memSize(memSize),
        .memImm(memImm),
        .memSigned(memSigned),

        .halt(halt)
    );

    //Register file
    wire regRead;
    wire regLatch;
    wire [31:0] regData;
    wire [31:0] rs1;
    wire [31:0] rs2;
    RegisterFile registers(
        `ifdef DEBUG
        .clk(clk),
        `endif
        .cpu_clk(cpu_clk),
        .reset(reset),
        .rs1Id(rs1Id),
        .rs2Id(rs2Id),
        .rdId(rdId),
        .read(regRead),
        .latch(regLatch),
        .dataIn(regData),
        .rs1(rs1),
        .rs2(rs2)
    );

    //ALU
    wire [31:0] aluIn1 = rs1;
    wire [31:0] aluIn2 = (aluIn2Mux) ? rs2 : aluImm;
    wire [31:0] aluOut;
    wire EQ;
    wire LT;
    wire LTU;
    ALU alu(
        `ifdef DEBUG
        .clk(clk),
        `endif
        .op(aluOp),
        .in1(aluIn1),
        .in2(aluIn2),
        .out(aluOut),
        .EQ(EQ),
        .LT(LT),
        .LTU(LTU)
    );

    //Program Counter
    wire pcLatch;
    wire [31:0] pcPlus4;
    wire [31:0] pcPlusImm;
    wire [31:0] pcOut;
    ProgramCounter programCounter(
        `ifdef DEBUG
        .clk(clk),
        `endif
        .cpu_clk(cpu_clk),

        //Branch Calc
        .branchOp(branchOp),
        .EQ(EQ),
        .LT(LT),
        .LTU(LTU),

        //Pc Calc
        .pcOp(pcOp),
        .pcImm(pcImm),
        .pcAbs(aluOut),

        //Controls
        .reset(reset),
        .latch(pcLatch),

        //Output
        .pcPlus4(pcPlus4),
        .pcPlusImm(pcPlusImm),
        .out(pcOut)
    );

    //Register mux
    wire [31:0] memData;
    RegisterMux regMux(
        `ifdef DEBUG
        .clk(clk),
        `endif

        .regOp(regOp),
        .pcPlus4(pcPlus4),
        .pcPlusImm(pcPlusImm),
        .regImm(regImm),
        .memData(memData),
        .aluOut(aluOut),

        .writeData(regData)
    );

    //Memory access
    wire [31:0] loadStoreAddr;
    wire [3:0] writeMask;
    MemoryAccess memoryAccess(
        `ifdef DEBUG
        .clk(clk),
        `endif

        .rs1(rs1),
        .memImm(memImm),
        .memSize(memSize),
        .rs2(rs2),
        .memSigned(memSigned),
        .memDataR(memDataR),
        .loadStoreAddr(loadStoreAddr),
        .memDataW(memDataW),
        .loadData(memData),
        .writeMask(writeMask)
    );

    //State machine states
    enum logic [3:0]
    {
        FETCH,
        FETCH_WAIT,
        LOAD_REGS,
        EXECUTE,
        LOAD,
        LOAD_WAIT,
        STORE,
        RESET
    } state = RESET, next_state = RESET;

    //Next state logic
    always_comb begin
        unique case(state)
            RESET: next_state = FETCH;
            FETCH: next_state = FETCH_WAIT;
            FETCH_WAIT: next_state = LOAD_REGS;
            LOAD_REGS: next_state = EXECUTE;
            EXECUTE: next_state = memOp == MEM_LOAD ? LOAD : 
                                  memOp == MEM_STORE ? STORE :
                                    FETCH;
            LOAD: next_state = LOAD_WAIT;
            LOAD_WAIT: next_state = FETCH;
            STORE: next_state = FETCH;
        endcase
    end

    //Drive state machine
    always_ff @(posedge cpu_clk) begin
        if(reset) begin
            state <= RESET;
        end else begin
            state <= next_state;
        end

        //State outputs
        case(state)
            RESET: begin
                instr <= 32'h0;
            end
            FETCH_WAIT: begin
                instr <= memDataR;
            end
        endcase
    end

    //Output wires
    assign regRead = (state == LOAD_REGS);
    assign memAddr = (state == FETCH || state == FETCH_WAIT) ? pcOut : loadStoreAddr;
    assign memRead = (state == FETCH || state == LOAD);
    assign memWrite = (state == STORE) ? writeMask : 4'b0;
    assign regLatch = (state == EXECUTE || state == LOAD_WAIT) ? regWrite : 1'b0;
    assign pcLatch = (state == EXECUTE);

`ifdef DEBUG
    processor_vio processor_vio (
        .clk(clk),                // input wire clk
        .probe_in0(state),    // input wire [3 : 0] probe_in0
        .probe_in1(pcOut),    // input wire [31 : 0] probe_in1
        .probe_in2(memAddr),    // input wire [31 : 0] probe_in2
        .probe_in3(memWrite),    // input wire [3 : 0] probe_in3
        .probe_in4(memRead),    // input wire [0 : 0] probe_in4
        .probe_in5(memDataR),    // input wire [31 : 0] probe_in5
        .probe_in6(memDataW),    // input wire [31 : 0] probe_in6
        .probe_in7(regLatch),    // input wire [0 : 0] probe_in7
        .probe_in8(regData),    // input wire [31 : 0] probe_in8
        .probe_in9(instr),    // input wire [31 : 0] probe_in9
        .probe_in10(halt),  // input wire [0 : 0] probe_in10
        .probe_in11(memOp)  // input wire [1 : 0] probe_in11
    );
`endif
endmodule
