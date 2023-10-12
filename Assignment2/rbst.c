#include "rbst.h"

//Initialize a new Random BST
RBST initRBST()
{
    RBST tree;
    tree.root = malloc(sizeof(Root));
    if(tree.root == NULL)
        printf("Root failed to allocate memory\n");
    tree.root->node = malloc(sizeof(Node));
    if(tree.root->node == NULL)
        printf("Root failed to allocate memory\n");
    tree.size = malloc(sizeof(int));
    if(tree.size == NULL)
        printf("Failed to allocate memory for RBST size\n");
    *(tree.size) = 0;
    return tree;
}


//Recursive helper function to insert into BST
int insertHelper(Node* root, Node* newNode)
{   
    int nodesVisted = 1;
    if(*(newNode->key) < *(root->key)){ //check if right
        if(root->right == NULL) {
            root->right = newNode;
        } 
        else {
            nodesVisted += insertHelper(root->right, newNode); //recursive call
        }
    } 
    else if (*(newNode->key) > *(root->key)) { //check if left
        if(root->left == NULL) {
            root->left = newNode;
        } else {
            nodesVisted += insertHelper(root->left, newNode); //recursive call
        }
    }
    return nodesVisted;
}

//Handles deciding whether or not to make the new key the root node and inserting the node. Returns # of nodes visited
int insertRBST(RBST tree, int key)
{
    int nodesVisted = 0;
    *(tree.size) += 1;

    if(*(tree.size) == 1) { //Special Case if tree has no data yet
        tree.root->node->key = malloc(sizeof(int));
        *(tree.root->node->key) = key;
        tree.root->node->left = NULL;
        tree.root->node->right = NULL;
        return 1; 
    }
    else {
        //create node
        Node* newNode = malloc(sizeof(Node));
        newNode->key = malloc(sizeof(int));
        if(newNode == NULL) {
            printf("Error creating space for a node\n");
            return 0;
        }
        *(newNode->key) = key;
        newNode->left = NULL;
        newNode->right = NULL;

        //insert the node in the tree
        nodesVisted += insertHelper(tree.root->node, newNode);

        if(drand48() < 1.0/(float)(*(tree.size))) //the random part of RBST
        {
            nodesVisted += rebuildRBST(tree, newNode);
        }
        return nodesVisted;
    }
}

//Recursive fuction for free RBST
int freeRBSTHelper(Node* root)
{
    int nodesVisted = 1;
    if(root->left != NULL) {
        nodesVisted += freeRBSTHelper(root->left);
    }
    if(root->right != NULL) {
        nodesVisted += freeRBSTHelper(root->right);
    }
    free(root->key);
    free(root);
    return nodesVisted;
}

//Frees the memory reserved by the tree
int freeRBST(RBST tree)
{
    free(tree.size);
    int freed = freeRBSTHelper(tree.root->node);
    return freed;
}


int collapseTree(Node* root)
{
    int nodesVisted = 1;
    if (root->left == NULL && root->right == NULL) //check to see if bottom node
        return nodesVisted;

    //witchcraft for collapsing left side of a node
    //go left and point all the way up
    //basically collapse everthing into a doublely linked list
    /*
            o
          /   \
        ooo   ooo
    to
        ooooooo
    but recursively so for any size of tree
    */
    if (root->left != NULL)
    {
        Node* nextNode = root->left;
        nodesVisted += collapseTree(nextNode);
        while(nextNode->right != NULL)
            {nextNode = nextNode->right; nodesVisted++;}
        nextNode->right = root;
        root->left = nextNode;
    }

    //same but for right
    if(root->right != NULL)
    {
        Node* nextNode = root->right;
        nodesVisted += collapseTree(nextNode);
        while(nextNode->left != NULL)
            {nextNode = nextNode->left; nodesVisted++;}
        nextNode->left = root;
        root->right = nextNode;
    }
    return nodesVisted;
}

//recursive function for rebuilding the ree. Returns # of nodes visted
int rebuildHelper(Node* newRoot)
{
    int nodesVisted = 0;
    if(newRoot->left != NULL) {
        Node* leftTemp = newRoot->left;
        leftTemp->right = NULL; //stop pointing at me
        int k = 1;
        while(leftTemp->left != NULL) {//randomly chooses a spot to point to
            leftTemp = leftTemp->left;
            if(drand48() < 1.0/(float)k)
            {
                newRoot->left = leftTemp;
            }
            nodesVisted++;
            k++;
        }
        nodesVisted += rebuildHelper(newRoot->left);
    }
    //also do for right
    if(newRoot->right != NULL) {
        Node* rightTemp = newRoot->right;
        newRoot->right->left = NULL;
        int k = 1;
        while(rightTemp->right != NULL) {
            rightTemp = rightTemp->right;
            if(drand48() < 1.0/(float)k)
            {
                newRoot->right = rightTemp;
            }
            nodesVisted++;
            k++;
        }
        nodesVisted += rebuildHelper(newRoot->right);
    }
    return nodesVisted;
}

//Flattens and rebuilds the RBST with the key being the root node. Returns # of nodes visited
int rebuildRBST(RBST tree, Node* newRoot)
{
    int nodesVisted = 0;
    //Collapse tree into a doublely linked list
    nodesVisted += collapseTree(tree.root->node);
    //Tree points to the newNode
    tree.root->node = newRoot;
    //passes it to rebuildHelper
    nodesVisted += rebuildHelper(newRoot);
    return nodesVisted;
}