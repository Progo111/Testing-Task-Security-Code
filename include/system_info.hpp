#pragma once

#include <string>
#include <vector>

#define UNKNOWN_USER_NAME "UnkownUser"
#define UNKNOWN_COMPUTER_NAME "UnkownComputer"
const std::string USER_INFO_ERROR_MESSAGE("Error in GetUserInfo: ");

struct UserInfo {
    std::string userName;
    std::vector<std::string> groups;
    std::string workStationName;
};

void GetUserInfo(UserInfo& user);