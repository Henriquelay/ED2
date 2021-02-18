#ifndef _STACKS_H_
#define _STACKS_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct stack {
    void* value;
    struct stack* next;
} stack_t;

void push(stack_t** stackp, void* item);

void* pop(stack_t** stackp);

void print(stack_t* stack, const char* format);

void destroyStack(stack_t** stackp);

#endif
