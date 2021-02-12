#ifndef _JOSEPHUS_H_
#define _JOSEPHUS_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct josephusList {
    int* list;
    int size;
} josephusList;

josephusList* init(int size);

void run(josephusList* josephus, int n, char print);

void printAll(josephusList* josephus);

void destroy(josephusList* josephus);

#endif
