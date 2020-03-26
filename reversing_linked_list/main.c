#include <stdio.h>
#include <stdlib.h>

typedef struct NodeInfo *pNodeInfo;
struct NodeInfo {
    int Addr;
    int Data;
    int Next;
};
struct NodeInfo ZeroNodeInfo = {0, 0, 0};

typedef struct SNode *Stack;
struct SNode {
    struct NodeInfo Info;
    struct SNode *Next;
};

struct NodeInfo FindNode(pNodeInfo L, int Length, int Addr);
int IsEmpty(Stack S);
Stack CreateStack();
int Push(Stack S, struct NodeInfo Info);
struct NodeInfo Pop(Stack S);

int main() {
    FILE *fp;
    fp = fopen("input.txt", "r");
    int HEAD, N, K;
    fscanf(fp, "%d %d %d", &HEAD, &N, &K);
    
    pNodeInfo List = (pNodeInfo)malloc(sizeof(struct NodeInfo) * N);

    for(int i = 0; i < N; i++) {
        fscanf(fp, "%d %d %d", &(List[i].Addr), &(List[i].Data), &(List[i].Next));
    }

    fclose(fp);

    Stack S = CreateStack();

    int Addr = HEAD;
    for(int i = 0; i < K; i++) {
        struct NodeInfo TempNodeInfo;
        TempNodeInfo = FindNode(List, N, Addr);
        Push(S, TempNodeInfo);
        Addr = TempNodeInfo.Next;
    }

    struct NodeInfo TempNodeInfo;
    struct NodeInfo LastTempNodeInfo;
    for (int i = 0; i < K; i++) {       
        TempNodeInfo = Pop(S);
        if (i != 0) {
            LastTempNodeInfo.Next = TempNodeInfo.Addr;
            printf("%05d %d %05d\n", LastTempNodeInfo.Addr, LastTempNodeInfo.Data, LastTempNodeInfo.Next);
        }
        LastTempNodeInfo = TempNodeInfo;
    }

    LastTempNodeInfo.Next = Addr;
    printf("%05d %d %05d\n", LastTempNodeInfo.Addr, LastTempNodeInfo.Data, LastTempNodeInfo.Next);

    for (int i = 0; i < N - K; i++) {
        TempNodeInfo = FindNode(List, N, Addr);
        printf("%05d %d %05d\n", TempNodeInfo.Addr, TempNodeInfo.Data, TempNodeInfo.Next);
        Addr = TempNodeInfo.Next;
    }

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