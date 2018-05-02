//
// Created by harld on 29-Apr-18.
//

#ifndef RISCV_SIMULATOR_CONTEX_H
#define RISCV_SIMULATOR_CONTEX_H

#include <array>
#include <cstdint>

typedef std::array<uint32_t, 32> Regfile_t;

class Hart {
public:
    Regfile_t regfile;
    uint32_t PC;

    Hart();
};




#endif //RISCV_SIMULATOR_CONTEX_H
