#include <stdio.h>
#include <stdlib.h>

typedef struct NodeInfo *pNodeInfo;
struct NodeInfo {
    int Addr;
    int Data;
    int Next;
};
struct NodeInfo ZeroNodeInfo = {0, 0, 0};

typedef struct SNode *List;
typedef struct SNode *Stack;
struct SNode {
    struct NodeInfo Info;
    struct SNode *Next;
};

struct NodeInfo FindNode(pNodeInfo L, int Length, int Addr);

List CreatEmptyList();
int PrintList(List L);
struct SNode* Insert(struct SNode *Target, struct NodeInfo Info);

int IsEmpty(Stack S);
Stack CreateStack();
int Push(Stack S, struct NodeInfo Info);
struct NodeInfo Pop(Stack S);

int main() {
    FILE *fp;
    fp = fopen("input.txt", "r");
    int HEAD, N, K;
    fscanf(fp, "%d %d %d", &HEAD, &N, &K);
    
    pNodeInfo Array = (pNodeInfo)malloc(sizeof(struct NodeInfo) * N);

    for(int i = 0; i < N; i++) {
        fscanf(fp, "%d %d %d", &(Array[i].Addr), &(Array[i].Data), &(Array[i].Next));
    }

    fclose(fp);

    List L = CreatEmptyList();
    int Addr = HEAD;
    struct SNode *Tail = L;
    while (Addr != -1) {
        struct NodeInfo TempNodeInfo;
        TempNodeInfo = FindNode(Array, N, Addr);
        Tail = Insert(Tail, TempNodeInfo);
        Addr = TempNodeInfo.Next;
    }

    Stack S = CreateStack();

    struct SNode *Cursor = L->Next;
    for (int i = 0; i < K; i++) {
        struct NodeInfo TempNodeInfo;
        TempNodeInfo = Cursor->Info;
        L->Next = Cursor->Next;
        Push(S, TempNodeInfo);
        free(Cursor);
        Cursor = L->Next;
    }

    struct SNode *Target = L;
    for (int i = 0; i < K; i++) {       
        struct NodeInfo TempNodeInfo = Pop(S);    
        Target = Insert(Target, TempNodeInfo);
    }

    Cursor = L;
    while (Cursor->Next != NULL) {
        Cursor->Info.Next = Cursor->Next->Info.Addr;
        Cursor = Cursor->Next;
    }

    PrintList(L);

    return 0;
}

struct NodeInfo FindNode(pNodeInfo L, int Length, int Addr) {
    int i = 0;
    while (i < Length && L[i].Addr != Addr) {
        i++;
    }
    return L[i];
}

Stack CreateStack(){
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}

int Push(Stack S, struct NodeInfo Info){
    struct SNode *NewSNode = (struct SNode*)malloc(sizeof(struct SNode));
    NewSNode->Info = Info;
    NewSNode->Next = S->Next;
    S->Next = NewSNode;
    return 0;
}

struct NodeInfo Pop(Stack S) {
    if (IsEmpty(S)) {
        return ZeroNodeInfo;
    } else {
        struct SNode *Top = S->Next;
        S->Next = Top->Next;
        struct NodeInfo Info = Top->Info;
        free(Top);
        return Info;
    }
}

int IsEmpty(Stack S) {
    return S->Next == NULL;
}

List CreatEmptyList() {
    List L = (List)malloc(sizeof(struct SNode));
    L->Info = ZeroNodeInfo;
    L->Next = NULL;

    return L;
}

struct SNode* Insert(struct SNode *Target, struct NodeInfo Info) {   
    struct SNode *NewNode = (struct SNode *)malloc(sizeof(struct SNode));
    NewNode->Info = Info;
    NewNode->Next = Target->Next;
    Target->Next = NewNode;

    return NewNode;
}

int PrintList(List L) {
    if (L == NULL) {
        printf("Non-Existed List");
        return -1;
    }

    if (L->Next == NULL) {
        printf("Empty List!");
        return 0;
    }

    struct SNode* Cursor = L->Next;
    while(Cursor->Next != NULL) {
        printf("%05d %d %05d\n", Cursor->Info.Addr, Cursor->Info.Data, Cursor->Info.Next);
        Cursor = Cursor->Next;
    }
    printf("%05d %d -1", Cursor->Info.Addr, Cursor->Info.Data);

    return 0;
}