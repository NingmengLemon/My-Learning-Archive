#ifndef GENERICS_H_
#define GENERICS_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define UNDEFINED_GTYPE_SIZE 0

#define extrcGvar(gvar, type) (*((type*)(gvar->data)))
#define literalPtr(var, type) (&(type){var})

enum GenericsType_ {
    CHAR, SHORT, INT, LONG, LONG_LONG, 
    FLOAT, DOUBLE, LONG_DOUBLE,
    BOOL,
    UNSIGNED_CHAR, UNSIGNED_SHORT, UNSIGNED_INT, UNSIGNED_LONG, UNSIGNED_LONG_LONG
};

typedef enum GenericsType_ GenericsType;

extern char GenericsType_specifiers[][5];

struct GenericsVar_ {
    void* data;
    GenericsType type;
};

typedef struct GenericsVar_ GenericsVar;

/*
将 GenericsType 转换为对应类型的大小
*/
size_t _gtype_to_size(GenericsType type);

/*
创建一个泛型变量
如果 data 字段为空指针则不初始化值
如果创建失败则返回空指针
*/
GenericsVar* create_gvar(GenericsType type, void* data);

/*
销毁一个泛型变量
*/
void destroy_gvar(GenericsVar* var);

/*
改变一个泛型变量的类型
注意这会使原来的值变为未初始化的状态
返回是否操作成功
*/
bool change_gtype(GenericsVar* var, GenericsType new_type);

/*
改变一个泛型变量的内容
请确保二者的类型是相同的
Tip: `&(int){n}` 更简便哦 (n 为一个字面量)
*/
void change_gvar(GenericsVar* var, void* new_data);

#endif