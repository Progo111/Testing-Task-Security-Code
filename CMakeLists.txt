cmake_minimum_required(VERSION 3.15)

project(DiskInfoUtility VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DiskInfoUtility 
    src/main.cpp
    src/arg_parser.cpp
    src/disk_info.cpp
    src/file_scanner.cpp
    src/system_info.cpp
    src/run_task.cpp
)

target_include_directories(DiskInfoUtility PRIVATE include)

target_link_libraries(DiskInfoUtility PRIVATE 
    advapi32  
    netapi32   
    user32     
)