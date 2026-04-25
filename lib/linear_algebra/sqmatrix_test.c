#include "vector.h"
#include "sqmatrix.h"
#include <stdio.h>
#include <assert.h>

void test_mul_matrix_vector_2x2()
{
    sqmatrix *m = sqmatrix_calloc(2);
    sqmatrix_set(m, 0, 0, 1);
    sqmatrix_set(m, 0, 1, 3);
    sqmatrix_set(m, 1, 0, 4);
    sqmatrix_set(m, 1, 1, 5);
    
    vector *v = vector_calloc(2);
    vector_set(v, 0, 2);
    vector_set(v, 1, 6);

    vector *mv = vector_calloc(2);
    sqmatrix_mul_vec(m, v, mv);
    assert(vector_get(mv, 0) == 20);
    assert(vector_get(mv, 1) == 38);

    vector_free(mv);
    vector_free(v);
    sqmatrix_free(m);
}

void test_mul_matrix_vector_3x3()
{
    sqmatrix *m = sqmatrix_calloc(3);
    sqmatrix_set(m, 0, 0, 3);
    sqmatrix_set(m, 0, 1, 4);
    sqmatrix_set(m, 0, 2, 5);
    sqmatrix_set(m, 1, 0, 6);
    sqmatrix_set(m, 1, 1, 7);
    sqmatrix_set(m, 1, 2, 8);
    sqmatrix_set(m, 2, 0, 9);
    sqmatrix_set(m, 2, 1, 10);
    sqmatrix_set(m, 2, 2, 11);
    
    vector *v = vector_calloc(3);
    vector_set(v, 0, 1);
    vector_set(v, 1, 2);
    vector_set(v, 2, 3);

    vector *mv = vector_calloc(3);
    sqmatrix_mul_vec(m, v, mv);
    assert(vector_get(mv, 0) == 26);
    assert(vector_get(mv, 1) == 44);
    assert(vector_get(mv, 2) == 62);

    vector_free(mv);
    vector_free(v);
    sqmatrix_free(m);
}

void test_mul_matrix_matrix_3x3()
{
    sqmatrix *m1 = sqmatrix_calloc(3);
    sqmatrix_set(m1, 0, 0, 1);
    sqmatrix_set(m1, 0, 1, 2);
    sqmatrix_set(m1, 0, 2, 3);
    sqmatrix_set(m1, 1, 0, 4);
    sqmatrix_set(m1, 1, 1, 5);
    sqmatrix_set(m1, 1, 2, 6);
    sqmatrix_set(m1, 2, 0, 7);
    sqmatrix_set(m1, 2, 1, 8);
    sqmatrix_set(m1, 2, 2, 9);

    sqmatrix *m2 = sqmatrix_calloc(3);
    sqmatrix_set(m2, 0, 0, 1);
    sqmatrix_set(m2, 0, 1, 2);
    sqmatrix_set(m2, 0, 2, 3);
    sqmatrix_set(m2, 1, 0, 4);
    sqmatrix_set(m2, 1, 1, 5);
    sqmatrix_set(m2, 1, 2, 6);
    sqmatrix_set(m2, 2, 0, 7);
    sqmatrix_set(m2, 2, 1, 8);
    sqmatrix_set(m2, 2, 2, 9);

    sqmatrix *m = sqmatrix_calloc(3);
    sqmatrix_mul_mat(m1, m2, m);
    assert(sqmatrix_get(m, 0, 0) == 30);
    assert(sqmatrix_get(m, 0, 1) == 36);
    assert(sqmatrix_get(m, 0, 2) == 42);
    assert(sqmatrix_get(m, 1, 0) == 66);
    assert(sqmatrix_get(m, 1, 1) == 81);
    assert(sqmatrix_get(m, 1, 2) == 96);
    assert(sqmatrix_get(m, 2, 0) == 102);
    assert(sqmatrix_get(m, 2, 1) == 126);
    assert(sqmatrix_get(m, 2, 2) == 150);

    sqmatrix_free(m);
    sqmatrix_free(m2);
    sqmatrix_free(m1);
}

int main()
{
    // gcc sqmatrix_test.c vector.c sqmatrix.c
    printf("[matrix_test.c]\n");

    test_mul_matrix_vector_2x2();
    printf(" - test_mul_matrix_vector_2x2 ... ok\n");
    
    test_mul_matrix_vector_3x3();
    printf(" - test_mul_matrix_vector_3x3 ... ok\n");
    
    test_mul_matrix_matrix_3x3();
    printf(" - test_mul_matrix_matrix_3x3 ... ok\n");
}
