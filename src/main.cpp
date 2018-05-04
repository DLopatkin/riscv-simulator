#include <iostream>
#include <opcode.h>
#include <processor.h>
#include <glog/logging.h>


int main() {
    google::InitGoogleLogging("log.txt");
    FLAGS_stderrthreshold = 0;
    LOG(INFO) << "logging started";
    std::string filename = "/Users/lopatkindaniil/CLionProjects/riscv-simulator/test/a.out";
    Processor processor;
    processor.process(filename);
    return 0;
}