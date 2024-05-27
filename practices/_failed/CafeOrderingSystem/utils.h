#ifndef _COFFEE_UTILS_H_
#define _COFFEE_UTILS_H_

#include "vector.h"

#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CSV_LINE_WIDTH 1024

// 嗯在gpt指导下写的跨平台获取当前位置
#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#include <windows.h>
#define GETCWD _getcwd
#define SEC_SLEEP(t) Sleep(t * 1000)
#else
#include <unistd.h>
#define GETCWD getcwd
#define SEC_SLEEP(t) sleep(t)
#endif

// 记得在 main 函数里 srand((unsigned int)time(NULL));

char generate_random_char();

void generate_random_string(char *str, int length);

Vector *read_csv(char *filename);

void init_random(void);

void write_csv(Vector *lines, char *filename);

int easy_menu(char *question, int option_count, ...);

void clear_buffer(void);

#endif