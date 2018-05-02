//
// Created by harld on 02-May-18.
//


#include "memory.h"

Memory::Memory() = default;

Memory::~Memory() = default;

uint8_t* Memory::get_data() {
    return memory.data();
}

uint32_t Memory::load_word(uint32_t address) {
    return (uint32_t) (memory[address] + memory[address+1] * 0x100 +
           memory[address+2] * 0x10000 + memory[address+3] * 0x1000000);
}

uint32_t Memory::load_half(uint32_t address) {
    int32_t tmp = (int16_t) memory[address] + memory[address+1] * 0x100;
    return (uint32_t) tmp;
}

uint32_t Memory::load_halfu(uint32_t address) {
    return (uint32_t) memory[address] + memory[address+1] * 0x100;
}

uint32_t Memory::load_byte(uint32_t address) {
    int32_t tmp = (int8_t) memory[address];
    return (uint32_t) tmp;
}

uint32_t Memory::load_byteu(uint32_t address) {
    return (uint32_t) memory[address];
}

void Memory::store_word(uint32_t address, uint32_t value) {
    *(uint32_t *)(this->get_data() + address) = value;
}

void Memory::store_half(uint32_t address, uint16_t value) {
    *(uint16_t *)(this->get_data() + address) = value;
}

void Memory::store_byte(uint32_t address, uint8_t value) {
    this->get_data()[address] = value;
}