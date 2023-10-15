#ifndef _GAME_H
#define _GAME_H

#ifndef _MATRIX_H
#include "matrix.h"
#endif

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

#define UP_UPPER 'W'
#define DOWN_UPPER 'S'
#define LEFT_UPPER 'A'
#define RIGHT_UPPER 'D'

bool merge(Matrix*, char);

void merge_single(int*, int);

bool summon_new_num(Matrix*, int);

void print_stage(Matrix);

void get_empty_block_randomly(Matrix, int*, int*);

int get_max_block_width(Matrix);

int get_num_width(int);

void multi_print(char, int);

bool check_if_end(Matrix);

bool check_if_any_effect(Matrix, char);

bool check_if_target_reached(Matrix, int);

#endif
