#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>
#include <stdio.h>


typedef struct linked_node_t {
    void* value;
    struct linked_node_t* next;
    struct linked_node_t* previous;
} linked_node_t;

typedef struct list_t {
    linked_node_t* head;
    linked_node_t* tail;
} list_t;

list_t* initList();

void push(list_t* list, void* item);
void* pop(list_t* list);

void enqueue(list_t* list, void* item);
void* dequeue(list_t* list);

void runOnAll(list_t* list, void (*visit)(linked_node_t));

void printList(list_t* stack, const char* format);

void destroyList(list_t* list);

#endif
