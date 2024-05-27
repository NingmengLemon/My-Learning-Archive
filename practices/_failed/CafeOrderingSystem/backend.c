#include "backend.h"

Vector *cafe_items = NULL;
Vector *cafe_orders = NULL;

/*
录入新商品的接口, 也被用于从文件加载
*/
void record_new_item(char *id, char *name, float price, char *desc,
                     int init_stock_num, ItemCategory cate) {
    if (cafe_items == NULL)
        load_items(DEFAULT_ITEMS_SAVEPATH);
    Item item;
    strcpy_s(item.id, sizeof(item.id), id);
    strcpy_s(item.name, sizeof(item.name), name);
    item.price = price;
    strcpy_s(item.description, sizeof(item.description), desc);
    item.stock_num = init_stock_num;
    item.category = cate;
    item.is_deleted = false;

    vector_push_back(cafe_items, &item);
}

/*
创建新订单的接口, 也被用于从文件加载
*/
void create_new_order(char *id, char *cusname, time_t otime, char *items,
                      int icount, OrderStatus status) {
    if (cafe_orders == NULL)
        load_items(DEFAULT_ITEMS_SAVEPATH);
    Order order;
    strcpy_s(order.id, sizeof(order.id), id);
    strcpy_s(order.customer_nickname, sizeof(order.customer_nickname), cusname);
    order.order_time = otime;
    strcpy_s(order.items, sizeof(order.items), items);
    order.status = status;

    vector_push_back(cafe_orders, &order);
}

/*
各种初始化的代码都装在这里
启动时调用
*/
void init_all(void) {
    init_random();
    load_items(DEFAULT_ITEMS_SAVEPATH);
    load_orders(DEFAULT_ORDERS_SAVEPATH);
    atexit(save_all);
}

void load_items(char *filename) {
    if (cafe_items == NULL) {
        cafe_items = vector_create(sizeof(Item), 10);
    } else {
        vector_clear(cafe_items);
    }
    Vector *temp = read_csv(filename);
    if (temp == NULL) {
        printf("No items loaded.\n");
        return;
    }
    char line[MAX_CSV_LINE_WIDTH];
    // 索引从 1 开始是为了跳过表头
    // 其实按理说应该做键值对匹配的, 怎么秽蚀呢C语言你说说
    for (size_t i = 1; i < temp->size; i++) {
        strcpy_s(line, MAX_CSV_LINE_WIDTH * sizeof(char),
                 (char *)vector_get(temp, i));
        // printf("%s\n", line);
        char id[ITEM_ID_LENGTH + 1];
        char name[ITEM_NAME_MAX_LENGTH + 1];
        float price;
        char desc[ITEM_DESC_MAX_LENGTH + 1];
        int stock;
        ItemCategory cate;

        strcpy_s(id, sizeof(id), strtok(line, ","));
        strcpy_s(name, sizeof(name), strtok(NULL, ","));
        price = atof(strtok(NULL, ","));
        strcpy_s(desc, sizeof(desc), strtok(NULL, ","));
        stock = atoi(strtok(NULL, ","));
        cate = (ItemCategory)atoi(strtok(NULL, ","));

        record_new_item(id, name, price, desc, stock, cate);
    }
    vector_free(temp);
}

void load_orders(char *filename) {
    if (cafe_orders == NULL) {
        cafe_orders = vector_create(sizeof(Item), 10);
    } else {
        vector_clear(cafe_orders);
    }
    Vector *temp = read_csv(filename);
    if (temp == NULL) {
        printf("No orders loaded.\n");
        return;
    }
    char line[MAX_CSV_LINE_WIDTH];
    // 索引从 1 开始是为了跳过表头
    for (size_t i = 1; i < temp->size; i++) {
        strcpy_s(line, MAX_CSV_LINE_WIDTH * sizeof(char),
                 (char *)vector_get(temp, i));
        // printf("%s\n", line);
        char id[ORDER_ID_LENGTH + 1];
        char cusname[CUST_NAME_MAX_LENGTH + 1];
        time_t order_time;
        char items[ORDER_ITEMS_MAX_NUM * (ITEM_ID_LENGTH + 1)];
        int item_count;
        OrderStatus status;

        strcpy_s(id, sizeof(id), strtok(line, ","));
        strcpy_s(cusname, sizeof(cusname), strtok(NULL, ","));
        order_time = atoll(strtok(NULL, ","));
        strcpy_s(items, sizeof(items), strtok(NULL, ","));
        item_count = atoi(strtok(NULL, ","));
        status = (OrderStatus)atoi(strtok(NULL, ","));

        create_new_order(id, cusname, order_time, items, item_count, status);
    }
    vector_free(temp);
}

void print_all_items(void) {
    if (cafe_items->size == 0) {
        printf("No items yet.\n");
    }
    for (size_t i = 0; i < cafe_items->size; i++) {
        Item item = EXTRACT_VOID_PTR(vector_get(cafe_items, i), Item);
        printf("商品名: %s\n商品ID: %s\n售价: %.2f￥\n描述: %s\n库存: "
               "%d件\n商品分类: %d\n\n",
               item.name, item.id, item.price, item.description, item.stock_num,
               item.category);
    }
}

void print_all_orders(void) {
    if (cafe_orders->size == 0) {
        printf("No orders yet.\n");
    }
    for (size_t i = 0; i < cafe_orders->size; i++) {
        Order order = EXTRACT_VOID_PTR(vector_get(cafe_orders, i), Order);
        printf(
            "订单ID: %s\n顾客昵称: %s\n包含商品: %s (共 %d 件)\n订单状态: %d",
            order.id, order.customer_nickname, order.items, order.item_count,
            order.status);
    }
}

void save_items(char *filename) {
    if (cafe_items == NULL)
        return;
    Vector *temp = vector_create(sizeof(char) * MAX_CSV_LINE_WIDTH, 10);
    char *head = "id,name,price,desc,stock,cate";
    vector_push_back(temp, (void *)head);
    char line[MAX_CSV_LINE_WIDTH];
    size_t count = 0;
    for (size_t i = 0; i < cafe_items->size; i++) {
        Item item = EXTRACT_VOID_PTR(vector_get(cafe_items, i), Item);
        if (item.is_deleted)
            continue;
        sprintf(line, "%s,%s,%.2f,%s,%d,%d", item.id, item.name, item.price,
                item.description, item.stock_num, item.category);
        vector_push_back(temp, (void *)line);
        count++;
    }
    write_csv(temp, filename);
    printf("%d items saved.\n", count);
}

void save_orders(char *filename) {
    if (cafe_orders == NULL)
        return;
    Vector *temp = vector_create(sizeof(char) * MAX_CSV_LINE_WIDTH, 10);
    char *head = "id,customer_name,time,items,count,status";
    vector_push_back(temp, (void *)head);
    char line[MAX_CSV_LINE_WIDTH];
    size_t count = 0;
    for (size_t i = 0; i < cafe_orders->size; i++) {
        Order order = EXTRACT_VOID_PTR(vector_get(cafe_orders, i), Order);
        if (order.status == DELETED)
            continue;
        sprintf(line, "%s,%s,%lld,%s,%d,%d", order.id, order.customer_nickname,
                order.order_time, order.items, order.item_count, order.status);
        vector_push_back(temp, (void *)line);
    }
    write_csv(temp, filename);
    printf("%d orders saved.\n", count);
}

/*
点餐接口
不带余量和商品存在性检查, 可能把余量扣成负数
items 里装的是要下单的商品id们, 用 / 分割
*/
void order_new_items(char *cusname, char *items) {
    char order_id[ORDER_ID_LENGTH + 1];
    time_t otime = generate_order_id(order_id);
    
    create_new_order(order_id, cusname, otime, items, 1, PENDING);
}

bool if_has_item(char* item_id){}

void save_all(void) {
    printf("\nSaving all...\n");
    save_items(DEFAULT_ITEMS_SAVEPATH);
    save_orders(DEFAULT_ORDERS_SAVEPATH);
}
