#pragma once
#include <string>

const std::string TASK_INVALID_ARGUMENT_MESSAGE("Need argument \"--task {1, 2, 3}\"");
const std::string UNKNOWN_ARGUMEN_MESSAGE("Unknown argument: ");

enum Task {DiskTask, FileScanTask, UserInfoTask, UndefindedTask};

struct ProgramOptions {
    std::string outputFile = "output.txt";
    bool enableLogging = false;
    Task task = UndefindedTask;
};

ProgramOptions ParseArguments(int argc, char* argv[]);