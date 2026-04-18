#include <assert.h>
#include "stack.h"

int main(){
    // gcc test.c stack.c
    // ./a.out

    stack s;
    initialize(&s, 5);
    assert(capacity(&s) == 5);
    assert(is_empty(&s));
    assert(!is_full(&s));

    push(&s, 1);
    push(&s, 2);
    assert(!is_empty(&s));
    
    int top;
    peek(&s, &top);
    assert(top == 2);

    assert(size(&s) == 2);
    pop(&s, &top);
    assert(size(&s) == 1);

    clear(&s);
    assert(size(&s) == 0);
    assert(is_empty(&s));

    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    push(&s, 4);
    push(&s, 5);
    assert(is_full(&s));
}