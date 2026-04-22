#ifndef ___matrix
#define ___matrix

#include "vector.h"

/// @brief 正方行列
typedef struct {
    int size;
    double *values;    
} sqmatrix;

sqmatrix *sqmatrix_calloc(int size);

void sqmatrix_free(sqmatrix *m);

void sqmatrix_print(const sqmatrix *m);

double sqmatrix_get(const sqmatrix *m, int row, int col);

void sqmatrix_set(sqmatrix *m, int row, int col, double value);

void sqmatrix_mul_vec(const sqmatrix *m, const vector *v, vector *res);

void sqmatrix_mul_mat(const sqmatrix *m1, const sqmatrix *m2, sqmatrix *res);

#endif