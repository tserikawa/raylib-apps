#include "array-int-queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    // gcc test.c array-int-queue.c
    // ./a.out

    array_int_queue *q = aiq_initialize(2);
    assert(!aiq_is_full(q));
    
    aiq_enqueue(q, 10);
    aiq_enqueue(q, 12);
    assert(aiq_is_full(q));
}