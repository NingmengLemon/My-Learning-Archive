#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_VECTOR_CAPACITY 100

/*
便于导出`void*`的值的宏函数
`ptr` 为`void*`类型指针
`type`为将要导出为的类型

不要用在存入时便是指针的东西上(比如字符数组的名字), 会造成意外的解引用
*/
#define EXTRACT_VOID_PTR(ptr, type) (*((type *)(ptr)))

/*
用于修改 void* 指向的内容
*/
#define MODIFY_VOID_PTR(ptr, type, value)                                      \
    {                                                                          \
        type *typed = (type *)ptr;                                             \
        (*typed) = value;                                                      \
    }

/*
用于为还未分配空间的 void* 分配空间并赋一个初始值
*/
#define INIT_VOID_PTR(pvar, type, value)                                       \
    {                                                                          \
        pvar = (void *)malloc(sizeof(type));                                   \
        MODIFY_VOID_PTR(pvar, type, value);                                    \
    }

typedef struct {
    void *data;
    size_t size;
    size_t element_size;
    size_t capacity;
} Vector;

Vector *vector_create(size_t element_size, size_t initial_capacity);

void vector_free(Vector *v);

bool vector_resize(Vector *v, size_t new_capacity);

bool vector_shrink(Vector *v);

bool vector_push_back(Vector *v, const void *element);

void vector_pop_back(Vector *v);

void *vector_get(Vector *v, size_t index);

void vector_clear(Vector* v);

#endif