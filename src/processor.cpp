//
// Created by harld on 29-Apr-18.
//
#include "instr_impl.h"
#include "opcode.h"
#include "decoder.h"
#include "processor.h"
#include "context.h"
#include <vector>
#include <elf_reader.h>
#include <memory.h>
#include <opcode.h>


int Processor::process(std::string filename) {

    Memory mem;
    ElfReader elfReader(mem.get_data(), filename);
    elfReader.InitElf();
    elfReader.LoadElf();

    Hart hart;

    while(true) {
        Instruction instr = Decoder::decode(mem.load_word(hart.PC));

        Instr_impl::execute(instr, hart, mem);

        if(instr.opcode < JAL || instr.opcode >BGEU)
            hart.PC += 4;
    }


}