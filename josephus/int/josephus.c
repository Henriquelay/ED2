#include "josephus.h"

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

    newJosephus->list = (int*)calloc(size, sizeof(int));

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
    int i = 0;

    // To exclude all but 1 number
    for (int members = 1; members < josephus->size; members++) {
        // Excludes nth member, ignores marked already
        int nCounter = 0;
        do {

            if (josephus->list[i] == 0)
                nCounter++;
            if (nCounter >= n) break;
            i = (i + 1) % josephus->size;
        } while (1);
        if (print)
            printf("%d, ", i + 1);
        josephus->list[i] = 1;
    }
}

void printAll(josephusList* josephus) {
    printf("[");
    for (int i = 0; i < josephus->size; i++) {
        if (!(josephus->list[i])) {
            printf("%d,", i + 1);
        }
    }
    printf("]\n");
}
