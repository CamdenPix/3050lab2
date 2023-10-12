#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct rbstNode Node;

typedef struct rbstNode{
    int * key;
    Node * right;
    Node * left;
}Node;

typedef struct Root{
    Node* node;
}Root;


typedef struct RBST{
    int * size;
    Root* root;
}RBST;

RBST initRBST();

int insertHelper(Node* root, Node* newNode);

int insertRBST(RBST tree, int key);

int freeRBSTHelper(Node* root);

int freeRBST(RBST tree);

int collapseTree(Node* root);

int rebuildHelper(Node* newRoot);

int rebuildRBST(RBST tree, Node* newRoot);


int testRSBT(int n, int* array);

int freeRSBT(int n, int* array);