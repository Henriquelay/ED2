#include <time.h>
#include "bst.h"

void printUsingFormat(node_t* tree) {
    printf("%d ", tree->key);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        puts("Usage: main (NUMBER OF RANDOM INSERTIONS) [print format]");
        return 1;
    }

    srand(time(NULL));
    node_t* tree = NULL;
    printf("Generated: ");
    for (int i = 0; i < atoi(argv[1]); i++) {
        int generated = rand();
        printf("%d ", generated);
        tree = insertKey(&tree, generated);
    }
    puts("");

    if (argc > 2) {
        inOrder(tree, &printUsingFormat);
        puts("");
    }

    // printf("Altura: %d\n", height(tree));

    postOrderIterative(tree, &printUsingFormat);

    destroyBST(&tree);

    return 0;
}
