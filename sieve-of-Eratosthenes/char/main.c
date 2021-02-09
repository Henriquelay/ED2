#include <stdio.h>
#include <stdlib.h>

#include "sieve.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Program needs at least a number N to sieve up to that number!");
        return 1;
    }

    int size = atoi(argv[1]);
    t_list* numberList = init(size);

    markEveryMultiple(numberList, size);

    if (argc > 2) {
        printPrimes(numberList, size);
    }

    destroy(numberList);

    return 0;
}
