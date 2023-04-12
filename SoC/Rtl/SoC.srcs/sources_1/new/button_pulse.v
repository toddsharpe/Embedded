`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/19/2023 01:01:32 PM
// Design Name: 
// Module Name: button_pulse
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


module button_pulse(
    input clk,
    input button,
    output reg pulse
    );

reg q;

always @(posedge button or posedge pulse) begin
    if (pulse) begin
        q <= 0;
    end else begin
        q <= 1;
    end
end

always @(posedge clk) begin
    pulse <= q;
end

endmodule

