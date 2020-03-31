#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TNode *Tree;
struct TNode {
    char Data;
    struct TNode *Left;
    struct TNode *Right;
};

struct ListTree {
    char Data;
    int Left;
    int Right;
};

int IsEmpty(Tree S);
struct ListTree*  ReadTree(FILE *fp, int N);
Tree InsertTree(struct ListTree *ListTree, int i);
int FindRoot(struct ListTree *LT, int N);
int IsomorphismCheck(Tree T1, Tree T2);

int main() {
    FILE *fp;
    fp = fopen("input1.txt", "r");
    int N;

    fscanf(fp, "%d\n", &N);
    //scanf("%d\n", &N);
    struct ListTree *LT1 = ReadTree(fp, N);

    //struct ListTree *LT1 = ReadTree(N);
    Tree T1 = N == 0 ? NULL : InsertTree(LT1, FindRoot(LT1, N));

    fscanf(fp, "%d\n", &N);
    //scanf("%d\n", &N);
    struct ListTree *LT2 = ReadTree(fp, N);
    //struct ListTree *LT2 = ReadTree(N);
    Tree T2 = N == 0 ? NULL : InsertTree(LT2, FindRoot(LT2, N));

    //fclose(fp);

    int result = IsomorphismCheck(T1, T2);
    if (result)
        printf("Yes");
    else
        printf("No");    

    free(LT1);
    free(LT2);
    //DestroyTree(T1);
    //DestroyTree(T2);
    return 0;
}

int IsEmpty(Tree S) {
    return S == NULL;
}

struct ListTree* ReadTree(FILE *fp, int N) {
    struct ListTree* LT = (struct ListTree*)malloc(sizeof(struct ListTree) * N);  
    
    char Data;
    char Left[2];
    char Right[2];
    
    for (int i = 0; i < N; i++) {
        fscanf(fp, "%c %s %s\n", &Data, &Left, Right);
        //scanf("%c %s %s\n", &Data, Left, Right);
        LT[i].Data = Data;
        LT[i].Left = strcmp(Left, "-") ? atoi(Left) : -1;
        LT[i].Right = strcmp(Right, "-") ? atoi(Right) : -1;
    }

    return LT;
}

Tree InsertTree(struct ListTree *ListTree, int i) {
    Tree T = (Tree)malloc(sizeof(struct TNode));
    
    T->Data = ListTree[i].Data;
    
    T->Left = ListTree[i].Left == -1 ? NULL : InsertTree(ListTree, ListTree[i].Left);
    T->Right = ListTree[i].Right == -1 ? NULL : InsertTree(ListTree, ListTree[i].Right);

    return T;
}

int FindRoot(struct ListTree *LT, int N) {
    int *NumMap = (int*)malloc(sizeof(int) * N);
    memset(NumMap, 0, N * sizeof(int));

    for (int i = 0; i < N; i++) {
        if (LT[i].Left != -1) 
            NumMap[LT[i].Left] = 1;
        if (LT[i].Right != -1) 
            NumMap[LT[i].Right] = 1;
    }
    
    int i = 0;
    while (NumMap[i] == 1) {
        i++;
    }

    free(NumMap);
    return i;
}

int IsomorphismCheck(Tree T1, Tree T2) {
    if (T1 == NULL && T2 == NULL) // both NULL
        return 1;
    else if (T1 == NULL || T2 == NULL) // either NULL
        return 0;

    if (T1->Data != T2->Data)
        return 0;

    if (IsomorphismCheck(T1->Left, T2->Right) && IsomorphismCheck(T1->Right, T2->Left)) { // symmetric nodes
        return 1;
    } else if (IsomorphismCheck(T1->Left, T2->Left) && IsomorphismCheck(T1->Right, T2->Right)) { // same nodes
        return 1;
    }

    return 0;
}