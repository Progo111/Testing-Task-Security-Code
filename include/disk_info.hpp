#pragma once
#include <string>
#include <vector>


struct DiskInfo {
    std::string name;
    unsigned long long sizeInBytes;
    std::string filesystem;
};

typedef std::vector<DiskInfo> Disks;

void GetDiskInfo(Disks& disks);