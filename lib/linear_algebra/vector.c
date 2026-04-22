#include "vector.h"
#include <assert.h>
#include <stdlib.h>

vector *vector_calloc(int size)
{
    vector *v = malloc(sizeof(vector));
    if(v == NULL){
        return NULL;
    }

    v->size = size;
    v->values = calloc(size, sizeof(double));
    if ( v->values == NULL)
    {
        return NULL;
    }
    else
    {
        return v;
    }
}

void vector_free(vector *v)
{
    free(v->values);
    free(v);
}

void vector_set(vector *v, int index, double value)
{
    assert(0 <= index && index < v->size);
    v->values[index] = value;
}

double vector_get(const vector *v, int index)
{
    assert(0 <= index && index < v->size);
    return v->values[index];
}