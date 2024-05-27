
#include "objects.h"

/*
将生成的订单号保存到 order_id 中
同时额外返回一个生成时时间戳 (秒级)
*/
time_t generate_order_id(char *order_id) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestr[14 + 1];
    char random_suffix[4 + 1];
    strftime(timestr, sizeof(timestr), "%Y%m%d%H%M%S", tm_info);
    generate_random_string(random_suffix, 4);
    // 格式化时间戳
    // 生成订单编号
    strcpy(order_id, "#");
    strcat(order_id, timestr);
    strcat(order_id, "-");
    strcat(order_id, random_suffix);
    // snprintf(order_id, ORDER_ID_LENGTH, "%s%s", timestr, random_suffix);
    // order_id[ORDER_ID_LENGTH] = '\0';
    return now;
}
