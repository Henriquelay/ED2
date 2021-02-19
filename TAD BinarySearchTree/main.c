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

    srand(time(NULL));
    node_t* tree = NULL;
    for (int i = 0; i < atoi(argv[1]); i++) {
        int generated = rand();
        tree = insertKey(&tree, generated);
    }

    clock_t startTime;

    startTime = clock();
    inOrderRecursive(tree, &printUsingFormat);
    printf("Recursive time: %lf seconds\n", ((double)clock() - startTime) / CLOCKS_PER_SEC);
    startTime = clock();
    inOrderIterative(tree, &printUsingFormat);
    printf("Iterative time: %lf seconds\n", ((double)clock() - startTime) / CLOCKS_PER_SEC);



    destroyBST(&tree);

    return 0;
}
