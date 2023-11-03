#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "generics.h"

// 一些状态码的定义
#define ElemNotFoundError -1
#define NodeCreationFailure -2
#define HeadNodeDeletionNotAllowed -3
#define MinusIndexNotSupported -4
// 成功都是 0
#define ElemFoundSucc 0
#define NodeInsertSucc 0
#define NodePopSucc 0

/*
实现了一个泛型的链表
但是这个链表实现其实有点……问题?
因为它以头节点为索引 0 始计, 而头节点不存数据……
首元节点的索引就是 1 了, 但好在基于此构建的 Vector 的索引定义是正常的ww
*/

struct Node_ {
    /* 你说得对, 
     * 但是这也是个指针, 这个指针指向的东西才是真正的`GenericsVar`
     * 但是`GenericsVar`里面还有个指针, 创建的时候由`create_gvar`进行分配
     * 但是这也就是说,`Gvar`的创建与销毁都必须经过`generics.h`中的函数们的手
     * tmd, 你搞这么多指针干什么嘛, 傻逼
    **/
    GenericsVar* value;
    // 指向下一个 node 的指针
    struct Node_* next;
};

typedef struct Node_ Node;
typedef Node* Link;

/*
创建一个链表, 返回它的头指针.
头节点存储的值为`NULL`
*/
Link* create_linklist(int length, GenericsType default_type);

/*
返回节点的值的(副本)指针
是否是副本取决于参数中的`is_copy`
获取失败就是`NULL`
传入链表的头指针 和`index`
以头节点的索引为`0`始计

~~当不是副本时, 理论上就可以通过修改返回的指针来修改节点的值~~
*/
GenericsVar* get_item_linklist(const Link* head, int index, bool is_copy);

/*
返回函数的执行状态
将 新节点(值为`new_node_value`(的拷贝)) 插入索引为`index`的节点**之后**
是否为拷贝取决于参数中的`is_copy`
以头节点的索引为`0`始计
*/
int insert_item_linklist(Link* head, int index, GenericsVar* new_node_value, bool is_copy);

/*
返回被pop的节点的值的指针(不是拷贝)
若失败则返回`NULL`
删除链表的 index 处的节点
以头节点的索引为 0
但头节点不允许被删除
*/
GenericsVar* pop_item_linklist(Link* head, int index);

/*
删除整个链表
*/
void destroy_linklist(Link* head);

/*
返回是否操作成功
修改一个节点的值
index 以头节点为 0 始计
请确保新的值的类型与节点的值匹配
Based on `get_item_linklist`
*/
bool modify_value_linklist(Link* head, int index, void* new_data);

#endif