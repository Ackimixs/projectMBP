#include "Utils.hpp"

bool Utils::isNumber(const std::string &s) {/*
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
*/
    return true;  
}

bool Utils::isDouble(const std::string &s) {
/*    return !s.empty() && std::find_if(s.begin(),
                s.end(), [](unsigned char c) { return !std::isdigit(c) && c != '.'; }) == s.end();
*/
    return true;
}

std::string Utils::getCurrentDateTime() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t time = std::chrono::system_clock::to_time_t(now);
    const std::tm* current_time = std::localtime(&time);

    char buffer[20]; // Buffer to store the formatted date and time

    // Format the date and time as "yyyy-MM-dd HH:mm:ss"
    std::strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", current_time);

    return buffer;
}

bool Utils::doesValueExist(const std::vector<int> &vec, const int valueToFind) {
    const auto it = std::find(vec.begin(), vec.end(), valueToFind);

    return it != vec.end();
}
