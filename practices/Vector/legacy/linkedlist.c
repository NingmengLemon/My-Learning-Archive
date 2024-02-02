#include "linkedlist.h"

Link* create_linklist(int length, GenericsType default_type){
    // 芝士头指针
    Link *head = (Link*)malloc(sizeof(Link)); 
    if(head==NULL){
        return NULL;
    }
    // 芝士头节点
    *head = (Link)malloc(sizeof(Node));
    if(*head==NULL){
        free(head);
        return NULL;
    }
    // 芝士头节点的值, 直接设定为 NULL 方便标识
    (*head) -> value = NULL;
    (*head) -> next = NULL;
    // 进行一个一个节点的创
    Link p = NULL;
    Link last_p = (*head);
    for(int i=0;i<length;i++){
        // 没有做分配失败时的处理
        p = (Link)malloc(sizeof(Node));
        p -> next = NULL;
        // 没有做创建失败时的处理
        p -> value = create_gvar(default_type, NULL);
        last_p -> next = p;
        last_p = p;
    }
    return head;
}

GenericsVar* get_item_linklist(const Link* head, int index, bool is_copy){
    Link p = *head; // 芝士头节点
    int i = 0;
    while(p!=NULL && i<index){
        p = p->next;
        i ++;
    }
    if(p==NULL){
        return NULL;
    }

    if(is_copy){
        return copy_gvar(p->value);
    }
    else{
        return p->value;
    }
}

int insert_item_linklist(Link* head, int index, GenericsVar* new_node_value, bool is_copy){
    Link p = *head; // 头节点
    Link tmp = NULL;
    int i = 0;
    while(p!=NULL && i<index){
        p = p->next;
        i++;
    }
    if(p==NULL){
        return ElemNotFoundError;
    }

    tmp = (Link)malloc(sizeof(Node));
    if(tmp==NULL){
        return NodeCreationFailure;
    }
    if(is_copy){
        tmp->value = copy_gvar(new_node_value);
    }
    else{
        tmp->value = new_node_value;
    }

    tmp->next = p->next;
    p->next = tmp;
    return NodeInsertSucc;
}

GenericsVar* pop_item_linklist(Link* head, int index){
    if(index==0) return NULL; // 头节点不允许删除
    else if(index<0) return NULL; // 索引不能为负
    // 开始正常的流程
    GenericsVar* value_popped = NULL;
    Link parent = *head;
    Link child = parent->next;
    for(int i=1; parent!=NULL && child!=NULL && i<index; i++){
        parent = child;
        child = child->next;
    }
    if(parent==NULL || child==NULL){
        return NULL;
    }

    parent->next = child->next;  // 断开父节点链接
    child->next = NULL;          // 断开子节点链接
    value_popped = child->value; // 保存节点的值(其实是指针)
    free(child); // 丢掉节点
    return value_popped;
}

void destroy_linklist(Link* head){
    if(head==NULL) return;
    Link p = (*head)->next;
    Link tmp = NULL;
    while(p!=NULL && p!=(*head)){
        tmp = p;
        p = p->next;
        destroy_gvar(tmp->value);
        free(tmp);
    }
    free(*head);
    free(head);
    return;
}

bool modify_value_linklist(Link* head, int index, void* new_data){
    GenericsVar* var = get_item_linklist(head, index, false);
    if(var==NULL){
        return false;
    }
    else{
        change_gvar(var, new_data);
        return true;
    }
}