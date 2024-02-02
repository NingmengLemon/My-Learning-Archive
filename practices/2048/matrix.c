#include <stdlib.h>
#include <stdbool.h>

#include "matrix.h"

Matrix* create_matrix(int w, int h, int fill){
    Matrix* m = (Matrix*)malloc(sizeof(Matrix));
    if(m==NULL) return NULL;

    m->w = w;
    m->h = h;
    m->var = (int**)malloc(h*sizeof(int*));
    if(m->var==NULL){
        free(m);
        return NULL;
    }

    for(int i=0;i<h;i++){
        m->var[i] = (int*)malloc(w*sizeof(int));

        if(m->var[i]==NULL){
            for(int j=0;j<i;j++){
                free(m->var[j]);
            }
            free(m);
            return NULL;
        }

        for(int j=0;j<w;j++){
            m->var[i][j] = fill;
        }
    }
    return m;
}

void destroy_matrix(Matrix* m){
    int w=m->w, h=m->h;
    for(int i=0;i<h;i++){
        free(m->var[i]);
    }
    free(m->var);
    free(m);
}

void modify_matrix(Matrix* m, int x, int y, int v){
    m->var[y][x] = v;
}

int get_matrix_item(Matrix m, int x, int y){
    return m.var[y][x];
}

int* get_matrix_line(Matrix m, int y){
    int l = m.w;
    int* res = (int*)malloc(l*sizeof(int));
    if(res==NULL) return NULL;

    for(int i=0;i<l;i++){
        res[i] = m.var[y][i];
    }
    return res;
}

int* get_matrix_column(Matrix m, int x){
    int l = m.h;
    int* res = (int*)malloc(l*sizeof(int));
    if(res==NULL) return NULL;

    for(int i=0;i<l;i++){
        res[i] = m.var[i][x];
    }
    return res;
}

void reverse_array(int* arr, int length){
    int tmp;
    for(int i=0;i<length/2;i++){
        tmp = arr[i];
        arr[i] = arr[length-1-i];
        arr[length-1-i] = tmp;
    }
}

void modify_matrix_line(Matrix* m, int* line, int y){
    int l = m->w;
    int* res = (int*)malloc(l*sizeof(int));
    for(int i=0;i<l;i++){
        m->var[y][i] = line[i];
    }
}

void modify_matrix_column(Matrix* m, int* column, int x){
    int l = m->h;
    int* res = (int*)malloc(l*sizeof(int));
    for(int i=0;i<l;i++){
        m->var[i][x] = column[i];
    }
}

bool compare_matrix(Matrix a, Matrix b){
    if(a.w!=b.w || a.h!=b.h) return false;
    for(int y=0;y<a.h;y++){
        for(int x=0;x<a.w;x++){
            if(a.var[y][x]!=b.var[y][x]) return false;
        }
    }
    return true;
}

Matrix* deep_copy_matrix(Matrix m){
    Matrix *new_m = create_matrix(m.w,m.h,0);
    if(new_m==NULL) return NULL;

    for(int y=0;y<m.h;y++){
        for(int x=0;x<m.w;x++){
            new_m->var[y][x] = m.var[y][x];
        }
    }
    return new_m;
}