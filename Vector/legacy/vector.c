#include "vector.h"

Vector* create_vector(GenericsType elem_type){
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    if(vec==NULL) return NULL;

    /*
    这里的 elem_type 其实可以换成任意 GenericsType, 
    因为创建的链表长度为 0 
    */
    vec->_linkedlist_head = create_linklist(0, elem_type);
    if(vec->_linkedlist_head==NULL){
        free(vec);
        return NULL;
    }
    vec->size = 0;
    vec->elem_type = elem_type;

    return vec;
}

void destroy_vector(Vector* vec){
    destroy_linklist(vec->_linkedlist_head);
    free(vec);
    vec = NULL;
}

int push_back_vector(Vector* vec, void* new_item_data){
    int index = vec->size;

    GenericsVar* var = create_gvar(vec->elem_type, new_item_data);
    if(var==NULL){
        return VectorPushBackFailure;
    }
    insert_item_linklist(vec->_linkedlist_head, index, var, false);
    vec->size += 1;
    return vec->size;
}

void print_vector(const Vector* vec, char sep, char end){
    Link p = *(vec->_linkedlist_head); // 头节点
    p = p->next; // 首元节点
    GenericsVar* var = NULL;
    int i = 1;
    while(p!=NULL) {
        var = p->value;
        if(i!=1 && sep!=0){ // 特殊处理第一个元素
            putchar(sep);
        }
        print_gvar(var);

        p = p->next;
        i ++;
    }
    if(end!=0) putchar(end);
}

GenericsVar* pop_item_vector(Vector* vec, int index){
    if(index<-1) return NULL;
    if(index==-1) index = vec->size-1;
    index += 1;

    GenericsVar* popped_var = pop_item_linklist(vec->_linkedlist_head, index);
    vec->size -= 1;
    return popped_var;
}

GenericsVar* pop_back_vector(Vector* vec){
    return pop_item_vector(vec, -1);
}

GenericsVar* at_vector(const Vector* vec, int index, bool is_copy){
    if(index<-1) return NULL; // 处理掉不合法的索引
    if(index==-1) index = vec->size-1; // 将 -1 索引重定向为 最后一个元素的索引
    index += 1; // 注意, 这里的索引定义与链表的不同, 这里直接从 0 始计
    // 将 Vector 索引转换为 linkedlist 索引

    return get_item_linklist(vec->_linkedlist_head, index, is_copy);
}

void set_vector(Vector* vec, int index, void* new_data){
    // 索引预处理, 同上面那个函数
    if(index<-1) return;
    if(index==-1) index = vec->size-1;
    index += 1;

    modify_value_linklist(vec->_linkedlist_head, index, new_data);
}

int push_back_batch_vector(Vector* vec, void* new_item_data, int count){
    for(int i=0;i<count;i++){
        push_back_vector(vec, new_item_data);
    }
    return vec->size;
}

void del_item_vector(Vector* vec, int index){
    GenericsVar* popped = pop_item_vector(vec, index);
    destroy_gvar(popped);
}

int vector_size(const Vector* vec){
    return vec->size;
}

GenericsType vector_type(const Vector* vec){
    return vec->elem_type;
}

Link* vector_inner_linklist(const Vector* vec){
    return vec->_linkedlist_head;
}