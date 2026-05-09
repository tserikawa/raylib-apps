#ifndef ARRAY_INT_QUEUE
#define ARRAY_INT_QUEUE

typedef struct {
    int capacity;
    int count;
    int *values;
} array_int_queue;
 
array_int_queue *aiq_initialize(int capacity);

int aiq_enqueue(array_int_queue *q, int value);

int aiq_is_full(const array_int_queue *q);
#endif