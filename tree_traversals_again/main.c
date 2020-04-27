#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int First = 1;

typedef struct TNode *Tree;
struct TNode {
    char Data;
    struct TNode *Left;
    struct TNode *Right;
    struct TNode *Father;
    int Traversed;
};

int IsEmpty(Tree T);
Tree InsertNode(int Data, Tree Father);
void PostOrderTraversal(Tree T);
Tree PopNode(Tree CurNode);

int main() {
    FILE *fp;
    fp = fopen("input1.txt", "r");

    int N = 0;
    fscanf(fp, "%d\n", &N);
    int (*Op)[2] = malloc(sizeof(int) * 2 * (2 * N));

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

    if(N == 0) return 0;

    Tree T = InsertNode(Op[0][1], NULL);
    Tree CurNode = T;

    for (int i = 1; i < 2 * N; i++) {
        if (Op[i][0] == 1) {
            if (CurNode->Left == NULL) {
                CurNode->Left = InsertNode(Op[i][1], CurNode);
                CurNode = CurNode->Left;
            } else {
                CurNode->Right = InsertNode(Op[i][1], CurNode);
                CurNode = CurNode->Right;
            }
        } else if (Op[i][0] == -1) {
            CurNode = PopNode(CurNode);
        }
    }

    PostOrderTraversal(T);
    
    return 0;
}

int IsEmpty(Tree T) {
    return T == NULL;
}

Tree InsertNode(int Data, Tree Father) {
    Tree T = (Tree)malloc(sizeof(struct TNode));
    
    T->Data = Data;
    
    T->Left = NULL;
    T->Right = NULL;
    T->Father = Father;
    T->Traversed = 0;

    return T;
}

void PostOrderTraversal(Tree T) {
    if (T == NULL)
        return;
    
    PostOrderTraversal(T->Left);
    PostOrderTraversal(T->Right);
    if (!First) 
        printf(" ");
    printf("%d", T->Data);
    First = 0;
}

Tree PopNode(Tree CurNode){
    if (CurNode->Traversed == 0) {
        CurNode->Traversed = 1;
    } else {
        CurNode = CurNode->Father;
        CurNode = PopNode(CurNode);
    }

    return CurNode;
}