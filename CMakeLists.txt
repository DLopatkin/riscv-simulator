cmake_minimum_required(VERSION 3.10)
project(riscv_simulator)

set(CMAKE_CXX_STANDARD 11)
include_directories(./inc)
add_executable(riscv_simulator src/main.cpp src/decoder.cpp inc/decoder.h inc/opcode.h src/processor.cpp inc/processor.h)