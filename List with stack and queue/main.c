#include <time.h>

#include "list.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        puts("Usage: main (NUMBER OF RANDOM INSERTIONS) [print format]");
        return 1;
    }

    srand(time(NULL));
    list_t* list = init_list();

    printf("Generated: ");
    for (int i = 0; i < atoi(argv[1]); i++) {
        int* allocatingSize = (int*)malloc(sizeof(int));
        int generated = rand() % 10;
        *allocatingSize = generated;
        printf("%d ", generated);
        enqueue(list, allocatingSize);
    }
    puts("");

    printList(list, "%p ");
    puts("");

    for (int i = 0; i < atoi(argv[1]); i++) {
        int* removed = (int*)pop(list);
        printf("%d ", *removed);
        free(removed);
    }

    destroyList(list);

    return 0;
}
