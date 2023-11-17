#include "LogColor.hpp"

std::string LogColor::operator+(const LogColor::Modifier &mod, const std::string &str) {
    std::stringstream ss;
    ss << mod << str << mod;
    return ss.str();
}

std::string LogColor::operator+(const std::string &str, const LogColor::Modifier &mod) {
    std::stringstream ss;
    ss << str << mod << mod;
    return ss.str();
}