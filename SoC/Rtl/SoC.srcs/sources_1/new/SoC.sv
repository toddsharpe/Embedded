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


module SoC(
    input clk,
    input cpu_clk,
    input reset,
    output halt,
    input [15:0] switchesIn,
    output [15:0] displayOut,
    output [15:0] ledsOut,
    output uartTx
);

    wire [31:0] memAddr;
    wire [31:0] memDataIn;
    wire [31:0] memDataOut;
    wire [3:0] memWrite;
    wire memRead;

    //Memory Map
    //0x0000-0x1FFF: Memory
    //0x4000 (int16): LED Display
    //0x4004 (int16): LED Bar
    //0x4008 (int16): Switches
    //0x400C (int16): <Unallocated>
    //0x4010 (int32): UART
    //-----0: UART TX

    //Memory Controller
    //TODO(tsharpe): Find a better way to do this
    wire isMemory = (memAddr < 'h10000);
    wire isLedDisplay = ((memAddr >= 'h10000) && (memAddr < 'h10004));
    wire isLedBar = ((memAddr >= 'h10004) && (memAddr < 'h10008));
    wire isSwitches = ((memAddr >= 'h10008) && (memAddr < 'h1000C));
    wire isUart = ((memAddr >= 'h10010) && (memAddr < 'h10014));

    wire [31:0] memoryOut;
    wire [31:0] switchesOut;
    wire [31:0] uartOut;

    assign memDataOut = isMemory ? memoryOut :
                        isSwitches ? switchesOut :
                        isUart ? uartOut :
                        32'hcccccccc;

    Memory #(.WORDS('h4000)) memory(
        .cpu_clk(cpu_clk),
        .reset(reset),
        .enable(isMemory),
        .address(memAddr[31:2]),
        .dataIn(memDataIn),
        .dataOut(memoryOut),
        .write(memWrite)
    );

    wire [31:0] device1024;
    GpioOutputPort ledDisplay(
        .cpu_clk(cpu_clk),
        .reset(reset),
        .enable(isLedDisplay),
        .dataIn(memDataIn),
        .write(memWrite),
        .device(device1024)
    );
    assign displayOut = device1024[15:0];

    wire [31:0] device1028;
    GpioOutputPort ledBar(
        .cpu_clk(cpu_clk),
        .reset(reset),
        .enable(isLedBar),
        .dataIn(memDataIn),
        .write(memWrite),
        .device(device1028)
    );
    assign ledsOut = device1028[15:0];

    wire [31:0] device1032 = {16'h0000, switchesIn};
    GpioInputPort switches(
        //input cpu_clk,
        //input reset,
        .dataOut(switchesOut),
        .device(device1032)
    );

    Uart uart(
        .clk(clk),
        .cpu_clk(cpu_clk),
        .reset(reset),
        .enable(isUart),
        .dataIn(memDataIn[7:0]),
        .dataOut(uartOut),
        .write(memWrite[0]),
        .uartTx(uartTx)
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
