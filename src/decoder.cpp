//
// Created by Лопаткин Даниил on 28.04.2018.
//
#include "decoder.h"


#define MASK(len) ( (1u << (len)) - 1u)
#define BITS(src, offset, len) (( (src) >> (len) ) & MASK( (len) ))

#define OPCODE(instr) ( (uint8_t) ( (instr) & MASK(7)) )

#define RD(instr) ( (uint8_t) (BITS( (instr), 7u, 5u )))
#define RS1(instr) ((uint8_t) (BITS( (instr), 15u, 5u )))
#define RS2(instr) ((uint8_t) (BITS( (instr), 20u, 5u )))

#define FUNCT3(instr) ( (uint8_t) (BITS((instr), 12u, 7u )))
#define FUNCT7(instr) ((uint8_t) (BITS( (instr), 25u, 7u )))

#define IMM_U(instr) ( (instr) >> 12u << 12u)
#define IMM_I(instr) (BITS( (instr), 20u, 12u ))
#define IMM_S(instr) (BITS( (instr), 7u, 5u ) \
                     | (BITS( (instr), 25u,7u ) << 5u ))
#define IMM_B(instr) ((BITS( (instr), 8u, 4u) << 1u) \
                     | (BITS( (instr), 25u, 6u) << 5u) \
                     | (BITS( (instr), 7u, 1u) << 11u) \
                     | (BITS( (instr), 31u, 1u) << 12u))
#define IMM_J(instr) ((BITS( (instr), 31u, 1u) << 20u) \
                     | (BITS( (instr), 21u, 10u) << 21u) \
                     | (BITS( (instr), 20u, 1u) << 11u) \
                     | (BITS( (instr), 12u, 8u) << 12u))

Instruction Decoder::decode(uint32_t instr) {
    Instruction decoded_result;
    uint8_t opcode = OPCODE(instr);
    uint8_t funct3 = ERROR_FUNCT;
    uint8_t type = ERR_TYPE;
    switch (opcode) {
        case DECODE_LUI: {
            decoded_result.opcode = LUI;
            type = U_TYPE;
            break;
        }

        case DECODE_AUIPC: {
            decoded_result.opcode = AUIPC;
            type = U_TYPE;
            break;
        }

        case DECODE_JAL: {
            decoded_result.opcode = JAL;
            type = J_TYPE;
            break;
        }

        case DECODE_JALR: {
            decoded_result.opcode = JALR;
            type = I_TYPE;
            break;
        }

        case DECODE_BRANCH: {
            funct3 = FUNCT3(instr);
            type = B_TYPE;
            switch (funct3) {
                case FUNCT_BEQ:
                    decoded_result.opcode = BEQ;
                    break;

                case FUNCT_BNE:
                    decoded_result.opcode = BNE;
                    break;

                case FUNCT_BLT:
                    decoded_result.opcode = BLT;
                    break;

                case FUNCT_BGE:
                    decoded_result.opcode = BGE;
                    break;

                case FUNCT_BGEU:
                    decoded_result.opcode = BGEU;
                    break;

                case FUNCT_BLTU:
                    decoded_result.opcode = BLTU;
                    break;

                default:
                    break;
            }
            break;
        }

        case DECODE_LOAD: {
            funct3 = FUNCT3(instr);
            type = I_TYPE;
            switch (funct3) {
                case FUNCT_LB:
                    decoded_result.opcode = LB;
                    break;

                case FUNCT_LH:
                    decoded_result.opcode = LH;
                    break;

                case FUNCT_LW:
                    decoded_result.opcode = LW;
                    break;

                case FUNCT_LBU:
                    decoded_result.opcode = LBU;
                    break;

                case FUNCT_LHU:
                    decoded_result.opcode = LHU;
                    break;

                default:
                    break;
            }
            break;
        }

        case DECODE_STORE: {
            funct3 = FUNCT3(instr);
            type = S_TYPE;
            switch (funct3) {
                case FUNCT_SB:
                    decoded_result.opcode = SB;
                    break;

                case FUNCT_SH:
                    decoded_result.opcode = SH;
                    break;

                case FUNCT_SW:
                    decoded_result.opcode = SW;
                    break;

                default:
                    break;
            }
            break;
        }

        case DECODE_OP_IMM: {
            funct3 = FUNCT3(instr);
            type = I_TYPE;
            switch (funct3) {
                case FUNCT_ADD:
                    decoded_result.opcode = ADDI;
                    break;

                case FUNCT_SLL:
                    type = R_TYPE;
                    decoded_result.opcode = SLLI;
                    break;

                case FUNCT_SLT:
                    decoded_result.opcode = SLTI;
                    break;

                case FUNCT_SLTU:
                    decoded_result.opcode = SLTIU;
                    break;

                case FUNCT_XOR:
                    decoded_result.opcode = XORI;
                    break;

                case FUNCT_SRL:
                    type = R_TYPE;
                    decoded_result.opcode = FUNCT7(instr) ? SRAI : SRLI;
                    break;

                case FUNCT_OR:
                    decoded_result.opcode = ORI;
                    break;

                case FUNCT_AND:
                    decoded_result.opcode = ANDI;
                    break;

                default:
                    break;
            }
            break;
        }

        case DECODE_OP: {
            funct3 = FUNCT3(instr);
            uint8_t funct7 = FUNCT7(instr);
            type = R_TYPE;
            switch (funct3) {
                case FUNCT_ADD:
                    decoded_result.opcode = funct7 ? SUB : ADD;
                    break;

                case FUNCT_SLL:
                    decoded_result.opcode = SLL;
                    break;

                case FUNCT_SLT:
                    decoded_result.opcode = SLT;
                    break;

                case FUNCT_SLTU:
                    decoded_result.opcode = SLTU;
                    break;

                case FUNCT_XOR:
                    decoded_result.opcode = XOR;
                    break;

                case FUNCT_SRL:
                    decoded_result.opcode = funct7 ? SRA : SRL;
                    break;

                case FUNCT_OR:
                    decoded_result.opcode = OR;
                    break;

                case FUNCT_AND:
                    decoded_result.opcode = AND;
                    break;

                default:
                    break;
            }
            break;
        }

        default:break;
    }

    switch (type) {
        case R_TYPE:
            decoded_result.rd = RD(instr);
            decoded_result.rs1 = RS1(instr);
            decoded_result.rs2 = RS2(instr);
            break;

        case I_TYPE:
            decoded_result.rd = RD(instr);
            decoded_result.rs1 = RS1(instr);
            decoded_result.imm = IMM_I(instr);
            break;

        case S_TYPE:
            decoded_result.rs1 = RS1(instr);
            decoded_result.rs2 = RS2(instr);
            decoded_result.imm = IMM_S(instr);
            break;

        case B_TYPE:
            decoded_result.rs1 = RS1(instr);
            decoded_result.rs2 = RS2(instr);
            decoded_result.imm = IMM_B(instr);
            break;

        case U_TYPE:
            decoded_result.rd = RD(instr);
            decoded_result.imm = IMM_U(instr);
            break;

        case J_TYPE:
            decoded_result.rd = RD(instr);
            decoded_result.imm = IMM_J(instr);
            break;

        default:break;
    }

    return decoded_result;
}