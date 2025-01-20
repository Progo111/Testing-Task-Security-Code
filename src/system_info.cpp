#include <windows.h>
#include <lm.h>
#include <codecvt>
#include <stdexcept>
#include "system_info.hpp"


bool SetCurrentUserName(UserInfo& user) 
{
    char username[UNLEN + 1];
    DWORD size = UNLEN + 1;
    if (GetUserNameA(username, &size)) {
        user.userName = username;
        return true;
    }
    user.userName = UNKNOWN_USER_NAME;
    return false;
}

bool SetComputerName(UserInfo& user) 
{
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
    if (GetComputerNameA(computerName, &size)) {
        user.workStationName = computerName;
        return true;
    }
    user.workStationName = UNKNOWN_COMPUTER_NAME;
    return false;
}

void SetUserGroups(UserInfo& user) 
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::vector<std::string> groups;
    std::wstring wUserName = converter.from_bytes(user.userName);
    DWORD entriesRead = 0, totalEntries = 0;
    LPLOCALGROUP_USERS_INFO_0 pBuf = NULL;

    if (NetUserGetLocalGroups(NULL, wUserName.c_str(), 0, LG_INCLUDE_INDIRECT, (LPBYTE*)&pBuf, MAX_PREFERRED_LENGTH, &entriesRead, &totalEntries) == NERR_Success) {
        for (DWORD i = 0; i < entriesRead; i++) {
            groups.emplace_back(converter.to_bytes(pBuf[i].lgrui0_name));
        }
    }
    if (pBuf) {
        NetApiBufferFree(pBuf);
    }
    user.groups = groups;
}

void GetUserInfo(UserInfo& user)
{
    if (!SetCurrentUserName(user)) {
        throw std::runtime_error(USER_INFO_ERROR_MESSAGE + "Can't get user name");
    }

    if (!SetComputerName(user)) {
        throw std::runtime_error(USER_INFO_ERROR_MESSAGE + "Can't get computer name");
    }

    SetUserGroups(user);
}