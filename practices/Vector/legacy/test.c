#include "vector.h"
#include "generics.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

void test(void){
    GenericsVar* tmp = NULL;
    // 整型 Vector 测试
    Vector* vec = create_vector(INT);
    // 末尾添加元素测试
    push_back_batch_vector(vec, literalPtr(114514, int), 5);
    // 修改元素测试
    set_vector(vec, 0, literalPtr(1919810, int));
    set_vector(vec, 1, literalPtr(721, int));
    print_vector(vec, ' ', '\n');
    // 取出元素测试
    tmp = pop_back_vector(vec);
    print_gvar(tmp);
    putchar('\n');
    destroy_gvar(tmp);
    // 删除元素测试
    del_item_vector(vec, 0);
    print_vector(vec, ' ', '\n');

    destroy_vector(vec);
    putchar('\n');
    // 浮点型 Vector 测试
    vec = create_vector(FLOAT);
    // 末尾添加元素测试
    push_back_batch_vector(vec, literalPtr(114.514, float), 5);
    print_vector(vec, ' ', '\n');
    // 修改元素测试
    set_vector(vec, 0, literalPtr(1919.810, float));
    set_vector(vec, 1, literalPtr(7.21, float));
    set_vector(vec, 2, literalPtr(11.4514, float));
    set_vector(vec, 3, literalPtr(1145.14, float));
    print_vector(vec, ' ', '\n');

    destroy_vector(vec);
}

int main(void){
    test();
    return EXIT_SUCCESS;
}