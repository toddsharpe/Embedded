`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/17/2023 11:12:33 PM
// Design Name: 
// Module Name: Spi
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


module Spi #(parameter ADDRESS, parameter WORDS = 1)(
    input clk,

    //Memory interface
    input cpu_clk,
    input reset,
    input [31:2] address,
    input [31:0] dataIn,
    output [31:0] dataOut,
    input [3:0] write,

    //SPI
    output cs,
    output mosi,
    input miso,
    output sck
);

    reg [7:0] txdata;
    wire enabled = ((address >= ADDRESS[31:2]) && (address < (ADDRESS[31:2] + WORDS)));

    // Edge detector for transmit
    reg tx_cur;
    reg tx_prev;
    reg tx_transmit;
    always_ff @(posedge cpu_clk)
    begin
        if (reset)
        begin
            txdata <= 32'h00000000;
        end
        else if (enabled & write) begin
            tx_cur <= 1;
            txdata[7:0] <= dataIn[7:0];
        end
        else
            tx_cur <= 0;
        tx_transmit <= tx_cur & ~tx_prev;
        tx_prev <= tx_cur;
    end

    //Spi core
    wire tx_idle;
    wire rx_available;
    wire [7:0] rx_data;

    spi_core #(.SPI_MODE(3), .CLKS_PER_HALF_BIT(8)) spi_core(
        .i_Rst_L(!reset),
        .i_Clk(clk),
        .i_TX_Byte(txdata),
        .i_TX_DV(tx_transmit),
        .o_TX_Ready(tx_idle),
        .o_RX_DV(rx_available),
        .o_RX_Byte(rx_data),
        .o_SPI_Clk(sck),
        .i_SPI_MISO(miso),
        .o_SPI_MOSI(mosi)
    );

    assign dataOut = enabled ? {!tx_idle, 31'h0} : 32'hzzzzzzzz;

`ifdef DEBUG
    spi_vio spi_vio (
        .clk(clk),              // input wire clk
        .probe_in0(enabled),  // input wire [0 : 0] probe_in0
        .probe_in1(tx_transmit),  // input wire [0 : 0] probe_in1
        .probe_in2(txdata),  // input wire [7 : 0] probe_in2
        .probe_in3(tx_idle)  // input wire [0 : 0] probe_in3
    );
`endif

endmodule
