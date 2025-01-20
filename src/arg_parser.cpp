#include "arg_parser.hpp"
#include <stdexcept>
#include <iostream>

ProgramOptions ParseArguments(int argc, char* argv[])
{
    ProgramOptions options;
    for (int i = 1; i < argc; ++i) {
        std::string arg {argv[i]};

        if (arg == "-o" && i + 1 < argc) {
            options.outputFile = argv[++i];
        } else if (arg == "--task") {

            if (i + 1 >= argc) {
                throw std::invalid_argument(TASK_INVALID_ARGUMENT_MESSAGE);
            }

            std::string taskNumber = argv[++i];
            if (taskNumber == "1") {
                options.task = DiskTask;
            } else if (taskNumber == "2") {
                options.task = FileScanTask;
            } else if (taskNumber == "3") {
                options.task = UserInfoTask;
            } else {
                throw std::invalid_argument(TASK_INVALID_ARGUMENT_MESSAGE);
            }
        } else if (arg == "--log") {
            options.enableLogging = true;
        } else {
            throw std::invalid_argument(UNKNOWN_ARGUMEN_MESSAGE + arg);
        }
    }
    return options;
}