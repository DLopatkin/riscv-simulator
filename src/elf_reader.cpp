//
// Created by Лопаткин Даниил on 01.05.2018.
//

#include <elf_reader.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <libelf/sys_elf.h>

ElfReader::ElfReader(uint8_t* mem, std::string filename) {
    this->mem = mem;
    this->filename = filename;
    fd = open( filename.c_str(), O_RDONLY);
}

int ElfReader::InitElf() {

    if (elf_version(EV_CURRENT) == EV_NONE) {
        std::cerr << "ELF library initialization failed: " << elf_errmsg(-1) << std::endl;
        return EXIT_FAILURE;
    }

    if (fd < 0) {
        std::cerr << "Failed to open " << filename << std::endl;
        return EXIT_FAILURE;
    }

    if ((e = elf_begin(fd, ELF_C_READ, NULL)) == NULL) {
        std::cerr << "elf_begin() failed: " << elf_errmsg(-1) << std::endl;
        return EXIT_FAILURE;
    }

    if (elf_kind(e) != ELF_K_ELF) {
        std::cerr << filename << " is not an ELF object." << elf_errmsg(-1) << std::endl;
        return EXIT_FAILURE;
    }

    if ( gelf_getehdr(e, &ehdr) == NULL  ) {
        std::cerr << " gelf_getehdr() failed: " << std::endl;
        return EXIT_FAILURE;
    }

    if ( gelf_getclass(e) != ELFCLASS32  ) {
        std::cerr << " Wrong ELF class: " << std::endl;
        return EXIT_FAILURE;
    }

    if (elf_getphdrnum(e, &headers_number) != 0) {
        std::cerr << "elf_getphdrnum() failed: " << elf_errmsg(-1) << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void ElfReader::LoadElf() {
    for (int i = 0; i < headers_number; i++) {
        if (gelf_getphdr(e, i, &phdr) != &phdr) {
            std::cerr << "gelf_getphdr() failed." << std::endl;
        }
        if (phdr.p_type == PT_LOAD) {
            off_t offset = lseek(fd, 0, SEEK_CUR);
            lseek(fd, phdr.p_offset, SEEK_SET);
            read(fd, mem + phdr.p_vaddr, phdr.p_filesz);
            lseek(fd, offset, SEEK_SET);
        }
    }
}

ElfReader::~ElfReader() {
    elf_end(e);
    close(fd);
}

uint32_t ElfReader::GetPC() {
    return ehdr.e_entry;
}
