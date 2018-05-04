#include <iostream>
#include <opcode.h>
#include <processor.h>


int main() {
    std::string filename = "/Users/lopatkindaniil/CLionProjects/riscv-simulator/test/a.out";
    Processor processor;
    processor.process(filename);
    return 0;
}