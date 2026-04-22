#include "solver.h"
#include "sqmatrix.h"
#include "vector.h"
#include <assert.h>
#include <stdio.h>

void solver_print(const sqmatrix *m, const vector *v)
{
    assert(m->size == v->size);

    int n = m->size;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%15.2f ", sqmatrix_get(m, i, j));
        }
        printf("|");
        printf("%15.2f ", vector_get(v, i));
        printf("\n");
    }
}

void solver_gaussian_elimination(sqmatrix *a, vector *b, vector *x)
{
    assert(a->size == b->size);

    int n = a->size;
    
    // 1. 前進消去
    for (int i = 0; i < n; i++)
    {
        // 1.1 定数倍(対角項を1にする)
        double aii = sqmatrix_get(a, i, i);

        double bi = vector_get(b, i) / aii;
        vector_set(b, i, bi);

        for (int j = i; j < n; j++)
        {
            double aij = sqmatrix_get(a, i, j);
            sqmatrix_set(a, i, j, aij / aii);
        }

        // 1.2 i + 1行以降のi列を0にする。
        for (int k = i + 1; k < n; k++)
        {
            double aki = sqmatrix_get(a, k, i);

            double bk = vector_get(b, k);
            vector_set(b, k, bk - aki * bi);

            for (int j = i; j < n; j++)
            {
                double aij = sqmatrix_get(a, i, j);
                double akj = sqmatrix_get(a, k, j);
                sqmatrix_set(a, k, j, akj - aki * aij);
            }
        }
    }

    // 2. 交代代入
    vector_set(x, n - 1, vector_get(b, n - 1) / sqmatrix_get(a, n - 1, n - 1));
    for (int i = n - 2; i >= 0; i--)
    {
        double ax = 0.0;
        for (int j = i + 1; j < n; j++)
        {
            ax += sqmatrix_get(a, i, j) * vector_get(x, j);
        }

        double bi = vector_get(b, i);
        double aii = sqmatrix_get(a, i, i);
        vector_set(x, i, (bi - ax) / aii);
    }
}