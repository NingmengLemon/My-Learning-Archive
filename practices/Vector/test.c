#include "vector.h"
#include <assert.h>

int main() {
    // 创建一个初始容量为 10，初始大小为 5 的 Vector，元素类型为 int
    int initial_data = 5;
    Vector* vec = create_vector(5, 10, sizeof(int), &initial_data);
    assert(vec != NULL);

    // 打印 Vector 的初始状态
    printf("Initial vector: ");
    print_vector(vec, int, "%d", ' ', '\n');

    // 向 Vector 中添加一些元素
    for (int i = 0; i < 10; i++) {
        int* new_data = malloc(sizeof(int));
        *new_data = i;
        push_back_vector(vec, new_data);
    }

    // 打印添加元素后的 Vector
    printf("After adding elements: ");
    print_vector(vec, int, "%d", ' ', '\n');

    // 删除一些元素
    for (int i = 0; i < 5; i++) {
        del_back_vector(vec);
    }

    // 打印删除元素后的 Vector
    printf("After deleting elements: ");
    print_vector(vec, int, "%d", ' ', '\n');

    // 销毁 Vector
    destroy_vector(vec);

    return 0;
}
