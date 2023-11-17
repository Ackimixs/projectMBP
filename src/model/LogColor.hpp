#pragma once

#include <vector>
#include <ostream>
#include <sstream>

namespace LogColor {
    enum Code {
        RESET = 0,
        BOLD = 1,
        UNDERLINE = 4,
        BLINK = 5,
        REVERSE = 7,
        CONCEALED = 8,
    };

    enum ForegroundColor {
        FG_DEFAULT = 39,
        FG_BLACK = 30,
        FG_RED = 31,
        FG_GREEN = 32,
        FG_YELLOW = 33,
        FG_BLUE = 34,
        FG_MAGENTA = 35,
        FG_CYAN = 36,
        FG_WHITE = 37,
        FG_BRIGHT_BLACK = 90,
        FG_BRIGHT_RED = 91,
        FG_BRIGHT_GREEN = 92,
        FG_BRIGHT_YELLOW = 93,
        FG_BRIGHT_BLUE = 94,
        FG_BRIGHT_MAGENTA = 95,
        FG_BRIGHT_CYAN = 96,
        FG_BRIGHT_WHITE = 97,
    };

    enum BackgroundColor {
        BG_DEFAULT = 49,
        BG_BLACK = 40,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_YELLOW = 43,
        BG_BLUE = 44,
        BG_MAGENTA = 45,
        BG_CYAN = 46,
        BG_WHITE = 47,
        BG_BRIGHT_BLACK = 100,
        BG_BRIGHT_RED = 101,
        BG_BRIGHT_GREEN = 102,
        BG_BRIGHT_YELLOW = 103,
        BG_BRIGHT_BLUE = 104,
        BG_BRIGHT_MAGENTA = 105,
        BG_BRIGHT_CYAN = 106,
        BG_BRIGHT_WHITE = 107,
    };

    class Modifier {
        std::vector<Code> codes;

    public:
        Modifier() {}

        Modifier& operator<<(Code code) {
            codes.push_back(code);
            return *this;
        }

        Modifier& operator<<(ForegroundColor color) {
            codes.push_back(static_cast<Code>(color));
            return *this;
        }

        Modifier& operator<<(BackgroundColor color) {
            codes.push_back(static_cast<Code>(color));
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, const Modifier& mod) {
            os << "\033[";
            const size_t size = mod.codes.size();
            for (size_t i = 0; i < size; ++i) {
                os << mod.codes.at(i);
                if (i < size - 1)
                    os << ';';
            }
            os << 'm';
            return os;
        }
    };

    // Overload + operator to combine strings with color modifiers
    std::string operator+(const std::string& str, const Modifier& mod);

    std::string operator+(const Modifier& mod, const std::string& str);
    // Define convenient global modifiers
    const Modifier reset = Modifier() << RESET;
    const Modifier bold = Modifier() << BOLD;
    const Modifier underline = Modifier() << UNDERLINE;
    const Modifier blink = Modifier() << BLINK;
    const Modifier reverse = Modifier() << REVERSE;
    const Modifier concealed = Modifier() << CONCEALED;

    // Define convenient global foreground colors
    const Modifier fgDefault = Modifier() << FG_DEFAULT;
    const Modifier fgBlack = Modifier() << FG_BLACK;
    const Modifier fgRed = Modifier() << FG_RED;
    const Modifier fgGreen = Modifier() << FG_GREEN;
    const Modifier fgYellow = Modifier() << FG_YELLOW;
    const Modifier fgBlue = Modifier() << FG_BLUE;
    const Modifier fgMagenta = Modifier() << FG_MAGENTA;
    const Modifier fgCyan = Modifier() << FG_CYAN;
    const Modifier fgWhite = Modifier() << FG_WHITE;
    const Modifier fgBrightBlack = Modifier() << FG_BRIGHT_BLACK;
    const Modifier fgBrightRed = Modifier() << FG_BRIGHT_RED;
    const Modifier fgBrightGreen = Modifier() << FG_BRIGHT_GREEN;
    const Modifier fgBrightYellow = Modifier() << FG_BRIGHT_YELLOW;
    const Modifier fgBrightBlue = Modifier() << FG_BRIGHT_BLUE;
    const Modifier fgBrightMagenta = Modifier() << FG_BRIGHT_MAGENTA;
    const Modifier fgBrightCyan = Modifier() << FG_BRIGHT_CYAN;
    const Modifier fgBrightWhite = Modifier() << FG_BRIGHT_WHITE;

    // Define convenient global background colors
    const Modifier bgDefault = Modifier() << BG_DEFAULT;
    const Modifier bgBlack = Modifier() << BG_BLACK;
    const Modifier bgRed = Modifier() << BG_RED;
    const Modifier bgGreen = Modifier() << BG_GREEN;
    const Modifier bgYellow = Modifier() << BG_YELLOW;
    const Modifier bgBlue = Modifier() << BG_BLUE;
    const Modifier bgMagenta = Modifier() << BG_MAGENTA;
    const Modifier bgCyan = Modifier() << BG_CYAN;
    const Modifier bgWhite = Modifier() << BG_WHITE;
    const Modifier bgBrightBlack = Modifier() << BG_BRIGHT_BLACK;
    const Modifier bgBrightRed = Modifier() << BG_BRIGHT_RED;
    const Modifier bgBrightGreen = Modifier() << BG_BRIGHT_GREEN;
    const Modifier bgBrightYellow = Modifier() << BG_BRIGHT_YELLOW;
    const Modifier bgBrightBlue = Modifier() << BG_BRIGHT_BLUE;
    const Modifier bgBrightMagenta = Modifier() << BG_BRIGHT_MAGENTA;
    const Modifier bgBrightCyan = Modifier() << BG_BRIGHT_CYAN;
    const Modifier bgBrightWhite = Modifier() << BG_BRIGHT_WHITE;
}
