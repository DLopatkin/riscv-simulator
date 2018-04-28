cmake_minimum_required(VERSION 3.10)
project(riscv_simulator)

set(CMAKE_CXX_STANDARD 11)

add_executable(riscv_simulator main.cpp decoder.cpp decoder.h)