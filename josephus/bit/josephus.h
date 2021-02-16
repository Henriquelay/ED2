#ifndef _JOSEPHUS_H_
#define _JOSEPHUS_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct josephusList {
    uint8_t* list;
    int size;
    unsigned int typeSize;
} josephusList;

josephusList* init(int size);

void run(josephusList* josephus, int n, char print);

void printAll(josephusList* josephus);

void destroy(josephusList* josephus);

#endif
