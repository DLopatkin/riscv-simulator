//
// Created by harld on 29-Apr-18.
//

#ifndef RISCV_SIMULATOR_PROCESSOR_H
#define RISCV_SIMULATOR_PROCESSOR_H


#include <cstdint>

class processor {
public:
    static int process(uint32_t code[]);
};

#endif //RISCV_SIMULATOR_PROCESSOR_H
