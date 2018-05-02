//
// Created by harld on 02-May-18.
//

#ifndef RISCV_SIMULATOR_MEMORY_H
#define RISCV_SIMULATOR_MEMORY_H

#include <cstdint>
#include <array>

class Memory {
private:
    std::array<uint8_t, 0x1000000> memory;
public:
    Memory();
    ~Memory();

    uint8_t* get_data();

    uint32_t load_word(uint32_t  address);
    uint32_t load_half(uint32_t  address);
    uint32_t load_halfu(uint32_t address);
    uint32_t load_byte(uint32_t  address);
    uint32_t load_byteu(uint32_t address);

    void store_word(uint32_t address, uint32_t value);
    void store_half(uint32_t address, uint16_t value);
    void store_byte(uint32_t address, uint8_t  value);

};




#endif //RISCV_SIMULATOR_MEMORY_H
