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

    wire [31:0] memAddr;
    wire [31:0] memDataIn;
    wire [31:0] memDataOut;
    wire [3:0] memWrite;

    //TODO(tsharpe): Signal isn't currently used, should it be?
    wire memRead;

    //RAM 192Kb, separated into 128k and 64k blocks

    //128k block
    Memory #(.ADDRESS(MEM_MEMORY1_START), .ADDR_WIDTH(15)) memory1(
        //Memory interface
        .cpu_clk(cpu_clk),
        .reset(reset),
        .address(memAddr[31:2]),
        .dataIn(memDataIn),
        .dataOut(memDataOut),
        .write(memWrite)
    );

    //64k block
    Memory #(.ADDRESS(MEM_MEMORY2_START), .ADDR_WIDTH(14)) memory2(
        //Memory interface
        .cpu_clk(cpu_clk),
        .reset(reset),
        .address(memAddr[31:2]),
        .dataIn(memDataIn),
        .dataOut(memDataOut),
        .write(memWrite)
    );

    SocBlock #(.ADDRESS(MEM_SOC_START)) socBlock(
        //Memory interface
        .cpu_clk(cpu_clk),
        .reset(reset),
        .address(memAddr[31:2]),
        .dataIn(memDataIn),
        .dataOut(memDataOut)
    );

    IoBlock #(.ADDRESS(MEM_IO_START)) ioBlock(
        //Memory interface
        .cpu_clk(cpu_clk),
        .reset(reset),
        .address(memAddr[31:2]),
        .dataIn(memDataIn),
        .dataOut(memDataOut),
        .write(memWrite),

        //IO
        .displayOut(displayOut),
        .ledsOut(ledsOut),
        .switchesIn(switchesIn)
    );

    //Bits [0-3]: JC Pins 7-10
    GpioBlock #(.ADDRESS(MEM_GPIO1_START)) gpio1(
        //Memory interface
        .cpu_clk(cpu_clk),
        .reset(reset),
        .address(memAddr[31:2]),
        .dataIn(memDataIn),
        .dataOut(memDataOut),
        .write(memWrite),
        
        //GPIO
        .devices(JC[7:4])
    );

    Uart #(.ADDRESS(MEM_UART_START)) uart(
        .clk(clk),

        //Memory interface
        .cpu_clk(cpu_clk),
        .reset(reset),
        .address(memAddr[31:2]),
        .dataIn(memDataIn[7:0]),
        .dataOut(memDataOut),
        .write(memWrite[0]),

        //UART
        .uartTx(uartTx)
    );

    Spi #(.ADDRESS(MEM_SPI1_START)) spi(
        .clk(clk),

        //Memory interface
        .cpu_clk(cpu_clk),
        .reset(reset),
        .address(memAddr[31:2]),
        .dataIn(memDataIn[7:0]),
        .dataOut(memDataOut),
        .write(memWrite[0]),

        //SPI
        .cs(JC[0]),
        .mosi(JC[1]),
        .miso(JC[2]),
        .sck(JC[3])
    );

    Processor processor(
        `ifdef DEBUG
        .clk(clk),
        `endif
        .cpu_clk(cpu_clk),
        .reset(reset),
        .halt(halt),
        .memAddr(memAddr),
        .memDataR(memDataOut),
        .memDataW(memDataIn),
        .memWrite(memWrite),
        .memRead(memRead)
    );

endmodule
