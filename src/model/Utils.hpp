#pragma once

#include <string>
#include <chrono>
#include <vector>
#include <algorithm>

namespace Utils {
    bool isNumber(const std::string& s);

    bool isDouble(const std::string& s);

    std::string getCurrentDateTime();

    bool doesValueExist(const std::vector<int>& vec, int valueToFind);
}
