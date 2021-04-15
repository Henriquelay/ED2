#include <time.h>

#include "list.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        puts("Usage: main (NUMBER OF RANDOM INSERTIONS) [print format]");
        return 1;
    }

    srand(time(NULL));
    list_t* list = list_init();

    printf("Generated: ");
    for (int i = 0; i < atoi(argv[1]); i++) {
        int* allocatingSize = (int*)malloc(sizeof(int));
        int generated = rand() % 10;
        *allocatingSize = generated;
        printf("%d ", generated);
        list_enqueue(list, allocatingSize);
    }
    puts("");

    list_print(list, "%p ");
    puts("");

    for (int i = 0; i < atoi(argv[1]); i++) {
        int* removed = (int*)list_pop(list);
        printf("%d ", *removed);
        free(removed);
    }

    list_destroy(list);

    return 0;
}
