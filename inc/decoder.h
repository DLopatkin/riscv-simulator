//
// Created by Лопаткин Даниил on 28.04.2018.
//

#ifndef RISCV_SIMULATOR_DECODER_H
#define RISCV_SIMULATOR_DECODER_H

#include <cstdint>

enum DecodeOpcode {
    DECODE_LUI = 0x37,
    DECODE_AUIPC = 0x17,
    DECODE_JAL = 0x6f,
    DECODE_JALR = 0x67,
    DECODE_BRANCH = 0x63,
    DECODE_LOAD = 0x03,
    DECODE_STORE = 0x23,
    DECODE_OP_IMM = 0x13,
    DECODE_OP = 0x33
};

enum Funct3 {
    FUNCT_BEQ = 0x0,
    FUNCT_BNE = 0x1,
    FUNCT_BLT = 0x4,
    FUNCT_BGE = 0x5,
    FUNCT_BLTU = 0x6,
    FUNCT_BGEU = 0x7,

    FUNCT_LB = 0x0,
    FUNCT_LH = 0x1,
    FUNCT_LW = 0x2,
    FUNCT_LBU = 0x4,
    FUNCT_LHU = 0x5,

    FUNCT_SB = 0x0,
    FUNCT_SH = 0x1,
    FUNCT_SW = 0x2,

    FUNCT_ADD = 0x0,
    FUNCT_SUB = 0x0,
    FUNCT_SLL = 0x1,
    FUNCT_SLT = 0x2,
    FUNCT_SLTU = 0x3,
    FUNCT_XOR = 0x4,
    FUNCT_SRL = 0x5,
    FUNCT_SRA = 0x5,
    FUNCT_OR = 0x6,
    FUNCT_AND = 0x7
};

typedef struct {
    uint8_t opcode;
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;
    uint32_t imm;
} Instruction;

class Decoder {
public:
    static Instruction decode(uint32_t instr);
};


#endif //RISCV_SIMULATOR_DECODER_H
