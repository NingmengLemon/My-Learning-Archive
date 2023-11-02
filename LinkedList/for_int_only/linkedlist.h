#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemNotFoundError -1
#define NodeCreationFailure -2
#define ElemFoundSucc 0
#define NodeInsertSucc 0
#define NodePopSucc 0

struct Node_ {
    int value;
    struct Node_* next;
};

typedef struct Node_ Node;
typedef Node* Link;

/*
创建一个链表, 返回它的头指针.
is_loop 为 true 时 使首尾相连
*/
Link* create(int length, bool is_loop);

/*
返回 函数的执行状态(有define)
res 用于返回得到的项
传入链表的头指针 和 index
以头节点的索引为 0
*/
int get_item(const Link* head, int index, int* res);

/*
返回 函数的执行状态
将 新节点(值为new_node_value) 插入 索引为 index 的节点之后
以头节点的索引为 0
*/
int insert_item(Link* head, int index, int new_node_value);

/*
返回 函数的执行状态
删除链表的 index 处的节点
以头节点的索引为 0
*/
int pop_item(Link* head, int index, int* value_popped);

/*
删除整个链表
*/
void destroy_linklist(Link* head);

#endif