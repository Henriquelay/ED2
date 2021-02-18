#ifndef _BST_H_
#define _BST_H_

#include <stdlib.h>
#include <stdio.h>
#include "../dijkstra's 2 stack/stacks.h"

typedef struct node_t {
    int key;
    struct node_t* left;
    struct node_t* right;
} node_t;

node_t* init(int key);

node_t* insert(node_t** tree, node_t* node);
node_t* insertKey(node_t** tree, int key);

// void remove(node_t** tree, node_t* node);

int height(node_t* tree);

void preOrder(node_t* tree, void (*visit)(node_t*));
void inOrder(node_t* tree, void (*visit)(node_t*));
void posOrder(node_t* tree, void (*visit)(node_t*));

void preOrderIterative(node_t* tree, void (*visit)(node_t*));
void inOrderIterative(node_t* tree, void (*visit)(node_t*));
void postOrderIterative(node_t* tree, void (*visit)(node_t*));

void destroyBST(node_t** tree);

#endif
