//
// Created by harld on 29-Apr-18.
//

#ifndef RISCV_SIMULATOR_INSTR_IMPL_H
#define RISCV_SIMULATOR_INSTR_IMPL_H


#include "decoder.h"
#include "context.h"
#include "memory.h"

class Instr_impl {
public:
    typedef void (*instr_impl)(const Instruction &, Hart &, Memory &);

    static int execute(const Instruction &instr, Hart &hart, Memory &mem);


private:



    static void LUI_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void AUIPC_impl(const Instruction &instr, Hart &hart, Memory &mem);

//======================================================================
// Control Transfer Instructions
//======================================================================
    static void JAL_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void JALR_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void BEQ_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void BNE_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void BLT_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void BGE_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void BLTU_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void BGEU_impl(const Instruction &instr, Hart &hart, Memory &mem);

//======================================================================
// Integer Memory Operations
//======================================================================
    static void LB_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void LH_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void LW_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void LBU_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void LHU_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void SB_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void SH_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void SW_impl(const Instruction &instr, Hart &hart, Memory &mem);

//======================================================================
// Integer Register-Immediate Instructions
//======================================================================
    static void ADDI_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void SLTI_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void SLTIU_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void XORI_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void ORI_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void ANDI_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void SLLI_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void SRLI_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void SRAI_impl(const Instruction &instr, Hart &hart, Memory &mem);

//======================================================================
// Integer Register-Register Operations
//======================================================================
    static void ADD_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void SUB_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void SLL_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void SLT_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void SLTU_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void XOR_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void SRL_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void SRA_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void OR_impl(const Instruction &instr, Hart &hart, Memory &mem);
    static void AND_impl(const Instruction &instr, Hart &hart, Memory &mem);


    static constexpr const instr_impl instr_map[] = {
            LUI_impl,
            AUIPC_impl,
            JAL_impl,
            JALR_impl,
            BEQ_impl,
            BNE_impl,
            BLT_impl,
            BGE_impl,
            BLTU_impl,
            BGEU_impl,
            LB_impl,
            LH_impl,
            LW_impl,
            LBU_impl,
            LHU_impl,
            SB_impl,
            SH_impl,
            SW_impl,
            ADDI_impl,
            SLTI_impl,
            SLTIU_impl,
            XORI_impl,
            ORI_impl,
            ANDI_impl,
            SLLI_impl,
            SRLI_impl,
            SRAI_impl,
            ADD_impl,
            SUB_impl,
            SLL_impl,
            SLT_impl,
            SLTU_impl,
            XOR_impl,
            SRL_impl,
            SRA_impl,
            OR_impl,
            AND_impl

    };


};


#endif //RISCV_SIMULATOR_INSTR_IMPL_H
