#include "array-int-queue.h"
#include <stdlib.h>

array_int_queue *aiq_initialize(int capacity)
{
    array_int_queue *q = malloc(sizeof(array_int_queue));
    if(q == NULL)
    {
        return NULL;
    }

    q->capacity = capacity;
    q->count = 0;
    q->values = calloc(capacity, sizeof(int));
    if(q->values == NULL)
    {
        return NULL;
    }

    return q;
}

int aiq_enqueue(array_int_queue *q, int value)
{
    if(aiq_is_full(q))
    {
        return -1;
    }

    q->values[q->count] = value;
    q->count++;
}

int aiq_is_full(const array_int_queue *q)
{
    return q->count >= q->capacity;
}