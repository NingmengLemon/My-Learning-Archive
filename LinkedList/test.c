#include "linkedlist.h"
#include <assert.h>

void test_linklist() {
    // 创建一个链表
    Link* head = create_linklist(3, INT);
    assert(head != NULL);

    // 插入元素
    int index = 1;
    GenericsVar* new_node_value = create_gvar(INT, literalPtr(10, int));
    assert(new_node_value != NULL);
    int status = insert_item_linklist(head, index, new_node_value, false);
    assert(status == NodeInsertSucc);

    // 获取并检查元素
    GenericsVar* item = get_item_linklist(head, index+1, true); // 注意，插入后元素的位置是 index+1
    assert(item != NULL);
    assert(extrcGvar(item, int) == 10);

    // 修改元素
    bool success = modify_value_linklist(head, index+1, literalPtr(20, int));
    assert(success);

    // 检查修改后的元素
    item = get_item_linklist(head, index+1, false);
    assert(item != NULL);
    assert(extrcGvar(item, int) == 20);

    // 删除元素
    GenericsVar* popped_item = pop_item_linklist(head, index+1);
    assert(popped_item != NULL);
    assert(extrcGvar(popped_item, int) == 20);
    destroy_gvar(popped_item);

    // 销毁链表
    destroy_linklist(head);
}

int main() {
    test_linklist();
    printf("All tests passed!\n");
    return 0;
}
