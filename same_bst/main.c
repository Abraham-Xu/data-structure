#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int First = 1;

typedef struct TNode *Tree;
struct TNode {
    char Data;
    struct TNode *Left;
    struct TNode *Right;
};

int IsEmpty(Tree T);
Tree InsertNode(int Data, Tree T);
int SameTree(Tree T1, Tree T2);
int DestroyTree(Tree T);

int main() {
    FILE *fp;
    fp = fopen("input1.txt", "r");

    int N = 0;
    fscanf(fp, "%d ", &N);
    int L = 0;

    while(N != 0) {
        fscanf(fp, "%d\n", &L);

        if (L > 0) {
            int **input = malloc(sizeof(int*) * (L + 1));
            for (int i = 0; i < L + 1; i++) {
                input[i] = malloc(sizeof(int) * N);
                for( int j = 0; j < N; j++) {
                    fscanf(fp, "%d ", &input[i][j]);
                }
            }

            Tree T0 = NULL;
            for (int j = 0; j < N; j++) {
                T0 = InsertNode(input[0][j], T0);
            }

            Tree T = NULL;
            for (int i = 0; i < L; i++) {
                for (int j = 0; j < N; j++) {
                    T = InsertNode(input[i + 1][j], T);
                }

                if (SameTree(T0, T))
                    printf("Yes\n");
                else
                    printf("No\n");

                DestroyTree(T);
                T = NULL;
            }
        }

        fscanf(fp, "%d ", &N);
    }

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
    } else if (Data < T->Data) {
        T->Left = InsertNode(Data, T->Left);
    } else if (Data > T->Data) {
        T->Right = InsertNode(Data, T->Right);
    }

    return T;
}

int SameTree(Tree T1, Tree T2) {
    if (IsEmpty(T1) && IsEmpty(T2))
        return 1;

    if (IsEmpty(T1) || IsEmpty(T2))
        return 0;

    if (T1->Data != T2->Data)
        return 0;

    return (SameTree(T1->Left, T2->Left) && SameTree(T1->Right, T2->Right));
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