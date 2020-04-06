#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SNode *Stack;
struct SNode {
    int Data;
    int Size;
    int MaxSize;
    struct SNode *Next;
};

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxSize);
int DestroyStack(Stack S);
int Push(Stack S, int Data);
int Pop(Stack S);

int main() {
    FILE *fp;
    fp = fopen("input1.txt", "r");

    int N = 0;
    fscanf(fp, "%d\n", &N);
    int (*Op)[2] = malloc(sizeof(int) * 2 * (2 * N + 1));

    char Operation[10];
    char Node[10];

    for (int i = 0; i < 2 * N; i++) {
        fscanf(fp, "%s", Operation);
        if (strcmp(Operation, "Push") == 0) {
            Op[i][0] = 1;
            fscanf(fp, "%s", Node);
            Op[i][1] = atoi(Node);
        } else if (strcmp(Operation, "Pop") == 0) {
            Op[i][0] = -1;
            Op[i][1] = -1;
        }
    }

    fclose(fp);

    Stack S = CreateStack(N);
    int SavePop = 0;
    for (int i = 0; i < 2 * N; i++) {
        if (Op[i][0] == 1) {
            Push(S, Op[i][1]);
        } else if (Op[i][0] == -1) {
            if (SavePop == 1) {
                printf("%d ", Pop(S));
                SavePop = 0;
            }
            if (Op[i + 1][0] != 1) {
                printf("%d ", Pop(S));
            } else {
                SavePop = 1;
            }
        }
    }

    DestroyStack(S);
    
    return 0;
}

Stack CreateStack(int MaxSize){
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    S->Size = 0;
    S->MaxSize = MaxSize;
    return S;
}

int DestroyStack(Stack S){
    struct SNode *Cursor = S;
    while (Cursor != NULL) {
        Cursor = Cursor->Next;
        free(Cursor);
        Cursor = NULL;
    }

    return 0;
}

int Push(Stack S, int Data){
    if (IsFull(S)) {
        return -1;
    } else { 
        struct SNode *NewSNode = (struct SNode*)malloc(sizeof(struct SNode));
        NewSNode->Data = Data;
        NewSNode->Next = S->Next;
        S->Next = NewSNode;
        S->Size++;
        return 0;
    }
}

int Pop(Stack S) {
    if (IsEmpty(S)) {
        return -1;
    } else {
        struct SNode *Top = S->Next;
        S->Next = Top->Next;
        int Data = Top->Data;
        free(Top);
        S->Size--;
        return Data;
    }
}

int IsEmpty(Stack S) {
    return S->Next == NULL;
}

int IsFull(Stack S) {
    return S->Size == S->MaxSize;
}