#pragma once
#include "arg_parser.hpp"
#include <fstream>

class RunTask {
    ProgramOptions m_options;
    std::ofstream m_outFile;
    void DiskTaskHandler();
    void FileScannerTaskHandler();
    void UserInformationTaskHandler();
public:
    RunTask(ProgramOptions& options);
    ~RunTask();
    void Run();
};