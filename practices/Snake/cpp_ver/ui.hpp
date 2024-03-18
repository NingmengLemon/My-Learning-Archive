#ifndef _UI_HPP_
#define _UI_HPP_

#include "./Eseq/eseq.hpp"
#include "./game.hpp"
#include "./Kbinput/kbinput.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

void printStatus(Game &game, int delay);
void printTips(Game &game);
void flushCin(void);
void printMenu_en(void);
void flushKb(KbInput &keyboard);
void menuLoop(KbInput &keyboard, Game &game);
void printConfig(Game &game);
std::string boolToString(bool b);
int nextValue(int current, std::vector<int> options);
#endif