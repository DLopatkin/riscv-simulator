//
// Created by Лопаткин Даниил on 01.05.2018.
//

#include <elf_reader.h>
#include <fcntl.h>
#include <iostream>

ElfReader::ElfReader(uint8_t mem, std::string filename) {
    this->mem = mem;
    this->filename = filename;
    fd = open( filename.c_str(), O_RDONLY);
}

int ElfReader::InitElf() {

    if (elf_version(EV_CURRENT) == EV_NONE) {
        std::cout << "ELF library initialization failed: " << elf_errmsg(-1) << std::endl;
        return EXIT_FAILURE;
    }

    if (fd < 0) {
        std::cout << "Failed to open " << filename << std::endl;
        return EXIT_FAILURE;
    }

    if ((e = elf_begin(fd, ELF_C_READ, NULL)) == NULL) {
        std::cout << "elf_begin() failed: " << elf_errmsg(-1) << std::endl;
        return EXIT_FAILURE;
    }

    if (elf_kind(e) != ELF_K_ELF) {
        std::cout << filename << " is not an ELF object." << elf_errmsg(-1) << std::endl;
        return EXIT_FAILURE;
    }

    if (elf_getphdrnum(e, &headers_number) != 0) {
        std::cout << "elf_getphdrnum() failed: " << elf_errmsg(-1) << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
