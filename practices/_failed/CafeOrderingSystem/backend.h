#ifndef _BACKEND_H_
#define _BACKEND_H_

#include "objects.h"
#include "utils.h"
#include "vector.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern Vector *cafe_items;
extern Vector *cafe_orders;

#define DEFAULT_ITEMS_SAVEPATH "./cafe_items.csv"
#define DEFAULT_ORDERS_SAVEPATH "./cafe_orders.csv"

void record_new_item(char *id, char *name, float price, char *desc,
                     int init_stock_num, ItemCategory cate);

void create_new_order(char *id, char *cusname, time_t otime, char *items,
                      int icount, OrderStatus status);

void load_items(char *filename);

void load_orders(char *filename);

void init_all(void);

void save_all(void);

void print_all_items(void);

void print_all_orders(void);

void save_items(char* filename);

void save_orders(char* filename);

#endif