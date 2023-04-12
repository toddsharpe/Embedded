`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/21/2023 10:14:13 PM
// Design Name: 
// Module Name: ControlUnit
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

function [3:0] AluOpSelect(input [2:0] func, input isSub, input isA);
    begin
        case (func)
        3'b000: return isSub ? ALU_SUB : ALU_ADD;
        3'b001: return ALU_SLL;
        3'b010: return ALU_SLT;
        3'b011: return ALU_SLTU;
        3'b100: return ALU_XOR;
        3'b101: return isA ? ALU_SRA : ALU_SRL;
        3'b110: return ALU_OR;
        3'b111: return ALU_AND;
        endcase
    end
endfunction : AluOpSelect

function [0:0] BranchCalc(input [2:0] branchOp, input EQ, input LT, input LTU);
    begin
        case(branchOp)
            B_EQ: return EQ;
            B_NE: return !EQ;
            B_LT: return LT;
            B_GE: return !LT;
            B_LTU: return LTU;
            B_GEU: return !LTU;
            default: return 1'b0;
        endcase
    end
endfunction : BranchCalc

function [31:0] PcNextCalc(input [2:0] pcOp, input [31:0] pcPlus4, input [31:0] pcPlusImm, input [31:0] pcAbs);
    begin
        case (pcOp)
            PC_NEXT: return pcPlus4;
            PC_REL: return pcPlusImm;
            PC_ABS: return pcAbs;
            default: return pcPlus4;
        endcase
    end
endfunction : PcNextCalc

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

//Store mask
//1111 - Word
//0011,1100 - Halfword (depending on address[1])
//0001,0010,0100,1000 - Byte (depending on address[1:0])
function [3:0] StoreMask(input [31:0] address, input [1:0] size);
    begin
        case (size)
            LS_BYTE:
            return address[1] ? (address[0] ? 4'b1000 : 4'b0100) :
                                (address[0] ? 4'b0010 : 4'b0001);
            LS_HALF:
                return address[1] ? 4'b1100 : 4'b0011;
            LS_WORD:
                return 4'b1111;
            default:
                return 4'b1111;
        endcase
    end
endfunction : StoreMask

module ControlUnit(
    `ifdef DEBUG
    input clk,
    `endif
    input [31:0] instr,
    input [31:0] rs1,
    input [31:0] rs2,
    output [4:0] rs1Id,
    output [4:0] rs2Id,
    output [4:0] rdId,
    output regLatch,
    output [31:0] regIn,
    input [31:0] pc,
    output [31:0] pcIn,
    output [31:0] loadstoreAddr,
    input [31:0] memDataR,
    output [31:0] memDataW,
    output [3:0] storeMask,
    output isLoad,
    output halt
);

    //Instructions
    wire isLUI;
    wire isAUIPC;
    wire isJAL;
    wire isJALR;
    wire isBranch;
    //wire isLoad;
    wire isStore;
    wire isALUimm;
    wire isALUreg;
    wire isSYSTEM;

    //Immediates
    wire [31:0] Uimm;
    wire [31:0] Iimm;
    wire [31:0] Simm;
    wire [31:0] Bimm;
    wire [31:0] Jimm;

    //Functions
    wire [2:0] funct3;
    wire [6:0] funct7;

    //Decoder
    Decoder decoder(
        .instr(instr),

        .isLUI(isLUI),
        .isAUIPC(isAUIPC),
        .isJAL(isJAL),
        .isJALR(isJALR),
        .isBranch(isBranch),
        .isLoad(isLoad),
        .isStore(isStore),
        .isALUimm(isALUimm),
        .isALUreg(isALUreg),
        .isSYSTEM(isSYSTEM),

        .Uimm(Uimm),
        .Iimm(Iimm),
        .Simm(Simm),
        .Bimm(Bimm),
        .Jimm(Jimm),

        .rs1Id(rs1Id),
        .rs2Id(rs2Id),
        .rdId(rdId),

        .funct3(funct3),
        .funct7(funct7)
    );

`ifdef DEBUG
    decoder_vio decoder_vio (
        .clk(clk),              // input wire clk
        .probe_in0(instr),  // input wire [31 : 0] probe_in0
        .probe_in1(rs1Id),  // input wire [4 : 0] probe_in1
        .probe_in2(rs2Id),  // input wire [4 : 0] probe_in2
        .probe_in3(rdId),  // input wire [4 : 0] probe_in3
        .probe_in4(funct3),  // input wire [2 : 0] probe_in4
        .probe_in5(funct7)  // input wire [6 : 0] probe_in5
    );
`endif

    //ALU Control
    //isSub: funct7[5] selects add/sub, instr[5] ensures this is unsigned (vs ADDI which is signed).
    //isA: is arithmetic (for shifts)
    wire isSub = funct7[5] & instr[5] &!isJALR;
    wire isA = funct7[5];
    wire [3:0] aluOp = AluOpSelect(funct3, isSub, isA);

    //ALU
    wire [31:0] aluIn1 = rs1;
    wire [31:0] aluIn2 = (isALUreg | isBranch) ? rs2 : Iimm;
    wire [31:0] aluOut;
    wire EQ;
    wire LT;
    wire LTU;
    ALU alu(
        .op(aluOp),
        .aluIn1(aluIn1),
        .aluIn2(aluIn2),
        .aluOut(aluOut),
        .EQ(EQ),
        .LT(LT),
        .LTU(LTU)
    );

`ifdef DEBUG
    alu_vio alu_vio (
        .clk(clk),              // input wire clk
        .probe_in0(aluOp),  // input wire [3 : 0] probe_in0
        .probe_in1(aluIn1),  // input wire [31 : 0] probe_in1
        .probe_in2(aluIn2),  // input wire [31 : 0] probe_in2
        .probe_in3(aluOut),  // input wire [31 : 0] probe_in3
        .probe_in4(EQ),  // input wire [0 : 0] probe_in4
        .probe_in5(LT),  // input wire [0 : 0] probe_in5
        .probe_in6(LTU)  // input wire [0 : 0] probe_in6
    );
`endif

    //Branches
    wire [2:0] branchOp = funct3;
    wire takeBranch = BranchCalc(branchOp, EQ, LT, LTU);

    //Program counter
    wire [31:0] pcPlus4 = pc + 4;
    wire [31:0] pcPlusImm = pc + (isJAL ? Jimm : isAUIPC ? Uimm : Bimm);
    wire [31:0] pcAbs = aluOut;
    wire [2:0] pcOp = ((isBranch && takeBranch) || isJAL) ? PC_REL :
                                                   isJALR ? PC_ABS :
                                                            PC_NEXT;
    assign pcIn = PcNextCalc(pcOp, pcPlus4, pcPlusImm, pcAbs);

    //Memory access
    assign loadstoreAddr = rs1 + (isStore ? Simm : Iimm);
    wire [31:0] loadData;
    MemoryAccess access(
        .memData(memDataR),
        .address(loadstoreAddr[1:0]),
        .size(funct3[1:0]),
        .signExtend(funct3[2]),
        .loadData(loadData)
    );
    wire [31:0] storeData = StoreData(rs2, loadstoreAddr);
    assign storeMask = {4{isStore}} & StoreMask(loadstoreAddr, funct3);
    assign memDataW = storeData;

    //Registers
    wire isJump = isJAL || isJALR;
    assign regIn = isJump  ? pcPlus4 :
                   isLUI   ? Uimm :
                   isAUIPC ? pcPlusImm :
                   isLoad  ? loadData :
                             aluOut;
    assign regLatch = !isBranch && !isStore;

    //Halt
    assign halt = isSYSTEM;
endmodule
