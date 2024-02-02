#ifndef VECTOR_H_
#define VECTOR_H_

#include "generics.h"
#include "linkedlist.h"

// #define DEFAULT_VECTOR_CAPACITY 1024

// #define VectorFullError -1
#define VectorPushBackFailure -2
#define VectorTmpVarCreateFailure -3

/* 一个使用链表实现的向量
 *
 * 运行时可能会比较慢, 相较于用动态数组实现的向量
 * 没有显式设定容量上限, 应该是 int 类型的上限?
**/
struct Vector_ {
    Link* _linkedlist_head; // 数据存放
    int size;               // 当前大小
    GenericsType elem_type; // 内容物类型
    // int capacity;
};

typedef struct Vector_ Vector;

/*
创建一个长度为 0 的新向量
返回指向它的指针
*/
Vector* create_vector(GenericsType elem_type);

/*
销毁一个向量
*/
void destroy_vector(Vector* vec);

/*
将一个新元素添加到向量末尾
返回操作后向量的长度
返回值为负数时表示出错
*/
int push_back_vector(Vector* vec, void* new_item_data);

/*
打印一个向量
`sep`是分隔符, 传入空字符表示不分隔
`end`是结束符, 同上
*/
void print_vector(const Vector* vec, char sep, char end);

/*
取出向量的第`index+1`个元素
后方的元素向前补位
*/
GenericsVar* pop_item_vector(Vector* vec, int index);

/*
取出向量的最后一个元素

Based on `pop_item_vector`
*/
GenericsVar* pop_back_vector(Vector* vec);

/*
获得向量的第`index+1`个元素
`is_copy`表示返回的指针是否为拷贝
*/
GenericsVar* at_vector(const Vector* vec, int index, bool is_copy);

/*
为向量的第`index+1`个元素指定一个新值
*/
void set_vector(Vector* vec, int index, void* new_data);

/*
批量添加新元素到向量末尾
返回操作后的向量长度

Based on `push_back_vector`
*/
int push_back_batch_vector(Vector* vec, void* new_item_data, int count);

/*
删除向量的第`index+1`个元素
后方的元素向前补位

Based on `pop_item_vector` 
*/
void del_item_vector(Vector* vec, int index);

/*获取向量的当前长度*/
int vector_size(const Vector* vec);

/*
获取向量的内容物类型
返回一个`GenericsType`
*/
GenericsType vector_type(const Vector* vec);

/*
获取向量的内部链表的头指针
注意, 随意修改可能会导致 Vector 不正常工作
还是建议只使用提供的函数进行操作……
*/
Link* vector_inner_linklist(const Vector* vec);

#endif