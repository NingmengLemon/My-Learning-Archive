#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include "./Eseq/eseq.hpp"
#include "./KbInput/kbinput.hpp"
#include "./game.hpp"
#include "./ui.hpp"
#include <iostream>
#include <map>
#include <string>
#include <unistd.h>

void prepare(void);
void gameLoop(KbInput &keyboard, Game &game);
int main(void);
void showNotice(KbInput &keyboard);

#endif