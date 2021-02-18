#include "bst.h"

void exitIfFailedAlloc(void* ptr) {
    if (ptr == NULL) {
        perror("Error allocating new node! Exiting");
        exit(1);
    }
}

node_t* init(int key) {
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
    }
    if (node->key < (*tree)->key) {
        insert(&((*tree)->left), node);
        return *tree;
    }
    if (node->key > (*tree)->key) {
        insert(&((*tree)->right), node);
        return *tree;
    }
    return NULL;
    // If `node->key == (*tree)->key`, it will be ignored
}

node_t* insertKey(node_t** tree, int key) {
    return insert(tree, init(key));
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

void preOrder(node_t* tree, void (*visit)(node_t*)) {
    if (tree == NULL) {
        return;
    }
    visit(tree);
    preOrder(tree->left, visit);
    preOrder(tree->right, visit);
}

void inOrder(node_t* tree, void (*visit)(node_t*)) {
    if (tree == NULL) {
        return;
    }
    inOrder(tree->left, visit);
    visit(tree);
    inOrder(tree->right, visit);
}

void posOrder(node_t* tree, void (*visit)(node_t*)) {
    if (tree == NULL) {
        return;
    }
    posOrder(tree->left, visit);
    posOrder(tree->right, visit);
    visit(tree);
}

void preOrderIterative(node_t* tree, void (*visit)(node_t*)) {
    stack_t* nodes = NULL;

    push(&nodes, tree);

    node_t* current = NULL;
    while ((current = pop(&nodes)) != NULL) {
        visit(current);
        if (current->right != NULL) {
            push(&nodes, current->right);
        }
        if (current->left != NULL) {
            push(&nodes, current->left);
        }
    }
}

void inOrderIterative(node_t* tree, void (*visit)(node_t*)) {
    stack_t* nodes = NULL;

    node_t* current = tree;
    while (nodes != NULL || current != NULL) {
        if (current != NULL) {
            push(&nodes, current);
            current = current->left;
        } else {
            current = pop(&nodes);
            visit(current);
            current = current->right;
        }
    }
}

void postOrderIterative(node_t* tree, void (*visit)(node_t*)) {
    stack_t* nodes = NULL;

    node_t* lastNodeVisited = NULL;

    node_t* current = tree;
    while (nodes != NULL || current != NULL) {
        if (current != NULL) {
            push(&nodes, current);
            current = current->left;
        } else {
            node_t* stackHead = nodes->value;

            if (stackHead->right != NULL && lastNodeVisited != stackHead->right) {
                current = stackHead->right;
            } else {
                visit(stackHead);
                lastNodeVisited = pop(&nodes);
            }
        }
    }
}
