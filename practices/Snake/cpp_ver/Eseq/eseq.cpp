#include "eseq.hpp"

namespace eseq::cursor {
std::string MoveTo(int line, int col) {
    std::ostringstream oss;
    if (line >= 1 && col >= 1)
        oss << "\033[" << line << ";" << col << "H";
    else if (col >= 1) {
        oss << "\033[" << col << "G";
    }

    return oss.str();
}

std::string MoveUp(int dy) {
    std::ostringstream oss;
    if (dy > 0) {
        oss << "\033[" << dy << "A";
    } else if (dy < 0) {
        oss << "\033[" << 0 - dy << "B";
    }
    return oss.str();
}

std::string MoveDown(int dy) { return MoveUp(0 - dy); }

std::string MoveRight(int dx) {
    std::ostringstream oss;
    if (dx > 0) {
        oss << "\033[" << dx << "D";
    } else if (dx < 0) {
        oss << "\033[" << 0 - dx << "C";
    }
    return oss.str();
}
std::string MoveLeft(int dy) { return MoveRight(0 - dy); }

std::string MoveToFirst(void) { return "\033[G"; }
std::string MoveToHome(void) { return "\033[H"; }
} // namespace eseq::cursor

namespace eseq::screen {
std::string ClearScreen(void) { return "\033[2J"; }
std::string ClearLine(void) { return "\033[2K"; }
} // namespace eseq::screen

namespace eseq::style {
std::string SetStyle(int text_style, int fore_color, int back_color) {
    std::ostringstream oss;
    oss << "\033[";
    bool flag = false;
    if (text_style >= 1 && text_style <= 8) {
        // reset operation should be done by ResetStyle
        oss << text_style;
        flag = true;
    }
    if ((fore_color >= 30 && fore_color <= 37) ||
        (fore_color >= 90 && fore_color <= 97)) {
        if (flag)
            oss << ";";
        oss << fore_color;
        flag = true;
    }
    if ((back_color >= 40 && back_color <= 47) ||
        (back_color >= 100 && back_color <= 107)) {
        if (flag)
            oss << ";";
        oss << back_color;
        flag = true;
    }
    if (!flag) {
        return std::string("");
    }
    oss << "m";
    return oss.str();
}

std::string SetColor(int fore, int back) { return SetStyle(-1, fore, back); };

std::string SetForeColor(int code) { return SetColor(code, -1); }
std::string SetBackColor(int code) { return SetColor(-1, code); };

std::string ResetStyle(void) { return "\033[0m"; }
} // namespace eseq::style
