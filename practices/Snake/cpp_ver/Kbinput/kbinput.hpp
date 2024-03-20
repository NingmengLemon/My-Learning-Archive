#ifndef _KBINPUT_H_
#define _KBINPUT_H_

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>

#else

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#endif

class KbInput {
  public:
    KbInput(void);
    ~KbInput(void);
    bool keyPressed(void);
    char getKey(void);

  private:
    void init(void);
    void reset(void);
};

#endif