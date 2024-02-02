#include "vector.h"

Vector* create_vector(size_t size, size_t capacity, size_t elem_size, void* elem_data) {
    if(size>capacity) return NULL;
    if(capacity==0) capacity = DEFAULT_VECTOR_CAPACITY;

    Vector* vec = (Vector*)malloc(sizeof(Vector));
    if(vec==NULL) return NULL;

    vec->data = (void**)malloc(capacity*sizeof(void*));
    if(vec->data==NULL){
        free(vec);
        return NULL;
    }

    for (size_t i = 0; i < capacity; i++){
        vec->data[i] = (void*)malloc(elem_size);
        if(i<size && vec->data[i]!=NULL){
            memcpy(vec->data[i], elem_data, elem_size);
        }
    }

    vec->elem_size = elem_size;
    vec->size = size;
    vec->capacity = capacity;

    return vec;
}

void destroy_vector(Vector* vec){
    for (size_t i = 0; i < vec->capacity; i++){
        free(vec->data[i]);
    }
    free(vec->data);
    free(vec);
    vec = NULL;
}

Vector* resize_vector(Vector* vec, size_t new_capacity){
    if(new_capacity == vec->capacity || new_capacity == 0){
        // NO NEED to do anything...
    }
    else if (new_capacity < vec->capacity){
        /*
        需求的容量上限 < 原先的容量上限
        需要截断数组 data
        */
        for (size_t i = new_capacity; i < vec->capacity; i++){
            free(vec->data[i]);                
        }
        vec->data = realloc(vec->data, new_capacity*sizeof(void*));
        vec->capacity = new_capacity;
        vec->size = new_capacity;
    }
    else{
        /*
        需求的容量上限 > 原先的容量上限
        需要扩大数组 data
        */
        vec->data = realloc(vec->data, new_capacity*sizeof(void*));
        for (size_t i = vec->capacity; i < new_capacity; i++){
            vec->data[i] = (void*)malloc(vec->elem_size);
        }
        vec->capacity = new_capacity;
    }
    return vec;
}

void* pop_back_vector(Vector* vec){
    if(vec->size==0) return NULL;
    void* res = (void*)malloc(vec->elem_size);
    memcpy(res, vec->data[vec->size-1], vec->elem_size);
    vec->size --;
    return res;
}

void del_back_vector(Vector* vec){
    if(vec->size==0) return;
    else vec->size --;
}

void* at_vector(const Vector* vec, size_t index){
    if(index+1 > vec->size) return NULL;
    void* res = (void*)malloc(vec->elem_size);
    memcpy(res, vec->data[index], vec->elem_size);
    return res;
}

void set_vector(Vector* vec, size_t index, void* new_data){
    if(index+1 > vec->size) return;
    memcpy(vec->data[index], new_data, vec->elem_size);
}

void push_back_vector(Vector* vec, void* new_data){
    if(vec->size>=vec->capacity) return;
    memcpy(vec->data[vec->size], new_data, vec->elem_size);
    vec->size ++;
}

void** vector_data(const Vector* vec){
    return vec->data;
}

size_t vector_size(const Vector* vec){
    return vec->size;
}

size_t vector_capacity(const Vector* vec){
    return vec->capacity;
}

size_t vector_elemsize(const Vector* vec){
    return vec->elem_size;
}