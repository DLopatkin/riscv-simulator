//
// Created by Лопаткин Даниил on 28.04.2018.
//

#ifndef RISCV_SIMULATOR_DECODER_H
#define RISCV_SIMULATOR_DECODER_H

#include <cstdint>

enum Opcode {
    LUI = 0x37,
    AUIPC = 0x17,
    JAL = 0x6f,
    JALR = 0x67,
    BRANCH = 0x63,
    LOAD = 0x03,
    STORE = 0x23,
    OP_IMM = 0x13,
    OP = 0x33
};

enum Funct3 {
    BEQ = 0x0,
    BNE = 0x1,
    BLT = 0x4,
    BGE = 0x5,
    BLTU = 0x6,
    BGEU = 0x7,

    LB = 0x0,
    LH = 0x1,
    LW = 0x2,
    LBU = 0x4,
    LHU = 0x5,

    SB = 0x0,
    SH = 0x1,
    SW = 0x2,

    ADD = 0x0,
    SUB = 0x0,
    SLL = 0x1,
    SLT = 0x2,
    SLTU = 0x3,
    XOR = 0x4,
    SRL = 0x5,
    SRA = 0x5,
    OR = 0x6,
    AND = 0x7,
};

typedef struct {
    uint8_t opcode;
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;
    uint8_t funct3;
    uint8_t funct7;
    uint32_t imm;
} Instruction;

class Decoder {
public:
    static Instruction decode(int32_t);
};


#endif //RISCV_SIMULATOR_DECODER_H
