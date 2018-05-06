//
// Created by harld on 29-Apr-18.
//

#include <glog/logging.h>
#include "opcode.h"
#include "instr_impl.h"


#define  RD hart.regfile[instr.rd]
#define RS1 hart.regfile[instr.rs1]
#define RS2 hart.regfile[instr.rs2]
#define IMM instr.imm

constexpr const Instr_impl::instr_impl Instr_impl::instr_map[];

int Instr_impl::execute(const Instruction &instr, Hart &hart, Memory &mem) {
    LOG(INFO) << "PC: " << std::hex << hart.PC;
    Instr_impl::instr_map[instr.opcode](instr, hart, mem);
    return 0;
}


void Instr_impl::LUI_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    if (instr.rd == x0) {
        return;
    }
    RD = IMM;
    LOG(INFO) << "LUI: x" << (int) instr.rd << ": " << RD
              << " = " << IMM;

}

void  Instr_impl::AUIPC_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    if (instr.rd == x0) {
        return;
    }
    RD = IMM + hart.PC;
    LOG(INFO) << "AUIPC: x" << (int) instr.rd << ": " << RD
              << " = " << IMM << " + PC: "  << hart.PC;
}

//======================================================================
// Control Transfer Instructions
//======================================================================
void Instr_impl::JAL_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    if ( instr.rd != x0) {
        RD = hart.PC + 4;
        LOG(INFO) << "JAL: x" << (int) instr.rd << ": " << RD << " = PC:" << hart.PC << " + 4";
    }
    hart.PC += (int32_t) IMM;
    LOG(INFO) << "JAL: PC: " << hart.PC << " += " << (int32_t) IMM;
}

void Instr_impl::JALR_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    if ( instr.rd != x0)
        RD = hart.PC + 4;
    // todo check
    hart.PC = RS1 + IMM;
    LOG(INFO) << "JAL: PC: " << hart.PC << " = x" << (int) instr.rs1 << ": "<< RS1 <<" + " << IMM;
}

void Instr_impl::BEQ_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    if (RS1 == RS2)
        hart.PC += IMM;
    else
        hart.PC += 4;
    LOG(INFO) << "BEQ: PC: " << hart.PC << " = (x" << (int) instr.rs1 << ": " << RS1
              << " == x" << (int) instr.rs2 << ": " << RS2 << ") ? PC + " << IMM << " : PC";
}

void Instr_impl::BNE_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    if (RS1 != RS2)
        hart.PC += IMM;
    else
        hart.PC += 4;
    LOG(INFO) << "BNE: PC: " << hart.PC << " = (x" << (int) instr.rs1 << ": " << RS1
              << " != x" << (int) instr.rs2 << ": " << RS2 << ") ? PC + " << IMM << " : PC";
}

void Instr_impl::BLT_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    if ((int32_t) RS1 < (int32_t) RS2)
        hart.PC += IMM;
    else
        hart.PC += 4;
    LOG(INFO) << "BLT: PC: " << hart.PC << " = (x" << (int) instr.rs1 << ": " << (int32_t) RS1
              << " < x" << (int) instr.rs2 << ": " << (int32_t) RS2 << ") ? PC + " << IMM << " : PC";
}

void Instr_impl::BGE_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    if ((int32_t) RS1 >= (int32_t) RS2)
        hart.PC += IMM;
    else
        hart.PC += 4;
    LOG(INFO) << "BGE: PC: " << hart.PC << " = (x" << (int) instr.rs1 << ": " << (int32_t) RS1
              << " >= x" << (int) instr.rs2 << ": " << (int32_t) RS2 << ") ? PC + " << IMM << " : PC";
}

void Instr_impl::BLTU_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    if (RS1 < RS2)
        hart.PC += IMM;
    else
        hart.PC += 4;
    LOG(INFO) << "BLTU: PC: " << hart.PC << " = (x" << (int) instr.rs1 << ": " << RS1
              << " < x" << (int) instr.rs2 << ": " << RS2 << ") ? PC + " << IMM << " : PC";
}

void Instr_impl::BGEU_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    if (RS1 >= RS2)
        hart.PC += IMM;
    else
        hart.PC += 4;
    LOG(INFO) << "BGEU: PC: " << hart.PC << " = (x" << (int) instr.rs1 << ": " << RS1
              << " >= x" << (int) instr.rs2 << ": " << RS2 << ") ? PC + " << IMM << " : PC";
}



//======================================================================
// Integer Memory Operations
//======================================================================

void Instr_impl::LB_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    if (instr.rd == x0) {
        return;
    }
    RD = mem.load_byte(RS1 + IMM);
    LOG(INFO) << "LB: x" << (int) instr.rd << ": " << RD
              << " load from (x" << (int) instr.rs1 << ": "<< RS1 <<" + " << (int32_t) IMM << ")";
}

void Instr_impl::LH_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    if (instr.rd == x0) {
        return;
    }
    RD = mem.load_half(RS1 + IMM);
    LOG(INFO) << "LH: x" << (int) instr.rd << ": " << RD
              << " load from (x" << (int) instr.rs1 << ": "<< RS1 <<" + " << (int32_t) IMM << ")";
}

void Instr_impl::LW_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    if (instr.rd == x0) {
        return;
    }
    RD = mem.load_word(RS1 + IMM);
    LOG(INFO) << "LW: x" << (int) instr.rd << ": " << RD
              << " load from (x" << (int) instr.rs1 << ": "<< RS1 <<" + " << (int32_t) IMM << ")";
}

void Instr_impl::LBU_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    if (instr.rd == x0) {
        return;
    }
    RD = mem.load_byteu(RS1 + IMM);
    LOG(INFO) << "LBU: x" << (int) instr.rd << ": " << RD
              << " load from (x" << (int) instr.rs1 << ": "<< RS1 <<" + " << (int32_t) IMM << ")";
}

void Instr_impl::LHU_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    if (instr.rd == x0) {
        return;
    }
    RD = mem.load_halfu(RS1 + IMM);
    LOG(INFO) << "LHU: x" << (int) instr.rd << ": " << RD
              << " load from (x" << (int) instr.rs1 << ": "<< RS1 <<" + " << (int32_t) IMM << ")";
}

void Instr_impl::SB_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    mem.store_byte(RS1 + IMM, (uint8_t) (RS2 & 0xFF));
    LOG(INFO) << "SB: x" << (int) instr.rs2 << ": " << RS2
              << " store to (x" << (int) instr.rs1 << ": "<< RS1 <<" + " << (int32_t) IMM << ")";
}

void Instr_impl::SH_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    mem.store_half(RS1 + IMM, (uint16_t) (RS2 & 0xFFFF));
    LOG(INFO) << "SH: x" << (int) instr.rs2 << ": " << RS2
              << " store to (x" << (int) instr.rs1 << ": "<< RS1 <<" + " << (int32_t) IMM << ")";
}

void Instr_impl::SW_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    mem.store_word(RS1 + IMM, RS2);
    LOG(INFO) << "SW: x" << (int) instr.rs2 << ": " << RS2
              << " store to (x" << (int) instr.rs1 << ": "<< RS1 <<" + " << (int32_t) IMM << ")";
}


//======================================================================
// Integer Register-Immediate Instructions
//======================================================================
void Instr_impl::ADDI_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = RS1 + IMM;
    LOG(INFO) << "ADDI: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " + " << (int32_t) IMM;
}

void Instr_impl::SLTI_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = (int32_t)RS1 < (int32_t)IMM ? 1 : 0;
    LOG(INFO) << "SLTI: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << (int32_t) RS1 << " < " << (int32_t) IMM;
}

void Instr_impl::SLTIU_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = RS1 < IMM ? 1 : 0;
    LOG(INFO) << "SLTIU: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " < " << IMM;
}


void Instr_impl::XORI_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = RS1 ^ IMM;
    LOG(INFO) << "XORI: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " ^ " << IMM;
}

void Instr_impl::ORI_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = RS1 | IMM;
    LOG(INFO) << "ORI: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " | " << IMM;
}

void Instr_impl::ANDI_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = RS1 & IMM;
    LOG(INFO) << "ANDI: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " & " << IMM;
}


void Instr_impl::SLLI_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = RS1 << instr.rs2;
    LOG(INFO) << "SLLI: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " << " << (int32_t) IMM;
}

void Instr_impl::SRLI_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = RS1 >> instr.rs2;
    LOG(INFO) << "SRLI: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " >> " << (int32_t) IMM;
}

void Instr_impl::SRAI_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = (int32_t)RS1 >> instr.rs2;
    LOG(INFO) << "SRAI: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " >> " << (int32_t) IMM;
}

//======================================================================
// Integer Register-Register Operations
//======================================================================
void Instr_impl::ADD_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = RS1 + RS2;
    LOG(INFO) << "ADD: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " + x" << (int) instr.rs2 << ": " << RS2;
}

void Instr_impl::SUB_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = RS1 - RS2;
    LOG(INFO) << "SUB: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " - x" << (int) instr.rs2 << ": " << RS2;
}

void Instr_impl::SLT_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = (int32_t)RS1 < (int32_t)RS2 ? 1 : 0;
    LOG(INFO) << "SLT: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << (int32_t) RS1 << " < x" << (int) instr.rs2 << ": " << (int32_t) RS2;
}

void Instr_impl::SLTU_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = RS1 < RS2 ? 1 : 0;
    LOG(INFO) << "SLTU: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " < x" << (int) instr.rs2 << ": " << RS2;
}

void Instr_impl::XOR_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = RS1 ^ RS2;
    LOG(INFO) << "XOR: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " ^ x" << (int) instr.rs2 << ": " << RS2;
}

void Instr_impl::OR_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = RS1 | RS2;
    LOG(INFO) << "OR: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " | x" << (int) instr.rs2 << ": " << RS2;
}

void Instr_impl::AND_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = RS1 & RS2;
    LOG(INFO) << "AND: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " & x" << (int) instr.rs2 << ": " << RS2;
}


void Instr_impl::SLL_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = RS1 << (RS2 & 0x1F);
    LOG(INFO) << "ADD: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " << x" << (int) instr.rs2 << ": " << (RS2 & 0x1F);
}

void Instr_impl::SRL_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = RS1 >> (RS2 & 0x1F);
    LOG(INFO) << "ADD: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << RS1 << " >> x" << (int) instr.rs2 << ": " << (RS2 & 0x1F);
}

void Instr_impl::SRA_impl(const Instruction &instr, Hart &hart, Memory &mem) {
    RD = (int32_t) RS1 >> (RS2 & 0x1F);
    LOG(INFO) << "ADD: x" << (int) instr.rd << ": " << RD
              << " = x" << (int) instr.rs1 << ": " << (int32_t) RS1 << " >> x" << (int) instr.rs2 << ": " << (RS2 & 0x1F);
}



