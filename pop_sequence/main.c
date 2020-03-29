#include <stdio.h>
#include <stdlib.h>

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
    fp = fopen("input.txt", "r");
    int M, N, K;
    fscanf(fp, "%d %d %d\n", &M, &N, &K);

    int **a = (int**)malloc(sizeof(int*) * K);  
    for (int i = 0; i < K; i++)  
        a[i] = (int*)malloc(sizeof(int) * N);

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++)
            fscanf(fp, "%d ", &a[i][j]);
    }

    fclose(fp);

    for (int i = 0; i < K; i++) {
        Stack S = CreateStack(M);
        int Top = 0;
        int Flag = 0;

        for (int j = 0; j < N; j++) {
            if (a[i][j] > Top) {
                for (int k = Top + 1; k < a[i][j]; k++) {
                    if (Push(S, k) == -1) {
                        Flag = 1;
                        break;
                    }
                }
                Top = a[i][j];
            } else {
                if (Pop(S) != a[i][j]) {
                    Flag = 1;
                    break;
                }
            }
            
            if (Flag == 1)
                break;
        }

        if (Flag == 1)
            printf("NO\n");
        else
            printf("YES\n");

        DestroyStack(S);
    }

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