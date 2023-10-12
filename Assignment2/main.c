#include "rbst.h"

//inserts n keys and returns number of nodes visited
int testInsertRSBT(int n, int* array)
{
    //printf("testInsert Called\n\n\n");
    int* index = malloc(sizeof(int));
    index = array;
    RBST tree = initRBST();
    if(tree.root == NULL || tree.size == NULL)
        return 0;
    int nodesVisited = 0;

    int i;
    for(i=0; i<n; i++)
    {
        int temp = insertRBST(tree,*(index+i));
        if(temp == 0)
            return 0;
        nodesVisited += temp;
        //printf("Value inserted was %d\n", *(index+i));
    }

    //free(index);
    freeRBST(tree);
    //printf("testInsert finished\n");
    return nodesVisited;
}


int testFreeRSBT(int n, int* array)
{
    //printf("testFree Called\n\n\n");
    int* index = malloc(sizeof(int));
    index = array;
    RBST tree = initRBST();
    if(tree.root == NULL || tree.size == NULL)
        return 0;

    int i;
    for(i=0; i<n; i++)
    {
        int temp = insertRBST(tree,*(index+i));
        if(temp == 0)
            return 0;
        //printf("Value inserted was %d\n", *(index+i));
    }

    //free(index);
    //printf("testFree almost finished\n");
    return freeRBST(tree);
}

void swap(int* i, int* j)
{
    int temp;
    temp = *i;
    *i = *j;
    *j = temp;
    return;
}

//note: start will be multiplied by 2 until it's greater than max
int scalingTests(int start, int max)
{
    while(start <= max)
    {
        //printf("Start: %d\n", start);
        int* array = malloc(start*sizeof(int));
        int* val = malloc(sizeof(int));
        val = array;
        int i;
        for(i = 1; i <= start; i++)
            {*(val+i) = i;}

        //Fisher Yates Shuffle to randomize the list
        int j;
        for(i = start - 1; i > 0; i--)
        {
            j = rand() % (i + 1);
            swap((val+i), (val+j));
        }

        printf("Data Size: %d\tWhen Inserting, Nodes Vistied: %d\tWhen Freeing, Nodes Visited: %d\n", start, testInsertRSBT(start, array), testFreeRSBT(start, array));

        free(array);
        //free(val);
        start *= 2;
    }
    return 1;
}

int main(){
    printf("Start\n");
    srand(time(0));
    scalingTests(32, 16384);
    printf("End\n\n");
}