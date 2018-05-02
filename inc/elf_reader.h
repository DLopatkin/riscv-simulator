//
// Created by Лопаткин Даниил on 01.05.2018.
//

#ifndef RISCV_SIMULATOR_ELF_READER_H
#define RISCV_SIMULATOR_ELF_READER_H

#include <string>
#include <libelf/sys_elf.h>
#include <libelf/gelf.h>
#include <cstdint>

class ElfReader {
private:
    std::string filename;
    int fd;
    Elf *e;
    GElf_Phdr phdr;
    uint8_t* mem;
    size_t headers_number;

public:
    ElfReader(uint8_t* mem, std::string filename);
    int InitElf();
    void LoadElf();
};

#endif //RISCV_SIMULATOR_ELF_READER_H
