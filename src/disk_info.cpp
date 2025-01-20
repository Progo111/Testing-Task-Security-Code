#include "disk_info.hpp"
#include <iostream>
#include <windows.h>
#include <stdexcept>

void GetDiskInfo(Disks& disks)
{
    std::vector<CHAR> driveStrings(256);
    DWORD size = GetLogicalDriveStringsA(driveStrings.size(), driveStrings.data());

    if (size == 0) {
        throw std::runtime_error("Error when get disk info");
    }

    if (size > driveStrings.size()) {
        DWORD newSize = size;
        driveStrings.resize(newSize);
        GetLogicalDriveStringsA(driveStrings.size(), driveStrings.data());
    }

    for (char* drive = driveStrings.data(); *drive; drive += strlen(drive) + 1) {
        DiskInfo& disk = disks.emplace_back();
        disk.name = drive;

        CHAR fsName[MAX_PATH + 1];
        if (GetVolumeInformationA(drive, nullptr, 0, nullptr, nullptr, nullptr, fsName, sizeof(fsName))) {
            disk.filesystem = fsName;
        } else {
            disk.filesystem = "Unknown";
        }

        ULARGE_INTEGER totalBytes;

        if (GetDiskFreeSpaceExA(drive, nullptr, &totalBytes, nullptr)) {
            disk.sizeInBytes = totalBytes.QuadPart;
        } else {
            disk.sizeInBytes = 0;
        }
    }
}