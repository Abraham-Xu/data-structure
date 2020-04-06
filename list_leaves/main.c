#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int FindRoot(int (*Input)[2], int N);
int InsertTree(int (*Input)[2], int *Tree, int i, int Pos);
int PrintLeaves(int *Tree, int TreeNodeMax);

int main() {
    FILE *fp;
    fp = fopen("input1.txt", "r");

    int N = 0;
    fscanf(fp, "%d\n", &N);

    int (*Input)[2] = malloc(sizeof(int[N][2]));
    for(int i = 0; i < N; i++) {
        char temp_left = 0;
        char temp_right = 0;
        fscanf(fp, "%c %c\n", &temp_left, &temp_right);
        Input[i][0] = temp_left == 45 ? -1 : (int)temp_left - 48;
        Input[i][1] = temp_right == 45 ? -1 : (int)temp_right - 48;
    }

    fclose(fp);

    int RootNum = FindRoot(Input, N);

    int TreeNodeMax = pow(2, N);
    int *Tree = malloc(sizeof(int) * TreeNodeMax);

    for (int i = 0; i < TreeNodeMax; i++) {
        Tree[i] = -1;
    }

    InsertTree(Input, Tree, RootNum, 1);
    PrintLeaves(Tree, TreeNodeMax);

    //int tree = (int*)malloc(sizeof(int) * pow(2, N));
    return 0;
}

int FindRoot(int (*Input)[2], int N) {
    int *NumMap = calloc(N, sizeof(int));

    for (int i = 0; i < N; i++) {
        if (Input[i][0] != -1) 
            NumMap[Input[i][0]] = 1;
        if (Input[i][1] != -1) 
            NumMap[Input[i][1]] = 1;
    }
    
    int i = 0;
    while (NumMap[i] == 1) {
        i++;
    }

    free(NumMap);
    return i;
}

int InsertTree(int (*Input)[2], int *Tree, int i, int Pos) {
    Tree[Pos] = i;
    
    if (Input[i][0] != -1)
        InsertTree(Input, Tree, Input[i][0], 2 * Pos);

    if (Input[i][1] != -1)
        InsertTree(Input, Tree, Input[i][1], 2 * Pos + 1);

    return 0;
}

int PrintLeaves(int *Tree, int TreeNodeMax) {
    int First = 0;
    for (int i = 0; i < TreeNodeMax; i++) {
        if (Tree[i] != -1 ) {
            if (2 * i >= TreeNodeMax) {
                if (First != 0)
                    printf(" ");
                printf("%d", Tree[i]);
                First = 1;
            } else if ((Tree[2 * i] == -1) && (Tree[2 * i + 1] == -1)) {
                if (First != 0)
                    printf(" ");
                printf("%d", Tree[i]);
                First = 1;
            }
        }
            
    }
}