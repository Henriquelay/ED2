#include "list.h"

list_t* initList() {
    list_t* newList = (list_t*)malloc(sizeof(list_t));
    if (newList == NULL) {
        perror("Error creating new list. Exiting");
        exit(1);
    }
    newList->head = NULL;
    newList->tail = NULL;

    return newList;
}

void push(list_t* list, void* item) {
    if (item == NULL) {
        return;
    }
    linked_node_t* newNode = (linked_node_t*)malloc(sizeof(linked_node_t));
    if (newNode == NULL) {
        perror("Allocation error: Node couldn't be created. Exiting.");
        exit(1);
    }

    newNode->value = item;
    newNode->previous = NULL;
    newNode->next = list->head;
    if (newNode->next != NULL) {
        newNode->next->previous = newNode;
    }
    list->head = newNode;
    if (list->tail == NULL) {
        list->tail = newNode;
    }
}

void* pop(list_t* list) {
    if (list->head == NULL) {
        return NULL;
    }

    void* holder = list->head->value;
    linked_node_t* destroyMe = list->head;
    list->head = list->head->next;
    if (list->head == NULL) {
        list->tail = NULL;
    } else {
        list->head->previous = NULL;
    }
    free(destroyMe);
    return holder;
}

void enqueue(list_t* list, void* item) {
    if (item == NULL) {
        return;
    }
    linked_node_t* newNode = (linked_node_t*)malloc(sizeof(linked_node_t));
    if (newNode == NULL) {
        perror("Allocation error: Node couldn't be created. Exiting.");
        exit(1);
    }

    newNode->value = item;
    newNode->next = NULL;
    newNode->previous = list->tail;
    if (newNode->previous != NULL) {
        newNode->previous->next = newNode;
    }
    list->tail = newNode;
    if (list->head == NULL) {
        list->head = newNode;
    }
}

void* dequeue(list_t* list) {
    return pop(list);
}

void printList(list_t* list, const char* format) {
    for (linked_node_t* current = list->head; current != NULL; current = current->next) {
        printf(format, current->value);
    }
    puts("");
}

void pointerThingy(linked_node_t* node) {
    if (node != NULL) {
        if (node->next != NULL) {
            node->next->previous = node->previous;
        }
        if (node->previous != NULL) {
            node->previous->next = node->next;
        }
    }
}

void destroyList(list_t* list) {
    if (list != NULL) {
        while (list->head != NULL) {
            linked_node_t* freeMe = list->head;
            list->head = list->head->next;
            free(freeMe->value);
            free(freeMe);
        }
        free(list);
    }
}
