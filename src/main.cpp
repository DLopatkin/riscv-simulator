#include <iostream>
#include <opcode.h>
#include <processor.h>
#include <glog/logging.h>


int main() {
    google::InitGoogleLogging("log.txt");
    FLAGS_logtostderr = 0;
    FLAGS_stderrthreshold = 0;
    FLAGS_log_prefix = 0;
    LOG(INFO) << "logging started";
    std::string filename = "../test/a.out";
    Processor processor;
    processor.process(filename);
    return 0;
}