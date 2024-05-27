#ifndef _ITEM_H_
#define _ITEM_H_

#include "utils.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ITEM_ID_LENGTH 20
#define ITEM_NAME_MAX_LENGTH 40
#define ITEM_DESC_MAX_LENGTH 250
#define ORDER_ID_LENGTH 20
#define CUST_NAME_MAX_LENGTH 40
#define ORDER_ITEMS_MAX_NUM 30

// 商品类型枚举
typedef enum ItemCategory {
    DRINK,
    FOOD,
    OTHER,
} ItemCategory;

// 商品结构体定义
typedef struct Item {
    // 这个 id 就没有太多要求了, 录入的时候可以尽情输入,
    // 别超限别重复 别夹半角逗号和正斜杠 就行, csv要用的
    char id[ITEM_ID_LENGTH + 1]; // +1 是为了字符串结尾的 \0
    char name[ITEM_NAME_MAX_LENGTH + 1];
    float price;
    char description[ITEM_DESC_MAX_LENGTH + 1];
    int stock_num; //
    ItemCategory category;
    bool is_deleted;
    /*
    思考之后决定只把这个当模板,
    每个 Order 里的商品清单中的每一项
    都指向加载好的全局变量Vector里存储的这东西.
    意味着每个商品只会在内存里存在一遍(上述的全局变量里),
    其他出现的每一处理论上都应该是它的商品id, 除了某些必要的拷贝.
    */
    /*
    写入文件时以这里的顺序为准
    */
} Item;

/* 注意区别商品id和订单id */

// 订单状态枚举
typedef enum OrderStatus {
    PENDING,
    PROCESSING,
    FINISHED,
    CANCELED,
    FAILED,
    DELETED,
    /*
    标记为deleted的订单不会显示, 且在保存到文件时会被忽略
    相当于在退出时被真正删除 (商品也是, 但是是独立的变量)
    嗯 像lua一样呐(唱)
    */
} OrderStatus;

typedef struct Order {
    /*
    id 以 # 字符开头
    紧跟着 14 位日期
    再一个 - 字符后接最后 4 位随机大小写字母数字混合字符串
    像是: #20240523003047-Rs2W
    总共 20 位, 额外的一位用来放 \0
    */
    char id[ORDER_ID_LENGTH + 1]; // 此处 +1 同理
    char customer_nickname[CUST_NAME_MAX_LENGTH + 1];
    time_t order_time;
    // 商品清单 (嗯)
    // 存的其实是商品编号
    // 用/分割
    char items[ORDER_ITEMS_MAX_NUM * (ITEM_ID_LENGTH + 1)];
    int item_count;
    OrderStatus status;
    // 总金额临时算就行不用记
} Order;
// 怀念面向对象编程的第1145天

time_t generate_order_id(char *orderId);

#endif