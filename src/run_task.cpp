#include <iostream>
#include <stdexcept>
#include <ranges>
#include "run_task.hpp"
#include "disk_info.hpp"
#include "file_scanner.hpp"
#include "system_info.hpp"

namespace rng = std::ranges;
namespace view = rng::views;

void RunTask::DiskTaskHandler()
{
    Disks disks;
    GetDiskInfo(disks);
    for (auto& disk : disks) {
        m_outFile << "DiskName: " << disk.name << std::endl
                << "DiskSize: " << disk.sizeInBytes << std::endl
                << "DiskFilesys: " << disk.filesystem << std::endl << std::endl;
    }
}

void RunTask::FileScannerTaskHandler()
{
    Disks disks;
    GetDiskInfo(disks);


    for (auto& disk : disks) {
        std::shared_ptr<Files> fileArray = std::make_shared<Files>();
        std::unique_ptr<size_t> cntFiles = std::make_unique<size_t>(0);
        std::unique_ptr<size_t> cntDir = std::make_unique<size_t>(0);
        ScanDirectory scanDirectory {fileArray, m_options.enableLogging, cntFiles.get(), cntDir.get()};

        scanDirectory.Scan(disk.name);

        m_outFile << "Volume: " << disk.name << std::endl 
                    << "Count Dirs: " << *cntDir << ", Count Files: " << *cntFiles << std::endl << std::endl;

        for (auto& file : *fileArray) {
            m_outFile << "FileName: " << file.fileName << ", "
                    << "IsDir: " << file.isDirectory << ", "
                    << "CreationTime: " << file.creatTime << std::endl;
        }
        m_outFile << std::endl;
    }

}

void RunTask::UserInformationTaskHandler()
{
    UserInfo user;
    GetUserInfo(user);

    m_outFile << "User name: " << user.userName << std::endl
                << "Computer name: " << user.workStationName << std::endl
                << "Groups: ";

    for (size_t i : view::iota(0, (long)user.groups.size())) {
        m_outFile << user.groups[i] << (i + 1 < user.groups.size() ? ", " : "\n");
    }
}

RunTask::RunTask(ProgramOptions& options) : m_options(options)
{
    m_outFile.open(options.outputFile);
    if (!m_outFile.is_open()) {
        throw std::runtime_error("Can't open file in RunTask constructor: " + options.outputFile);
    }
}

RunTask::~RunTask()
{
    m_outFile.close();
}

void RunTask::Run()
{
    switch (m_options.task) {
        case DiskTask:
            DiskTaskHandler();
            break;
        case FileScanTask:
            FileScannerTaskHandler();
            break;
        case UserInfoTask:
            UserInformationTaskHandler();
            break;
        
        default:
            break;
    }
}