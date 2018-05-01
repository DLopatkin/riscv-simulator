//
// Created by harld on 29-Apr-18.
//

#ifndef RISCV_SIMULATOR_INSTR_IMPL_H
#define RISCV_SIMULATOR_INSTR_IMPL_H


#include "decoder.h"

class Instr_impl {
public:
    static int execute(Instruction instr);
private:

    typedef int (*instr_impl)();

    static int LUI_impl();
    static int AUIPC_impl();
    static int JAL_impl();
    static int JALR_impl();
    static int BEQ_impl();
    static int BNE_impl();
    static int BLT_impl();
    static int BGE_impl();
    static int BLTU_impl();
    static int BGEU_impl();
    static int LB_impl();
    static int LH_impl();
    static int LW_impl();
    static int LBU_impl();
    static int LHU_impl();
    static int SB_impl();
    static int SH_impl();
    static int SW_impl();
    static int ADDI_impl();
    static int SLTI_impl();
    static int SLTIU_impl();
    static int XORI_impl();
    static int ORI_impl();
    static int ANDI_impl();
    static int SLLI_impl();
    static int SRLI_impl();
    static int SRAI_impl();
    static int ADD_impl();
    static int SUB_impl();
    static int SLL_impl();
    static int SLT_impl();
    static int SLTU_impl();
    static int XOR_impl();
    static int SRL_impl();
    static int SRA_impl();
    static int OR_impl();
    static int AND_impl();



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
