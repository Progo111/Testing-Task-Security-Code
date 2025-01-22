#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>


struct FileInfo {
    std::string fileName;
    std::string creatTime;
    bool isDirectory;
};

typedef std::vector<FileInfo> Files;

class ScanDirectory {
    std::weak_ptr<Files> m_pFiles;
    bool& m_enableLogging;
    size_t* m_cntFiles;
    size_t* m_cntDir;
public:
    ScanDirectory(std::weak_ptr<Files> pFiles, bool& enableLogging, size_t* cntFiles, size_t* cntDir);
    void Scan(const std::string& path);
};
