#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal( BinTree BT );  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    FILE *fp;
    fp = fopen("input1.txt", "r");
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST =  NULL;
    fscanf(fp, "%d", &N);
    for ( i=0; i<N; i++ ) {
        fscanf(fp, "%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    fscanf(fp, "%d", &N);
    for( i=0; i<N; i++ ) {
        fscanf(fp, "%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    fscanf(fp, "%d", &N);
    for( i=0; i<N; i++ ) {
        fscanf(fp, "%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    fclose(fp);
    return 0;
}
/* 你的代码将被嵌在这里 */

void PreorderTraversal( BinTree BT ) {
    if (BT == NULL)
        return;

    printf("%d ", BT->Data);
    
    if (BT->Left != NULL)
        PreorderTraversal(BT->Left);

    if (BT->Right != NULL)
        PreorderTraversal(BT->Right);
}

void InorderTraversal( BinTree BT ) {
    if (BT == NULL)
        return;
    
    if (BT->Left != NULL)
        InorderTraversal(BT->Left);

    printf("%d ", BT->Data);

    if (BT->Right != NULL)
        InorderTraversal(BT->Right);
}

BinTree Insert( BinTree BST, ElementType X ) {
    if (BST == NULL) {
        BinTree NewNode = malloc(sizeof(struct TNode));
        NewNode->Data = X;
        NewNode->Left = NULL;
        NewNode->Right = NULL;
        return NewNode;
    } else if (X < BST->Data) {
        BST->Left = Insert(BST->Left, X);
    } else if (X > BST->Data) {
        BST->Right = Insert(BST->Right, X);
    }

    return BST;
}

BinTree Delete( BinTree BST, ElementType X ) {
    if (BST == NULL) {
        printf("Not Found\n");
        return NULL;
    }

    if (X < BST->Data) {
        BST->Left = Delete(BST->Left, X);
    } else if (X > BST->Data) {
        BST->Right = Delete(BST->Right, X);
    } else {
        if (BST->Left == NULL && BST->Right == NULL) {
            BST = NULL;
        } else if (BST->Left != NULL && BST->Right == NULL) {
            Position Temp = BST;
            BST = BST->Left;
            free(Temp);
        } else if (BST->Left == NULL && BST->Right != NULL) {
            Position Temp = BST;
            BST = BST->Right;
            free(Temp);
        } else { // BST->Left != NULL && BST->Right != NULL
            Position NewRoot = FindMax(BST->Left);
            BST->Left = Delete(BST->Left, NewRoot->Data);
            BST->Data = NewRoot->Data;
        }
    }

    return BST;
}
 
Position Find( BinTree BST, ElementType X ) {
    if (BST == NULL)
        return NULL;

    if (X < BST->Data) {
        return Find(BST->Left, X);
    } else if (X > BST->Data) {
        return Find(BST->Right, X);
    } else {
        return BST;
    }
}

Position FindMin( BinTree BST ) {
    if (BST == NULL)
        return NULL;

    if (BST->Left != NULL)
        return FindMin(BST->Left);
    else
        return BST;
}

Position FindMax( BinTree BST ) {
    if (BST == NULL)
        return NULL;

    if (BST->Right != NULL)
        return FindMax(BST->Right);
    else
        return BST;
}