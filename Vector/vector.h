#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEFAULT_VECTOR_CAPACITY 1024

/*
便于导出`void*`的值的宏函数
`ptr` 为`void*`类型指针
`type`为将要导出为的类型
*/
#define extrcVoidptr(ptr, type) (*((type*)(ptr)))

/*
便于生成字面量的指针的宏函数
`type`为这个字面量的类型
*/
#define literalPtr(var, type) (&(type){var})

/*
用于打印 Vector 的宏函数
`vec`是将要被打印的 Vector
`elem_type`是 Vector 的内容物的类型 eg.`int`
`specifier`是每个数据的格式化标识符 eg.`"%d"`
`sep`是每个元素间的间隔字符, 传入空字符则没有间隔 eg.`-`
`end`是打印完成后的结束字符, 传入空字符则表示没有结束符 eg,`\n`
*/
#define print_vector(vec, elem_type, specifier, sep, end) { \
    for(size_t i=0; i<vec->size; i++){ \
        if(i!=0 && sep) putchar(sep); \
        printf(specifier, extrcVoidptr(vec->data[i], elem_type)); \
    } \
    if(end) putchar(end); \
}

/*
一个泛型的 Vector
使用者需要记住自己存进去的是何种数据,
来对得到的`void*`指针进行转换
但 Vector 只需要知道单个数据的大小
~~蒸馍, 你不扶器?~~

注意`size`当前有效长度 与 `capacity`容量上限 的区别
>=size 且 <capacity 的索引对应的值可能为垃圾值
*/
typedef struct Vector {
    void** data;
    size_t size;
    size_t capacity;
    size_t elem_size;
} Vector;

/*
创建一个 Vector, 返回指向它的指针
`capacity`是容量上限
`size`是要进行初始化的长度, 不得超过`capacity`
`elem_size`是单个数据的大小
`elem_data`是用于初始化的值的指针
创建失败返回`NULL`
*/
Vector* create_vector(size_t size, size_t capacity, size_t elem_size, void* elem_data);

/*
销毁一个 Vector
*/
void destroy_vector(Vector* vec);

/*
调整 Vector 的容量上限
若新的容量上限<当前有效长度, 超出的部分将会被截断
*/
Vector* resize_vector(Vector* vec, size_t new_capacity);

/*
取出 Vector 末尾的一个元素
返回一个新分配的`void*`指针, 注意用完销毁
*/
void* pop_back_vector(Vector* vec);

/*
删除 Vector 末尾的一个元素
*/
void del_back_vector(Vector* vec);

/*
获得 Vector 的第`index+1`个元素
返回一个新分配的`void*`指针, 注意用完销毁
*/
void* at_vector(const Vector* vec, size_t index);

/*
为 Vector 的第`index+1`个元素赋一个新值
传入的`index`必须在 Vector 的有效长度内
*/
void set_vector(Vector* vec, size_t index, void* new_data);

/*
在 Vector 的末尾添加一个元素
*/
void push_back_vector(Vector* vec, void* new_data);

/*
获取 Vector 的当前有效长度
*/
size_t vector_size(const Vector* vec);

/*
获取 Vector 的容量上限
*/
size_t vector_capacity(const Vector* vec);

/*
获取 Vector 的单个元素大小
*/
size_t vector_elemsize(const Vector* vec);

/*
获取 Vector 的内部的动态数组的指针
随意修改会影响到 Vector 的正常工作
*/
void** vector_data(const Vector* vec);

#endif