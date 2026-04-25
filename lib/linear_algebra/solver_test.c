#include "vector.h"
#include "sqmatrix.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_gaussian_elimination()
{
    sqmatrix *a = sqmatrix_calloc(3);
    sqmatrix_set(a, 0, 0, 10);
    sqmatrix_set(a, 0, 1, 2);
    sqmatrix_set(a, 0, 2, 1);
    sqmatrix_set(a, 1, 0, 2);
    sqmatrix_set(a, 1, 1, 20);
    sqmatrix_set(a, 1, 2, -2);
    sqmatrix_set(a, 2, 0, -2);
    sqmatrix_set(a, 2, 1, 3);
    sqmatrix_set(a, 2, 2, 10);
    
    vector *b = vector_calloc(3);
    vector_set(b, 0, 9);
    vector_set(b, 1, -44);
    vector_set(b, 2, 22);

    vector *x = vector_calloc(3);
    solver_gaussian_elimination(a, b, x);
    assert(abs( 1.0 - vector_get(x, 0) < 0.01));
    assert(abs(-2.0 - vector_get(x, 1) < 0.01));
    assert(abs( 3.0 - vector_get(x, 2) < 0.01));

    vector_free(x);
    vector_free(b);
    sqmatrix_free(a);
}
int main()
{
    // gcc solver_test.c vector.c sqmatrix.c solver.c
    printf("[solver_test.c]\n");

    test_gaussian_elimination();
    printf(" - test_gaussian_elimination ... ok\n");
}
