#ifndef ___vector
#define ___vector

typedef struct
{
    int size;
    double *values;
} vector;

vector *vector_calloc(int size);

void vector_free(vector *v);

void vector_set(vector *v, int index, double value);

double vector_get(const vector *v, int index);
#endif