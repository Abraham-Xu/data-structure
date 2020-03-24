#include <stdio.h>
#include <stdlib.h>

typedef struct Term *PtrToNode;

struct Term {
    int Coef;
    int Index;
    PtrToNode Next;
};

typedef PtrToNode List;

List CreatEmptyList();
List CreateList(int n);
List Insert(List L, PtrToNode P);
List Mul(List L1, int n, List L2, int m);
List Add(List L1, int n, List L2, int m);
int PrintList(List L);

int main() {
    int n = 0;
    scanf("%d", &n);
    List L1 = CreateList(n);
    
    int m = 0;
    scanf("%d", &m);
    List L2 = CreateList(m);

    List LMul;
    List LAdd;

    LMul = Mul(L1, n, L2, m);
    LAdd = Add(L1, n, L2, m);
    
    PrintList(LMul);
    printf("\n");
    PrintList(LAdd);

    free(L1);
    free(L2);
    free(LMul);
    free(LAdd);

    L1 = NULL;
    L2 = NULL;
    LMul = NULL;
    LAdd = NULL;

    return 0;
}

List CreatEmptyList() {
    List L = (List)malloc(sizeof(struct Term));
    L->Coef = 0;
    L->Index = 0;
    L->Next = NULL;

    return L;
}

List CreateList(int n) {
    List L = CreatEmptyList();

    PtrToNode Tail = L;
    for(int i =0; i < n; i++) {
        PtrToNode PNode = (PtrToNode)malloc(sizeof(struct Term));
        scanf(" %d", &(PNode->Coef));
        scanf(" %d", &(PNode->Index));
        PNode->Next = NULL;
        Tail->Next = PNode;
        Tail = Tail->Next;
    }

    return L;
}

List Insert(List L, PtrToNode P) {
    if (L == NULL)
        return NULL;
    
    PtrToNode Cursor1 = L;
    PtrToNode Cursor2 = L->Next;

    while (Cursor2 != NULL) {
        if (P->Index < Cursor2->Index) {
            Cursor1 = Cursor1->Next;
            Cursor2 = Cursor2->Next;
        } else {
            break;
        }
    }

    if (Cursor2 == NULL || P->Index != Cursor2->Index) {
        Cursor1->Next = P;
        P->Next = Cursor2;
        return L;
    } else {
        Cursor2->Coef += P->Coef;
        if (Cursor2->Coef == 0) {
            Cursor1->Next = Cursor2->Next;
            Cursor2->Next = NULL;
            free(Cursor2);
        }
    }

    return L;
}

List Mul(List L1, int n, List L2, int m) {
    if (L1 == NULL || L2 == NULL) {
        return NULL;
    }

    List L = CreatEmptyList();

    PtrToNode P1 = L1->Next;
    PtrToNode P2 = L2->Next;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            PtrToNode P0 = (PtrToNode)malloc(sizeof(struct Term));
            P0->Coef = P1->Coef * P2->Coef;
            P0->Index = P1->Index + P2->Index;
            P0->Next = NULL;

            if (P0->Coef == 0) {
                free(P0);
            } else {
                Insert(L, P0);
            }

            P2 = P2->Next;
        }

        P2 = L2->Next;
        P1 = P1->Next;
    }

    return L;
}

List Add(List L1, int n, List L2, int m) {
    if (L1 == NULL || L2 == NULL) {
        return NULL;
    }

    PtrToNode Cursor1 = L1->Next;
    PtrToNode Cursor2 = L2->Next;
    L1->Next = NULL;
    L2->Next = NULL;

    List L = CreatEmptyList();

    while (Cursor1 != NULL || Cursor2 != NULL) {
        int Op = 0;
        if (Cursor1 == NULL || Cursor2 == NULL) {
            if (Cursor2 == NULL)
                Op = 1;
        } else {
            if (Cursor1->Index > Cursor2->Index) {
                Op = 1;
            } else if(Cursor1->Index == Cursor2->Index) {
                Op = 2;
            }
        }
        
        PtrToNode P0 = (PtrToNode)malloc(sizeof(struct Term));

        switch (Op) {
            case 0:
                P0->Coef = Cursor2->Coef;
                P0->Index = Cursor2->Index;
                P0->Next = NULL;
                Cursor2 = Cursor2->Next;
                break;
            case 1:
                P0->Coef = Cursor1->Coef;
                P0->Index = Cursor1->Index;
                P0->Next = NULL;
                Cursor1 = Cursor1->Next;
                break;
            case 2:
                P0->Coef = Cursor1->Coef + Cursor2->Coef;
                P0->Index = Cursor1->Index;
                P0->Next = NULL;
                Cursor1 = Cursor1->Next;
                Cursor2 = Cursor2->Next;
                break;
            default:break;
        }

        if(P0->Coef == 0) {
            free(P0);
        } else {
            Insert(L, P0);
        } 
    }

    return L;
}

int PrintList(List L) {
    if (L == NULL) {
        printf("NULL");
        return -1;
    }

    if (L->Next == NULL) {
        printf("0 0");
        return 0;
    }

    PtrToNode Cursor = L->Next;
    while(Cursor != NULL) {
        printf("%d %d", Cursor->Coef, Cursor->Index);
        Cursor = Cursor->Next;
        if(Cursor != NULL)
            printf(" ");
    }

    return 0;
}