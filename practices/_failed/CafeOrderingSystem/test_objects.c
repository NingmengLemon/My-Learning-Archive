#include "objects.h"


/// @brief 用于单元测试的临时主函数
// /*
int main(void) {
    init_random();
    char *orderid = (char *)malloc(21 * sizeof(char));
    char *randomstr = (char *)malloc(21 * sizeof(char));

    generate_order_id(orderid);
    printf("Generate new order id: %s\n", orderid);

    generate_random_string(randomstr, 20);
    randomstr[20] = '\0';
    printf("Generate new random str: %s\n", randomstr);

    free(orderid);
    return 0;
}
// */