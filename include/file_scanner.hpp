#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>


struct FileInfo {
    std::string fileName;
    std::string creatTime;
    bool isDirectory;
    unsigned long countFiles;
    unsigned long countDirectory;
};

typedef std::vector<FileInfo> Files;

class ScanDirectory {
    std::weak_ptr<Files> m_pFiles;
    bool& m_enableLogging;
public:
    ScanDirectory(std::weak_ptr<Files> pFiles, bool& enableLogging);
    void Scan(const std::string& path);
};
