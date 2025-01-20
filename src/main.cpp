#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include "arg_parser.hpp"
#include "run_task.hpp"

int main(int argc, char* argv[])
{
    try {
        ProgramOptions options = ParseArguments(argc, argv);

        try {
            RunTask taskRunner(options);
            taskRunner.Run();
        } catch (std::exception& ex) {
            if (options.enableLogging) {
                std::cerr << ex.what();
            } else {
                std::cerr << "Program end with error. To see more information run with \"--log\" argument";
            }
        }

    } catch (std::exception& ex) {
        std::cout << ex.what();
    }
    
    return 0;
}