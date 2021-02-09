#include <stdlib.h>
#include <stdio.h>

#include "sieve.h"

t_list* init(int size) {
    if (size < 2) {
        perror("Size is invalid");
        exit(1);
    }

    t_list* list = (uint8_t*)calloc(size / 8, sizeof(uint8_t));

    if (list == NULL) {
        perror("Error allocating list");
        exit(1);
    }

    return list;
}

void destroy(t_list* list) {
    free(list);
    list = NULL;
}

char isMarked(t_list* list, int position) {
    return ((list[(position / 8)] >> position % 8) & 0x01);
}

int indexFirstNotMarkedBigger(t_list* list, int biggerThan, int size) {
    for (int i = biggerThan; i < size; i++) {
        if (!isMarked(list, i)) return i;
    }
    return -1;
}

void printPrimes(t_list* list, int size) {
    for (int i = 0; i < size - 2; i++) {
        if (!isMarked(list, i)) {
            printf("%d,", i + 2);
        }
    }
    puts("");
}

void markAllMultiples(t_list* list, int multipleOf, int size) {
    for (int multiple = 2, i = multiple * multipleOf; i < size - 2; multiple++, i = multiple * multipleOf) {
        list[i - 2] = list[i - 2] & (0x01 << i % 8);
    }
}

void markEveryMultiple(t_list* list, int size) {
    for (int i = 2; i < size - 2; i++) {
        if (isMarked(list, i - 2)) {
            continue;
        }
        markAllMultiples(list, i, size);
    }
}
