#include <time.h>
#include "bst.h"

void printUsingFormat(node_t* tree) {
    // printf("%d ", tree->key);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        puts("Usage: main (NUMBER OF RANDOM INSERTIONS) [print format]");
        return 1;
    }

    char debugMode = argc > 2;

    srand(time(NULL));
    node_t* tree = NULL;
    if (debugMode) printf("Generated: ");
    for (int i = 0; i < atoi(argv[1]); i++) {
        int generated = rand() % 20;
        if (debugMode) printf("%d ", generated);
        tree = insertKey(&tree, generated);
    }
    if (debugMode) puts("");


    clock_t startTime;

    startTime = clock();
    levelOrderInterative(tree, &printUsingFormat);
    printf("Iterative level time: %lf seconds\n", ((double)clock() - startTime) / CLOCKS_PER_SEC);



    destroyBST(&tree);

    return 0;
}
