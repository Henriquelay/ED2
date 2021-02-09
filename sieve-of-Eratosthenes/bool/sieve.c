#include <stdlib.h>
#include <stdio.h>

#include "sieve.h"

t_list* init(int size) {
    if (size < 2) {
        perror("Size is invalid");
        exit(1);
    }

    t_list* list = (t_list*)malloc(sizeof(t_list) * size - 2);

    if (list == NULL) {
        perror("Error allocating list");
        exit(1);
    }

    for (int i = 0; i < size - 2; i++) {
        list[i].mark = 0;
    }

    return list;
}

void destroy(t_list* list) {
    free(list);
    list = NULL;
}

int indexFirstNotMarkedBigger(t_list* list, int biggerThan, int size) {
    for (int i = biggerThan; i < size; i++) {
        if (!list[i - 2].mark) return i;
    }
    return -1;
}

void printPrimes(t_list* list, int size) {
    for (int i = 0; i < size - 2; i++) {
        if (!list[i].mark) {
            printf("%d,", i + 2);
        }
    }
    puts("");
}

void markAllMultiples(t_list* list, int multipleOf, int size) {
    for (int multiple = 2, i = multiple * multipleOf; i < size - 2; multiple++, i = multiple * multipleOf) {
        list[i - 2].mark = 1;
    }
}

void markEveryMultiple(t_list* list, int size) {
    for (int i = 2; i < size - 2; i++) {
        if (list[i].mark)
            continue;
        markAllMultiples(list, i, size);
    }
}
