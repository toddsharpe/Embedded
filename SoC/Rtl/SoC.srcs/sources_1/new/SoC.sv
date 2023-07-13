`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/10/2023 05:32:30 PM
// Design Name: 
// Module Name: SoC
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

localparam MEM_MEMORY1_START = 'h0;
localparam MEM_MEMORY2_START = 'h20000;
localparam DEVICE_START = 'h100000;
localparam MEM_SOC_START = DEVICE_START;
localparam MEM_IO_START = DEVICE_START  + 'h100;
localparam MEM_GPIO1_START = DEVICE_START + 'h200;
localparam MEM_UART_START = DEVICE_START  + 'h300;
localparam MEM_SPI1_START = DEVICE_START + 'h400;

module SoC(
    input clk,
    input cpu_clk,
    input reset,
    output halt,
    input [15:0] switchesIn,
    output [15:0] displayOut,
    output [15:0] ledsOut,
    inout [7:0] JC,
    output uartTx
);

    //Instruction memory port
    wire [31:0] imemAddr;
    wire [31:0] imemDataOut;

    //Data memory port
    wire [31:0] dmemAddr;
    wire [31:0] dmemDataIn;
    wire [3:0] dmemWrite;
    wire [31:0] dmemDataOut;

    //TODO(tsharpe): Signal isn't currently used, should it be?
    wire dataRead;

    Processor processor(
        `ifdef DEBUG
        .clk(clk),
        `endif

        .cpu_clk(cpu_clk),
        .reset(reset),
        .halt(halt),

        //Instruction memory port
        .instrAddress(imemAddr),
        .instrOut(imemDataOut),

        //Data memory port
        .dataAddress(dmemAddr),
        .dataIn(dmemDataIn),
        .dataRead(dataRead),
        .dataWrite(dmemWrite),
        .dataOut(dmemDataOut)
    );

    //RAM 192Kb, separated into 128k and 64k blocks
    //128k block
    Memory #(.ADDRESS(MEM_MEMORY1_START), .ADDR_WIDTH(15)) memory1(
        .cpu_clk(cpu_clk),
        .reset(reset),

        //Instruction
        .instrAddress(imemAddr[31:2]),
        .instrOut(imemDataOut),

        //Data
        .dataAddress(dmemAddr[31:2]),
        .dataIn(dmemDataIn),
        .dataWrite(dmemWrite),
        .dataOut(dmemDataOut)
    );

    //64k block
    Memory #(.ADDRESS(MEM_MEMORY2_START), .ADDR_WIDTH(14)) memory2(
        .cpu_clk(cpu_clk),
        .reset(reset),

        //Instruction
        .instrAddress(imemAddr[31:2]),
        .instrOut(imemDataOut),

        //Data
        .dataAddress(dmemAddr[31:2]),
        .dataIn(dmemDataIn),
        .dataWrite(dmemWrite),
        .dataOut(dmemDataOut)
    );

    SocBlock #(.ADDRESS(MEM_SOC_START)) socBlock(
        .cpu_clk(cpu_clk),
        .reset(reset),

        //Data interface
        .address(dmemAddr[31:2]),
        .dataOut(dmemDataOut)
    );

    IoBlock #(.ADDRESS(MEM_IO_START)) ioBlock(
        .cpu_clk(cpu_clk),
        .reset(reset),

        //Data interface
        .address(dmemAddr[31:2]),
        .dataIn(dmemDataIn),
        .write(dmemWrite),
        .dataOut(dmemDataOut),

        //IO
        .displayOut(displayOut),
        .ledsOut(ledsOut),
        .switchesIn(switchesIn)
    );

    //Bits [0-3]: JC Pins 7-10
    GpioBlock #(.ADDRESS(MEM_GPIO1_START)) gpio1(
        .cpu_clk(cpu_clk),
        .reset(reset),

        //Data interface
        .address(dmemAddr[31:2]),
        .dataIn(dmemDataIn),
        .write(dmemWrite),
        .dataOut(dmemDataOut),
        
        //GPIO
        .devices(JC[7:4])
    );

    Uart #(.ADDRESS(MEM_UART_START)) uart(
        .clk(clk),

        .cpu_clk(cpu_clk),
        .reset(reset),

        //Data interface
        .address(dmemAddr[31:2]),
        .dataIn(dmemDataIn[7:0]),
        .write(dmemWrite[0]),
        .dataOut(dmemDataOut),

        //UART
        .uartTx(uartTx)
    );

    Spi #(.ADDRESS(MEM_SPI1_START)) spi(
        .clk(clk),

        .cpu_clk(cpu_clk),
        .reset(reset),

        //Data interface
        .address(dmemAddr[31:2]),
        .dataIn(dmemDataIn[7:0]),
        .write(dmemWrite[0]),
        .dataOut(dmemDataOut),

        //SPI
        .cs(JC[0]),
        .mosi(JC[1]),
        .miso(JC[2]),
        .sck(JC[3])
    );

endmodule
