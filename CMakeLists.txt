cmake_minimum_required(VERSION 3.10)
project(riscv_simulator)

set(CMAKE_CXX_STANDARD 11)
include_directories(./inc)
add_executable(riscv_simulator src/main.cpp src/decoder.cpp inc/decoder.h inc/opcode.h src/Processor.cpp inc/Processor.h src/Instr_impl.cpp inc/Instr_impl.h src/Contex.cpp inc/Contex.h)