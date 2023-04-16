`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/29/2023 06:47:57 PM
// Design Name: 
// Module Name: Uart
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


//Defines a UART module
//0: TX Data [1:full|23:reserved|8:data]

module Uart #(parameter ADDRESS, parameter WORDS = 1)(
    input clk,

    //Memory interface
    input cpu_clk,
    input reset,
    input [31:2] address,
    input [31:0] dataIn,
    output [31:0] dataOut,
    input [3:0] write,

    //UART
    output uartTx
);

    reg [7:0] txdata;
    wire enabled = ((address >= ADDRESS[31:2]) && (address < (ADDRESS[31:2] + WORDS)));

    always_ff @(posedge cpu_clk)
    begin
        if (reset)
        begin
            txdata <= 32'h00000000;
        end
        else if (enabled & write) begin
            txdata[7:0] <= dataIn[7:0];
        end
    end

    // Edge detector for transmit
    reg tx_cur;
    reg tx_prev;
    reg tx_transmit;
    always_ff @(posedge clk)
    begin
        if (enabled & write)
            tx_cur <= 1;
        else
            tx_cur <= 0;
        tx_transmit <= tx_cur & ~tx_prev;
        tx_prev <= tx_cur;
    end

    //CLOCK_DIVIDE = Frequency(clk) / (4 * Baud)
    wire tx_idle;
    uart_core #(.CLOCK_DIVIDE(217)) uart(
        .clk(clk), // The master clock for this module
        .rst(reset), // Synchronous reset.
        .rx(), // Incoming serial line
        .tx(uartTx), // Outgoing serial line
        .transmit(tx_transmit), // Signal to transmit
        .tx_byte(txdata), // Byte to transmit
        .received(), // Indicated that a byte has been received.
        .rx_byte(), // Byte received
        .is_receiving(), // Low when receive line is idle.
        .is_transmitting(tx_idle), // Low when transmit line is idle.
        .recv_error() // Indicates error in receiving packet.
    );

    //NOTE(tsharpe): tx_idle is active low, therefore a high tx_idle means uart is full.
    assign dataOut = enabled ? {tx_idle, 31'h0} : 32'hzzzzzzzz;

endmodule
