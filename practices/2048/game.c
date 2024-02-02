#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "game.h"

bool merge(Matrix* matrix, char orient){
    /*
    Our purpose is just to modify m, dude.
    */
    int *line = NULL;
    int *column = NULL;
    switch(orient){
        case UP: case DOWN: case UP_UPPER: case DOWN_UPPER:
            for(int x=0;x<matrix->w;x++){
                column = get_matrix_column(*matrix, x);
                if(orient==DOWN || orient==DOWN_UPPER){
                    reverse_array(column, matrix->h);
                    merge_single(column, matrix->h);
                    reverse_array(column, matrix->h);
                }
                else{
                    merge_single(column, matrix->h);
                }
                modify_matrix_column(matrix, column, x);
                free(column);
            }
            break;
        case LEFT: case RIGHT: case LEFT_UPPER: case RIGHT_UPPER:
            for(int y=0;y<matrix->h;y++){
                line = get_matrix_line(*matrix, y);
                if(orient==RIGHT || orient==RIGHT_UPPER){
                    reverse_array(line, matrix->w);
                    merge_single(line, matrix->w);
                    reverse_array(line, matrix->w);
                }
                else{
                    merge_single(line, matrix->w);
                }
                modify_matrix_line(matrix, line, y);
                free(line);
            }
            break;
        default:
            return false;
    }
    return true;
}

void merge_single(int* array, int length){
    bool flag = true;
    while(flag){
        flag = false;
        for(int i=1;i<length;i++){
            if(array[i-1]==array[i] && array[i]!=0){
                array[i-1] = array[i]*2;
                array[i] = 0;
                flag = true;
            }
            if(array[i-1]==0 && array[i]!=0){
                array[i-1] = array[i];
                array[i] = 0;
                flag = true;
            }
        }        
    }
}

void get_empty_block_randomly(Matrix m, int* x, int* y){
    /*
    if could not find an empty block, x = y = -1
    if memory error, x = y = -2
    
    No modification, so no need to use deep copy.
    */
    int r = rand();
    int tn = m.w*m.h;
    int* xs = (int*)malloc(tn*sizeof(int));
    if(xs==NULL){
        *x = -2; *y = -2;
        return;
    }
    int* ys = (int*)malloc(tn*sizeof(int));
    if(xs==NULL){
        free(xs);
        *x = -2; *y = -2;
        return;
    }

    int count = 0;
    for(int i=0;i<m.h;i++){
        for(int j=0;j<m.w;j++){
            if(m.var[i][j]==0){
                xs[count] = j;
                ys[count] = i;
                count ++;
            }
        }
    }
    if(count==0){
        *x = -1;
        *y = -1;
    }
    else if(count==1){
        *x = xs[0];
        *y = ys[0];
    }
    else{
        r = rand()%(count-1);
        *x = xs[r];
        *y = ys[r];
    }
    free(xs);
    free(ys);
}

bool summon_new_num(Matrix* m, int n){
    /*
    Our purpose is just to modify m, dude.
    */
    int x,y;
    get_empty_block_randomly(*m, &x, &y);
    if(x<0 || y<0){
        return false;
    }
    else{
        m->var[y][x] = n;
        return true;
    }
}

int get_num_width(int x){
    int count = 0;
    if(x<10 && x>-10) return 1;
    while(x){
        x /= 10;
        count ++;
    }
    return count;
}

int get_max_block_width(Matrix m){
    int mw = 1;
    int tmp;
    for(int y=0;y<m.h;y++){
        for(int x=0;x<m.w;x++){
            tmp = get_num_width(m.var[y][x]);
            if(tmp>mw){
                mw = tmp;
            }
        }
    }
    return mw;
}

void multi_print(char c, int rp){
    for(int i=0;i<rp;i++) putchar(c);
}

void print_stage(Matrix m){
    /*
    No modification, so no need to use deep copy.
    */
    int mw = get_max_block_width(m);
    char tmp[10] = "";
    sprintf(tmp,"%%%dd|",mw);
    for(int y=0;y<m.h;y++){
        multi_print('-',(mw+1)*m.w+1);
        putchar('\n');
        putchar('|');
        for(int x=0;x<m.w;x++){
            printf(tmp,m.var[y][x]);
        }
        putchar('\n');
    }
    multi_print('-',(mw+1)*m.w+1);
    putchar('\n');
}

bool check_if_end(Matrix m){
    /*
    No modification, so no need to use deep copy.
    */
    for(int y=0;y<m.h;y++){
        for(int x=0;x<m.w;x++){
            if(m.var[y][x]==0) return false;
            if(x<m.w-1){
                if(m.var[y][x]==m.var[y][x+1]) return false;
            }
            if(y<m.h-1){
                if(m.var[y][x]==m.var[y+1][x]) return false;
            }
        }
    }
    return true;
}

bool check_if_any_effect(Matrix m, char orient){
    /* 
    We do not want to modify m,
    create a deep-copied temporary var to
    make simulation.
    */
    bool flag = true;
    Matrix* tmp = deep_copy_matrix(m);
    if(merge(tmp, orient)){
        if(compare_matrix(*tmp,m)){
            flag = false;
        }
    }
    // print_stage(*tmp);
    // print_stage(m);
    destroy_matrix(tmp);
    return flag;
}

bool check_if_target_reached(Matrix m, int target){
    if(target<0) return false;
    for(int y=0;y<m.h;y++){
        for(int x=0;x<m.w;x++){
            if(m.var[y][x]>=target){
                return true;
            }
        }
    }
    return false;
}