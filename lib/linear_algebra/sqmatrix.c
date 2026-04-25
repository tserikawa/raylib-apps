#include "sqmatrix.h"
#include "vector.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

sqmatrix *sqmatrix_calloc(int size)
{
    sqmatrix *m = malloc(sizeof(sqmatrix));
    if(m == NULL)
    {
        return NULL;
    }

    m->size = size;
    m->values = calloc(size * size, sizeof(double));
    if(m->values == NULL)
    {
        return NULL;
    }
    else
    {
        return m;
    }
}

void sqmatrix_free(sqmatrix *m)
{
    free(m->values);
    free(m);
}

void sqmatrix_print(const sqmatrix *m)
{
    for(int i = 0; i < m->size; i++)
    {
        printf("|");
        for(int j = 0; j < m->size; j++)
        {
            printf("%15.2f ", sqmatrix_get(m, i, j));
        }
        printf("|");
        printf("\n");
    }
}

double sqmatrix_get(const sqmatrix *m, int row, int col)
{
    assert(0 <= row && row < m->size);
    assert(0 <= col && col < m->size);
    return m->values[row * m->size + col];
}

void sqmatrix_set(sqmatrix *m, int row, int col, double value)
{
    assert(0 <= row && row < m->size);
    assert(0 <= col && col < m->size);
    m->values[row * m->size + col] = value;
}

void sqmatrix_mul_vec(const sqmatrix *m, const vector *v, vector *res)
{
    assert(m->size == v->size);
    assert(v->size == res->size);

    for(int i = 0; i < m->size; i++)
    {
        double result = 0.0;
        for(int j = 0; j < m->size; j++)
        {
            result += sqmatrix_get(m, i, j) * vector_get(v, j);
        }
        vector_set(res, i, result);
    }
}

void sqmatrix_mul_mat(const sqmatrix *m1, const sqmatrix *m2, sqmatrix *res)
{
    assert(m1->size == m2->size);

    int n = m1->size;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            double total = 0.0;
            for(int k = 0; k < n; k++)
            {
                total += sqmatrix_get(m1, i, k) * sqmatrix_get(m2, k, j);
            }
            sqmatrix_set(res, i, j, total);
        }
    }
}