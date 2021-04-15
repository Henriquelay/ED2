#include "bst.h"

void exitIfFailedAlloc(void* ptr) {
    if (ptr == NULL) {
        perror("Error allocating new node! Exiting");
        exit(1);
    }
}

node_t* initBST(int key) {
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    exitIfFailedAlloc(newNode);

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->key = key;

    return newNode;
}

void destroyBST(node_t** tree) {
    if (*tree == NULL) {
        return;
    }
    destroyBST(&((*tree)->left));
    destroyBST(&((*tree)->right));
    free(*tree);
    *tree = NULL;
}

node_t* insert(node_t** tree, node_t* node) {
    if (*tree == NULL) {
        *tree = node;
        return *tree;
    } else {
        if (node->key < (*tree)->key) {
            insert(&((*tree)->left), node);
        }
        if (node->key > (*tree)->key) {
            insert(&((*tree)->right), node);
        }
    }
    return *tree;
}

node_t* insertKey(node_t** tree, int key) {
    return insert(tree, initBST(key));
}

int height(node_t* tree) {
    if (tree == NULL) {
        return -1;
    }
    int leftHeight = height(tree->left);
    int rightHeight = height(tree->right);
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    return rightHeight + 1;
}

void preOrderRecursive(node_t* tree, void (*visit)(node_t*)) {
    if (tree == NULL) {
        return;
    }
    visit(tree);
    preOrderRecursive(tree->left, visit);
    preOrderRecursive(tree->right, visit);
}

void inOrderRecursive(node_t* tree, void (*visit)(node_t*)) {
    if (tree == NULL) {
        return;
    }
    inOrderRecursive(tree->left, visit);
    visit(tree);
    inOrderRecursive(tree->right, visit);
}

void postOrderRecursive(node_t* tree, void (*visit)(node_t*)) {
    if (tree == NULL) {
        return;
    }
    postOrderRecursive(tree->left, visit);
    postOrderRecursive(tree->right, visit);
    visit(tree);
}

void preOrderIterative(node_t* tree, void (*visit)(node_t*)) {
    list_t* list = list_init();

    list_push(list, tree);

    node_t* current = NULL;
    while ((current = list_pop(list)) != NULL) {
        visit(current);
        if (current->right != NULL) {
            list_push(list, current->right);
        }
        if (current->left != NULL) {
            list_push(list, current->left);
        }
    }

    free(list);
}

void inOrderIterative(node_t* tree, void (*visit)(node_t*)) {
    list_t* list = list_init();

    node_t* current = tree;
    while (list->head != NULL || current != NULL) {
        if (current != NULL) {
            list_push(list, current);
            current = current->left;
        } else {
            current = list_pop(list);
            visit(current);
            current = current->right;
        }
    }

    free(list);
}

void postOrderIterative(node_t* tree, void (*visit)(node_t*)) {
    list_t* list = list_init();

    node_t* lastNodeVisited = NULL;

    node_t* current = tree;
    while (list->head != NULL || current != NULL) {
        if (current != NULL) {
            list_push(list, current);
            current = current->left;
        } else {
            node_t* stackHead = list->head->value;

            if (stackHead->right != NULL && lastNodeVisited != stackHead->right) {
                current = stackHead->right;
            } else {
                visit(stackHead);
                lastNodeVisited = list_pop(list);
            }
        }
    }

    free(list);
}

void levelOrderInterative(node_t* tree, void (*visit)(node_t*)) {
    list_t* list = list_init();

    list_enqueue(list, tree);

    node_t* current = NULL;
    while (list->tail != NULL) {
        current = list_dequeue(list);
        visit(current);
        list_enqueue(list, current->left);
        list_enqueue(list, current->right);
    }

    free(list);
}
