#include "linkedlist.h"

Link* create(int length, bool is_loop){
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
    (*head) -> value = length;
    (*head) -> next = NULL;
    // 进行一个一个节点的创
    Link p = NULL;
    Link last_p = (*head);
    for(int i=0;i<length;i++){
        p = (Link)malloc(sizeof(Node));
        // 这里malloc失败了要怎么搞呢(沉思)
        p -> next = NULL;
        p -> value = i+1;
        last_p -> next = p;
        last_p = p;
    }
    // 根据需要进行一个一个连接
    if(is_loop){
        p->next = *head;
    }
    return head;
}

int get_item(const Link* head, int index, int* res){
    Link p = *head; // 芝士头节点
    int i = 1;
    while(p!=NULL && i<index){
        p = p->next;
        i ++;
    }
    if(p==NULL){
        return ElemNotFoundError;
    }
    *res = p->value;
    return ElemFoundSucc;
}

int insert_item(Link* head, int index, int new_node_value){
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
    tmp->value = new_node_value;

    tmp->next = p->next;
    p->next = tmp;
    (*head)->value ++;
    return NodeInsertSucc;
}

int pop_item(Link* head, int index, int* value_popped){
    Link parent = *head; // 芝士头节点, 不允许删除
    Link child = parent->next;
    for(int i=1; parent!=NULL && child!=NULL && i<index; i++){
        parent = child;
        child = child->next;
    }
    if(parent==NULL || child==NULL){
        return ElemNotFoundError;
    }

    parent->next = child->next;
    child->next = NULL;
    if(value_popped!=NULL){
        *value_popped = child->value;
    }
    free(child);
    (*head)->value --;
    return NodePopSucc;
}

void destroy_linklist(Link* head){
    Link p = (*head)->next;
    Link tmp = NULL;
    while(p!=NULL && p!=(*head)){
        tmp = p;
        p = p->next;
        free(tmp);
    }
    free(*head);
    free(head);
    head = NULL;
    return;
}