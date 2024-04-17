`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/25/2023 01:37:34 PM
// Design Name: 
// Module Name: MemoryAccess
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

import _SoC::*;

//Store mask
//1111 - Word
//0011,1100 - Halfword (depending on address[1])
//0001,0010,0100,1000 - Byte (depending on address[1:0])
function [3:0] StoreMask(input [31:0] address, MEM_SIZE size);
    begin
        case (size)
            MEM_BYTE:
            return address[1] ? (address[0] ? 4'b1000 : 4'b0100) :
                                (address[0] ? 4'b0010 : 4'b0001);
            MEM_HALF:
                return address[1] ? 4'b1100 : 4'b0011;
            MEM_WORD:
                return 4'b1111;
            default:
                return 0;
        endcase
    end
endfunction : StoreMask

function [31:0] StoreData(input [31:0] rs2, input [31:0] address);
    begin
        return {
                address[0] ? rs2[7:0]  : address[1] ? rs2[15:8] : rs2[31:24],
                address[1] ? rs2[7:0]  : rs2[23:16],
                address[0] ? rs2[7:0]  : rs2[15: 8],
                rs2[7:0]
            };
    end
endfunction : StoreData

module MemoryAccess import _SoC::*; (
    `ifdef DEBUG
    input clk,
    `endif

    //Address
    input wire [31:0] rs1,
    input wire [31:0] memImm,

    input MEM_SIZE memSize,

    //Store
    input wire [31:0] rs2,

    //Load
    input wire memSigned,
    input wire [31:0] memDataR,

    output wire [31:0] loadStoreAddr,
    output wire [31:0] memDataW,
    output logic [31:0] loadData,
    output wire [3:0] writeMask
);

    //Load/Store address
    wire [31:0] addr = rs1 + memImm;

    //Store calc
    assign memDataW = StoreData(rs2, addr);
    assign writeMask = StoreMask(addr, memSize);
    assign loadStoreAddr = addr;

    //Load calc
    wire [15:0] loadHalf = loadStoreAddr[1] ? memDataR[31:16] : memDataR[15:0];
    wire [7:0] loadByte = loadStoreAddr[0] ? loadHalf[15:8] : loadHalf[7:0];
    always_comb
        case (memSize)
            MEM_BYTE:
                loadData = {{24{memSigned & loadByte[7]}}, loadByte};
            MEM_HALF:
                loadData = {{16{memSigned & loadHalf[15]}}, loadHalf};
            default:
                loadData = memDataR;
        endcase

endmodule
