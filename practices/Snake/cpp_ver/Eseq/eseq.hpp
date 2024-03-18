#ifndef _ESEQ_H_
#define _ESEQ_H_

#include <sstream>
#include <string>

namespace eseq {
namespace cursor {

std::string MoveTo(int line = 1, int col = 1);

std::string MoveUp(int dy);

std::string MoveDown(int dy);

std::string MoveRight(int dx);

std::string MoveLeft(int dx);

std::string MoveToHome(void);

std::string MoveToFirst(void);
} // namespace cursor

namespace screen {

std::string ClearScreen(void);

std::string ClearLine(void);
} // namespace screen

namespace style {

std::string SetStyle(int text_style = -1, int fore_color = -1,
                     int back_color = -1);

std::string SetColor(int fore = -1, int back = -1);
std::string SetForeColor(int code);
std::string SetBackColor(int code);

std::string ResetStyle(void);

namespace styles {
enum styles {
    BOLD = 1,
    FAINT,
    ITALIC,
    UNDERLINE,
    SLOW_BLINK,
    RAPID_BLINK,
    REVERSE,
    HIDE
};
} // namespace styles

namespace colors {
namespace fore {
enum fore {
    BLACK = 30,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    GRAY = 90,
    BRIGHT_RED,
    BRIGHT_GREEN,
    BRIGHT_BLUE,
    BRIGHT_MAGENTA,
    BRIGHT_CYAN,
    BRIGHT_WHITE
};
} // namespace fore

namespace back {
enum back {
    BLACK = 40,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    GRAY = 100,
    BRIGHT_RED,
    BRIGHT_GREEN,
    BRIGHT_BLUE,
    BRIGHT_MAGENTA,
    BRIGHT_CYAN,
    BRIGHT_WHITE
};
} // namespace back

} // namespace colors

} // namespace style

} // namespace eseq

#endif