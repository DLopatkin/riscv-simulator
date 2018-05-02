cmake_minimum_required(VERSION 3.10)
project(riscv_simulator)

set(CMAKE_CXX_STANDARD 11)

if (LIBELF_LIBRARIES AND LIBELF_INCLUDE_DIRS)
    set (LibElf_FIND_QUIETLY TRUE)
endif (LIBELF_LIBRARIES AND LIBELF_INCLUDE_DIRS)

find_path (LIBELF_INCLUDE_DIRS
        NAMES
        libelf.h
        PATHS
        C:/msys64/mingw64/include/libelf
        /mingw64/include/libelf
        /usr/include
        /usr/include/libelf
        /usr/local/include
        /usr/local/include/libelf
        ENV CPATH)

find_library (LIBELF_LIBRARIES
        NAMES
        elf
        PATHS
        /usr/lib
        /usr/local/lib
        ENV LIBRARY_PATH
        ENV LD_LIBRARY_PATH)

include (FindPackageHandleStandardArgs)


# handle the QUIETLY and REQUIRED arguments and set LIBELF_FOUND to TRUE if all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibElf DEFAULT_MSG
        LIBELF_LIBRARIES
        LIBELF_INCLUDE_DIRS)

SET(CMAKE_REQUIRED_LIBRARIES elf)
INCLUDE(CheckCXXSourceCompiles)
CHECK_CXX_SOURCE_COMPILES("#include <libelf.h>
int main() {
  Elf *e = (Elf*)0;
  size_t sz;
  elf_getshdrstrndx(e, &sz);
  return 0;
}" ELF_GETSHDRSTRNDX)

mark_as_advanced(LIBELF_INCLUDE_DIRS LIBELF_LIBRARIES ELF_GETSHDRSTRNDX)

include_directories(./inc)
add_executable(riscv_simulator src/main.cpp src/decoder.cpp inc/decoder.h inc/context.h src/context.cpp inc/instr_impl.h src/instr_impl.cpp inc/opcode.h src/processor.cpp inc/processor.h inc/elf_reader.h src/elf_reader.cpp src/memory.cpp inc/memory.h)

target_link_libraries(riscv_simulator ${LIBELF_LIBRARIES})