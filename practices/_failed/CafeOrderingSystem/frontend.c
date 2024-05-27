#include "frontend.h"

void clear_screen(void) { puts("\033[2J\033[H"); }

void menu_main(void) {
    if (easy_menu("111真要看吗", 2, "111", "钝角") != 1) {
        puts("虾头楠...");
        return;
    }
    while (true) {
        clear_screen();
        switch (easy_menu("欢迎回来! 今天要做些什么呢 ～(∠・ω< )⌒☆", 4,
                          "进入订单管理系统", "进入商品管理系统",
                          "进入统计系统", "退出")) {
        case 0:
            puts("未意料的选项, 请检查输入喵\n");
            SEC_SLEEP(2);
            break;
        case 1:
            menu_order_management();
            break;
        case 2:
            menu_item_management();
            break;
        case 3:
            menu_stat();
            break;
        case 4:
            puts("See you next time ヾ(￣▽￣)\n");
            return;
        }
    }
}

void menu_order_management(void) {
    while (true) {
        switch (easy_menu("订单管理系统", 5, "查看全部订单", "搜索订单", "创建订单", "完成订单", "取消订单",
                          "删除订单", "返回")) {
        case 0:
            puts("未意料的选项, 请检查输入喵\n");
            SEC_SLEEP(2);
            break;
        case 5:
            return;
        case 1:
            puts("所有订单如下: \n");
            print_all_orders();
            break;
        }
    }
}

void ui_order_search(void){}

void ui_order_creation(void){}

void ui_order_change_status(void){}

void menu_item_management(void) {}

void menu_stat(void) {}

int main(void) { menu_main(); }