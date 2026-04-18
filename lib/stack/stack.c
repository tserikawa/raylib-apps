#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int initialize(stack *s, int size)
{
    s->size = 0;

    s->array = calloc(size, sizeof(int));
    if (s->array == NULL)
    {
        s->capacity = 0;
        return -1;
    }
    else
    {
        s->capacity = size;
        return 0;
    }
}

int push(stack *s, int value)
{
    if (s->size > s->capacity)
    {
        return -1;
    }
    else
    {
        s->array[s->size] = value;
        s->size++;
        return 0;
    }
}

int pop(stack *s, int *top)
{
    if (s->size <= 0)
    {
        return -1;
    }
    else
    {
        *top = s->array[s->size - 1];
        s->size--;
        return 0;
    }
}

int peek(stack *s, int *top)
{
    if (s->size <= 0)
    {
        return -1;
    }
    else
    {
        *top = s->array[s->size-1];
        return 0;
    }
}

void clear(stack *s)
{
    s->size = 0;
}

int capacity(const stack *s)
{
    return s->capacity;
}

int size(const stack *s)
{
    return s->size;
}

int is_empty(const stack *s)
{
    return s->size <= 0;
}

int is_full(const stack *s)
{
    return s->size == s->capacity;
}