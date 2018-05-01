//
// Created by harld on 29-Apr-18.
//

#ifndef RISCV_SIMULATOR_CONTEX_H
#define RISCV_SIMULATOR_CONTEX_H

#include <array>
#include <cstdint>

typedef std::array<int32_t, 32> Regfile_t;

class Contex {
public:
    Regfile_t regfile;
    uint32_t PC;

};


#endif //RISCV_SIMULATOR_CONTEX_H
