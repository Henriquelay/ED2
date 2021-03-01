#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "item.h"


extern void sort(Item* itemArray, int lo, int hi);

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("Missing arguments. Usage: (program) (Number of items to order) (list of items)");
    }

    int arraySize = atoi(argv[1]);
    Item* itemArray = (Item*)malloc(sizeof(Item) * arraySize);
    if (itemArray == NULL) {
        perror("Error allocating array! Exiting");
        exit(1);
    }
    for (int i = 0; i < arraySize; i++) {
        itemArray[i] = atoi(argv[2+ i]);
    }

    clock_t clockBefore = clock();

    sort(itemArray, 0, arraySize);

    printf("Sorting took %lf seconds\nSorted array: [", (double)(clock() - clockBefore) / CLOCKS_PER_SEC);
    for (int i = 0; i < arraySize; i++) {
        printf("%d ", itemArray[i]);
    }
    puts("]");

    free(itemArray);

    return 0;
}
