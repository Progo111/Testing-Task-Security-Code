#include <windows.h>
#include <iostream>
#include "file_scanner.hpp"

std::string ConvertFileTimeToString(const FILETIME& ft) {
    SYSTEMTIME st;
    FileTimeToSystemTime(&ft, &st);
    char buffer[17];
    sprintf_s(buffer, "%04d-%02d-%02d %02d-%02d", 
              st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);

    return std::string(buffer);
}

ScanDirectory::ScanDirectory(std::weak_ptr<Files> pFiles, bool& enableLogging) : m_pFiles(pFiles), m_enableLogging(enableLogging)
{
}

void ScanDirectory::Scan(const std::string& path)
{
    std::shared_ptr<Files> pSharedFiles = m_pFiles.lock();
    if ( pSharedFiles == nullptr ) {
        throw std::runtime_error("Error can't get shared_ptr in Scan");
    }

    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA((path + "*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        if (m_enableLogging) {
            std::cerr << "Debug: Invalid handle value in ScanDirectory with path: \"" + path + "\""<< std::endl;
        }
        return;
    }

    while (1) {
        std::string name = findFileData.cFileName;
        if (name != "." && name != "..") {
            std::string fullPath = path + name;
            bool isDir = (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

            std::string creationTime = ConvertFileTimeToString(findFileData.ftCreationTime);

            pSharedFiles->emplace_back(fullPath, creationTime, isDir, 0, 0);

            if (isDir) {
                Scan(fullPath + "\\");
            }
        }  

        if (!FindNextFileA(hFind, &findFileData)) {
            break;
        }
    }

    FindClose(hFind);
}