#pragma once

#include "LogColor.hpp"
#include "Utils.hpp"
#include "Constants.hpp"

#include <iostream>
#include <iomanip>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger {
    static LogLevel logLevel;

    static void log(const LogLevel level, const std::string& message, const std::string& context) {
        if (level >= logLevel) {
            std::cout << LogColor::bgBlack << LogColor::fgWhite << Utils::getCurrentDateTime() << LogColor::reset << " ";
            std::cout << LogColor::fgWhite << context << LogColor::reset << " ";

            switch (level) {
                case LogLevel::DEBUG:
                    std::cout << LogColor::fgBlue;
                    break;
                case LogLevel::INFO:
                    std::cout << LogColor::fgGreen;
                    break;
                case LogLevel::WARNING:
                    std::cout << LogColor::fgYellow;
                    break;
                case LogLevel::ERROR:
                    std::cout << LogColor::fgRed;
                    break;
                case LogLevel::CRITICAL:
                    std::cout << LogColor::fgRed << LogColor::bold;
                    break;
            }

            std::cout << std::setw(60 - (static_cast<int>(context.size()) - static_cast<int>(enumToString(level).size()))) << enumToString(level) << LogColor::reset << " ";

            std::cout << message << std::endl;
        }
    }

    static std::string enumToString(const LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG:
                return "DEBUG";
            case LogLevel::INFO:
                return "INFO";
            case LogLevel::WARNING:
                return "WARNING";
            case LogLevel::ERROR:
                return "ERROR";
            case LogLevel::CRITICAL:
                return "CRITICAL";
            default:
                return "UNKNOWN";
        }
    }

public:
    static void setLogLevel(const LogLevel level) {
        logLevel = level;
    }

    static void debug(const std::string &message, const std::string& context) {
        log(LogLevel::DEBUG, message, context);
    }

    static void info(const std::string &message, const std::string& context) {
        log(LogLevel::INFO, message, context);
    }

    static void warning(const std::string &message, const std::string& context) {
        log(LogLevel::WARNING, message, context);
    }

    static void error(const std::string &message, const std::string& context) {
        log(LogLevel::ERROR, message, context);
    }

    static void critical(const std::string &message, const std::string& context) {
        log(LogLevel::CRITICAL, message, context);
    }
};
