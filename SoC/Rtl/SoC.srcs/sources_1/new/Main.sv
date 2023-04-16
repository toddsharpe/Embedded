`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/10/2023 10:48:41 AM
// Design Name: 
// Module Name: Main
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


module Main(
    input clk,
    input btnC,
    input [15:0] sw,
    output [3:0] an,
    output [6:0] seg,
    output [15:0] led,
    output RsTx
);

    //SOC IO
    wire halt;

    //Peripherals
    wire [15:0] displayOut;

    //CPU Clock
    wire manual_clk;
    wire cpu_clk;
    /*
    cpu_clk_wiz cpu_clk_wiz(
        // Clock out ports
        .clk_out1_ce(~halt),  // input clk_out1_ce
        .clk_out1(cpu_clk),     // output clk_out1
        // Clock in ports
        .clk_in1(clk)      // input clk_in1
    );
    */
    clock_divider #(.FREQ(1024)) clk_1024(
        .clk(clk),
        .reset(),
        .clk_div(cpu_clk)
    );

    button_pressed btnC_pressed(
        .clk(clk),
        .button(btnC),
        .pressed(manual_clk)
    );
    wire soc_clk = (sw[15] ? manual_clk : cpu_clk);

    //SoC
    SoC soc(
        .clk(clk),
        .cpu_clk(soc_clk),
        .reset(1'b0),
        .halt(halt),
        .switchesIn({1'b0, sw[14:0]}),
        .displayOut(displayOut),
        .ledsOut(led),
        .uartTx(RsTx)
    );

    //LED Peripheral
    LedSegmentsController segDisplay(.clk(clk), .value(displayOut), .an(an), .seg(seg));
endmodule
