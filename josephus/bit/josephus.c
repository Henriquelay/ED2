#include "josephus.h"
#include <limits.h>

josephusList* init(int size) {
    if (size < 1) {
        perror("Size can't be less than 1!");
        exit(1);
    }

    josephusList* newJosephus = (josephusList*)malloc(sizeof(josephusList));

    if (newJosephus == NULL) {
        perror("Error allocating new list!");
        exit(1);
    }

    // From limits.h
    // Number of bytes * CHAR_BIT is how much bits is in a byte (may vary with archtecture)
    newJosephus->typeSize = sizeof(uint8_t) * CHAR_BIT;

    newJosephus->list = (uint8_t*)calloc(size / newJosephus->typeSize + 1, sizeof(uint8_t));

    if (newJosephus->list == NULL) {
        perror("Error allocating list of int!");
        exit(1);
    }

    newJosephus->size = size;

    return newJosephus;
}

void destroy(josephusList* it) {
    free(it->list);
    free(it);
    it = NULL;
}

void run(josephusList* josephus, int n, char print) {
    unsigned int i = 0;

    // To exclude all but 1 number
    for (int members = 1; members < josephus->size; members++) {
        // Excludes nth member, ignores marked already
        int nCounter = 0;
        for (;;) {
            if (!(josephus->list[i / josephus->typeSize] & (0x01 << (i % josephus->typeSize))))
                nCounter++;
            if (nCounter >= n) break;
            i = (i + 1) % josephus->size;
        }
        if (print) printf("%d, ", i + 1);
        josephus->list[i / josephus->typeSize] = josephus->list[i / josephus->typeSize] | (0x01 << (i % josephus->typeSize));
    }
}

void printAll(josephusList* josephus) {
    printf("[");
    unsigned int forTarget = josephus->size / josephus->typeSize;
    for (int i = 0; i < forTarget; i++) {
        if (!(josephus->list[i] & (0x01 << (i % josephus->typeSize)))) {
            printf("%d,", i + 1);
        }
    }
    printf("]\n");
}
