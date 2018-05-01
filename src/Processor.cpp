//
// Created by harld on 29-Apr-18.
//
#include "Instr_impl.h"
#include "opcode.h"
#include "decoder.h"
#include "Processor.h"
#include "Contex.h"


typedef std::vector<uint32_t> code_t;

int Processor::process(code_t code) {
    Instruction instruction = Decoder::decode(*code++);

    Contex contex = new Context();


    Instr_impl::execute(instruction);
}