// kbinput.cpp
#include "kbinput.hpp"

#if defined(_WIN32) || defined(_WIN64)

KbInput::KbInput() {}

KbInput::~KbInput() {}

bool KbInput::keyPressed() { return _kbhit() != 0; }

char KbInput::getKey() { return _getch(); }

#else

KbInput::KbInput() { init(); }

KbInput::~KbInput() { reset(); }

void KbInput::init() {
    termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ICANON & ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
}

void KbInput::reset() {
    termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

bool KbInput::keyPressed() {
    int bytesWaiting;
    ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
    return bytesWaiting > 0;
}

char KbInput::getKey() {
    char ch;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}

#endif
