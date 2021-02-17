#include "stacks.h"

void push(stack_t** stackp, void* item) {
    stack_t* newNode = (stack_t*)malloc(sizeof(stack_t));
    if (newNode == NULL) {
        perror("Allocation error: Node couldn't be created. Exiting.");
        exit(1);
    }

    newNode->value = item;

    if (*stackp == NULL) {    // Starting the stack now
        newNode->next = NULL;
    } else {                // Stack already has something in it
        newNode->next = *stackp;
    }

    *stackp = newNode;
}

void* pop(stack_t** stackp) {
    void* holder = (*stackp)->value;
    stack_t* destroyMe = *stackp;
    if ((*stackp)->next != NULL) {
        *stackp = (*stackp)->next;
    } else {
        *stackp = NULL;
    }
    free(destroyMe);
    return holder;
}

void print(stack_t* stack, const char* format) {
    for (stack_t* current = stack; current != NULL; current = current->next) {
        printf(format, current->value);
    }
    puts("");
}

void destroy(stack_t** stackp) {
    if (*stackp == NULL) {
        return;
    }
    destroy(&((*stackp)->next));
    free((*stackp)->value);
    free(*stackp);
    *stackp = NULL;
}
