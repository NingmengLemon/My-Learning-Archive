#ifndef _MATRIX_H
#define _MATRIX_H

typedef struct _Matrix
{
    int w;
    int h;
    int **var;
} Matrix;

Matrix* create_matrix(int WIDTH, int HEIGHT, int INT_TO_FILL);

void modify_matrix(Matrix* MATRIX, int X, int Y, int NEW_VAR);

void destroy_matrix(Matrix* MATRIX);

int get_matrix_item(Matrix MATRIX, int X, int Y);

int* get_matrix_line(Matrix MATRIX, int Y);

int* get_matrix_column(Matrix MATRIX, int X);

void reverse_array(int* ARRAY, int LENGTH);

void modify_matrix_line(Matrix* MATRIX, int* NEW_LINE, int Y);

void modify_matrix_column(Matrix* MATRIX, int* NEW_COLUMN, int X);

bool compare_matrix(Matrix MATRIX_A, Matrix MATRIX_B);

Matrix* deep_copy_matrix(Matrix MATRIX);

#endif