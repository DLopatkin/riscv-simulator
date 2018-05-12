//
// Created by harld on 29-Apr-18.
//
#include "instr_impl.h"
#include "opcode.h"
#include "decoder.h"
#include "processor.h"
#include "context.h"
#include <vector>
#include <map>
#include <glog/logging.h>
#include "elf_reader.h"
#include "memory.h"


int Processor::process(std::string filename) {
    Memory* mem = new Memory();
    ElfReader elfReader(mem->get_data(), filename);
    elfReader.InitElf();
    elfReader.LoadElf();

    Hart hart;

    hart.PC = elfReader.GetPC();


    auto linear_block = new std::vector<Instruction>();;
    auto instr_cache = new std::map<uint32_t, std::vector<Instruction> *>();

    uint32_t head_PC = hart.PC;

    while(hart.PC != 0) {

        if (instr_cache->find(hart.PC) != instr_cache->end()) {
            linear_block = (*instr_cache)[hart.PC];
            LOG(WARNING) << "Linear block: PC:" << std::hex << hart.PC << " LEN: " << linear_block->size();
            for (Instruction instr : *linear_block)
            {
                Instr_impl::execute(instr, hart, *mem);
                if(instr.opcode < JAL || instr.opcode > BGEU)
                    hart.PC += 4;
            }
        }
        else
        {
            LOG(WARNING) << "Decode";
            Instruction instr = Decoder::decode(mem->load_word(hart.PC));
            linear_block->push_back(instr);

            Instr_impl::execute(instr, hart, *mem);

            if(instr.opcode < JAL || instr.opcode > BGEU){
                hart.PC += 4;
            } else {
                instr_cache->insert(std::make_pair(head_PC, linear_block));
                head_PC = hart.PC;
                linear_block = new std::vector<Instruction>();
            }
        }



    }
}