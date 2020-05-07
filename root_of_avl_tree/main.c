#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int First = 1;

typedef struct TNode *Tree;
struct TNode {
    int Data;
    struct TNode *Left;
    struct TNode *Right;
    int Height;
    int BalanceFactor;
};

int IsEmpty(Tree T);
Tree InsertNode(int Data, Tree T);
int DestroyTree(Tree T);
int GetHeight(Tree T);
Tree LLRotate(Tree T);
Tree LRRotate(Tree T);
Tree RLRotate(Tree T);
Tree RRRotate(Tree T);
int UpdateHeight(Tree T);

int main() {
    FILE *fp;
    fp = fopen("input1.txt", "r");

    int N = 0;
    fscanf(fp, "%d ", &N);

    int* input = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        fscanf(fp, "%d ", &input[i]);
    }

    Tree T = NULL;
    for (int i = 0; i < N; i++) {
        T = InsertNode(input[i], T);
    }

    printf("%d", T->Data);
    
    DestroyTree(T);
    T = NULL;

    fclose(fp);
    
    return 0;
}

int IsEmpty(Tree T) {
    return T == NULL;
}

Tree InsertNode(int Data, Tree T) {
    if (IsEmpty(T)) {
        T = malloc(sizeof(struct TNode));
        T->Data = Data;
        T->Left = NULL;
        T->Right = NULL;
        T->Height = 0;
        T->BalanceFactor = 0;
        return T;
    } 
    
    if (Data < T->Data) {
        T->Left = InsertNode(Data, T->Left);
    } else if (Data > T->Data) {
        T->Right = InsertNode(Data, T->Right);
    }

    T->Height = GetHeight(T->Left) > GetHeight(T->Right) ? GetHeight(T->Left) : GetHeight(T->Right);
    T->Height++;
    T->BalanceFactor = GetHeight(T->Left) - GetHeight(T->Right);

    if (T->BalanceFactor > 1) {
        if (Data < T->Left->Data)
            T = LLRotate(T);
        else
            T = LRRotate(T);    
    } else if (T->BalanceFactor < -1) {
        if (Data < T->Right->Data)
            T = RLRotate(T);
        else
            T = RRRotate(T); 
    }

    return T;
}

int DestroyTree(Tree T) {
    if (IsEmpty(T))
        return 0;

    DestroyTree(T->Left);
    DestroyTree(T->Right);

    free(T);
    T = NULL;

    return 0;
}

int GetHeight(Tree T) {
    if (IsEmpty(T))
        return -1;
    else
        return T->Height;
}

Tree LLRotate(Tree T) {
    Tree NewRoot = T->Left;
    T->Left = NewRoot->Right;
    NewRoot->Right = T;

    UpdateHeight(NewRoot);
    return NewRoot;
}

Tree LRRotate(Tree T) {
    Tree NewRoot = T->Left->Right;
    T->Left->Right = NewRoot->Left;
    Tree Temp = T->Left;
    T->Left = NewRoot->Right;

    NewRoot->Left = Temp;
    NewRoot->Right = T;

    UpdateHeight(NewRoot);
    return NewRoot;
}

Tree RLRotate(Tree T) {
    Tree NewRoot = T->Right->Left;
    T->Right->Left = NewRoot->Right;
    Tree Temp = T->Right;
    T->Right = NewRoot->Left;

    NewRoot->Right = Temp;
    NewRoot->Left = T;

    UpdateHeight(NewRoot);
    return NewRoot;
}

Tree RRRotate(Tree T) {
    Tree NewRoot = T->Right;
    T->Right = NewRoot->Left;
    NewRoot->Left = T;

    UpdateHeight(NewRoot);
    return NewRoot;
}

int UpdateHeight(Tree T) {
    if (IsEmpty(T))
        return 0;
    
    if (!IsEmpty(T->Left))
        UpdateHeight(T->Left);

    if (!IsEmpty(T->Right))
        UpdateHeight(T->Right);

    T->Height = GetHeight(T->Left) > GetHeight(T->Right) ? GetHeight(T->Left) : GetHeight(T->Right);
    T->Height++;
    T->BalanceFactor = GetHeight(T->Left) - GetHeight(T->Right);

    return 0;
}