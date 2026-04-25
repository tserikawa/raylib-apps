#include "vector.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    // gcc vector_test.c vector.c
    vector *v = vector_calloc(3);
    assert(vector_get(v, 0) == 0);
    assert(vector_get(v, 1) == 0);
    assert(vector_get(v, 2) == 0);
    vector_set(v, 0, 10);
    vector_set(v, 1, 20);
    vector_set(v, 2, 30);
    assert(vector_get(v, 0) == 10);
    assert(vector_get(v, 1) == 20);
    assert(vector_get(v, 2) == 30);
    vector_free(v);
}