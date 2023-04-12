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

module Processor(
    `ifdef DEBUG
    input clk,
    `endif
    input cpu_clk,
    input reset,
    output halt,
    output [31:0] memAddr,
    input [31:0] memDataR,
    output [31:0] memDataW,
    output [3:0] memWrite,
    output memRead
);

    //Registers
    reg [31:0] pc;
    reg [31:0] instr;

    //Register signals
    wire [4:0] rs1Id;
    wire [4:0] rs2Id;
    wire [4:0] rdId;
    wire regLatch;
    wire [31:0] regIn;
    wire [31:0] rs1;
    wire [31:0] rs2;

    //Register file
    RegisterFile registers(
        `ifdef DEBUG
        .clk(clk),
        `endif
        .cpu_clk(cpu_clk),
        .reset(reset),
        .rs1Id(rs1Id),
        .rs2Id(rs2Id),
        .rdId(rdId),
        .latch(regLatch),
        .dataIn(regIn),
        .rs1(rs1),
        .rs2(rs2)
    );

    //Control signals
    wire [31:0] pcIn;
    wire controlRegLatch;
    wire [31:0] loadstoreAddr;
    wire [3:0] storeMask;
    wire isLoad;

    //ControlUnit
    ControlUnit controlUnit(
        `ifdef DEBUG
        .clk(clk),
        `endif
        .instr(instr),
        .rs1(rs1),
        .rs2(rs2),
        .rs1Id(rs1Id),
        .rs2Id(rs2Id),
        .rdId(rdId),
        .regLatch(controlRegLatch),
        .regIn(regIn),
        .pc(pc),
        .pcIn(pcIn),
        .loadstoreAddr(loadstoreAddr),
        .memDataR(memDataR),
        .memDataW(memDataW),
        .storeMask(storeMask),
        .isLoad(isLoad),
        .halt(halt)
    );

    //State machine states
    enum logic [2:0] {
        FETCH,
        EXECUTE,
        RESET
    } state = RESET, next_state = RESET;

    //Next state logic
    always_comb begin
        case(state)
            RESET: begin
                next_state = FETCH;
            end
            FETCH: begin
                next_state = EXECUTE;
            end
            EXECUTE: begin
                next_state = FETCH;
            end
            default: begin
                next_state = RESET;
            end
        endcase
    end

    //Drive state machine
    always_ff @(posedge cpu_clk) begin
        if(reset) begin
            state <= RESET;
        end else begin
            state <= next_state;
        end

        //Latch state
        case(state)
            RESET: begin
                pc <= 32'h0;
                instr <= 32'h0;
            end
            FETCH: begin
                instr <= memDataR;
            end
            EXECUTE: begin
                pc <= pcIn;
                instr <= 32'h0;
            end
        endcase
    end

    //Output wires
    assign memAddr = (state == FETCH) ? pc : loadstoreAddr;
    assign memRead = (state == FETCH) ? 1'b1 :isLoad;
    assign memWrite = (state == EXECUTE) ? storeMask : 4'b0;
    assign regLatch = (state == EXECUTE) ? controlRegLatch : 1'b0;

`ifdef DEBUG
    processor_vio processor_vio (
        .clk(clk),                // input wire clk
        .probe_in0(state),    // input wire [2 : 0] probe_in0
        .probe_in1(pc),    // input wire [31 : 0] probe_in1
        .probe_in2(memAddr),    // input wire [31 : 0] probe_in2
        .probe_in3(memWrite),    // input wire [3 : 0] probe_in3
        .probe_in4(memRead),    // input wire [0 : 0] probe_in4
        .probe_in5(memDataR),    // input wire [31 : 0] probe_in5
        .probe_in6(memDataW),    // input wire [31 : 0] probe_in6
        .probe_in7(regLatch),    // input wire [0 : 0] probe_in7
        .probe_in8(regIn),    // input wire [31 : 0] probe_in8
        .probe_in9(instr),    // input wire [31 : 0] probe_in9
        .probe_in10(halt)  // input wire [0 : 0] probe_in10
    );
`endif
endmodule
