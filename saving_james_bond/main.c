#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DIAMETER 15

struct SNode {
    int Data;
    struct SNode *Next;
};
typedef struct SNode *Position;

struct QNode {
    Position Front, Rear;
};
typedef struct QNode *Queue;

int IsEmpty(Queue S);
Queue CreateQueue();
int DestroyQueue(Queue S);
int Push(Queue S, int Data);
int Pop(Queue S);

int Connected(int *C1, int *C2, int Distance);
void DFS(int (*C)[2], int N, int S, int *V, int Dis);
void BFS(int **G, int N, int S, int *V);

int main()
{
    FILE *fp;
    fp = fopen("input3.txt", "r");
    int N, D;
    fscanf(fp, "%d %d\n", &N, &D);
    int (*Crocodiles)[2] = malloc(sizeof(int*) * (N + 1) * 2);

    for (int i = 0; i < N; i++) {
        fscanf(fp, "%d %d\n", &Crocodiles[i][0], &Crocodiles[i][1]);
    }
    Crocodiles[N][0] = 0;
    Crocodiles[N][1] = 0;

    fclose(fp);

    int *EdgeCocodiles = calloc(N, sizeof(int));

    for (int i = 0; i < N; i++) {
        if (Crocodiles[i][0] <= D - 50 
            || Crocodiles[i][0] >= 50 - D 
            || Crocodiles[i][1] <= D - 50
            || Crocodiles[i][1] >= 50 - D)
            EdgeCocodiles[i] = 1;
    }

    int *Visited = calloc(N + 1, sizeof(int)); // If the size of Visited is N, there will be runtime error in online test3.
    DFS(Crocodiles, N, N, Visited, D);

    int LiveOrDie = 0;
    if (N > 0) {
        for (int i = 0; i < N; i++) {
            if (Visited[i] && EdgeCocodiles[i]) {
                LiveOrDie = 1;
                break;
            }
        }
    } else {
        if (D >= 50)
            LiveOrDie = 1;
    }


    if (LiveOrDie == 1)
        printf("Yes");
    else
        printf("No");    

    return 0;
}

int Connected(int *C1, int *C2, int Distance) {
    float Dis;
    if (C1[0] == 0 && C1[1] == 0)
        Dis = (float)Distance + DIAMETER / 2.0; // Central Island Area
    else
        Dis = (float)Distance;
    
    return ((float)(pow((C1[0] - C2[0]), 2) + pow((C1[1] - C2[1]), 2)) <= (float)pow(Dis, 2));
}

void DFS(int (*C)[2], int N, int S, int *V, int Dis) {
    V[S] = 1;
    for (int i = 0; i < N; i++) {
        if (Connected(C[S], C[i], Dis) && !V[i]) {
            DFS(C, N, i, V, Dis);
        }
    }
}

void BFS(int **G, int N, int S, int *V) {
    printf("%d ", S);
    V[S] = 1;
    Queue Stk = CreateQueue(N);
    Push(Stk, S);
    while (!IsEmpty(Stk)) {
        int Temp = Pop(Stk);
        for (int i = 0; i < N; i++) {
            if (G[Temp][i] && !V[i]) {
                printf("%d ", i);
                V[i] = 1;
                Push(Stk, i);
            }
        }
    }
}

Queue CreateQueue(){
    Position Header = malloc(sizeof(struct SNode));
    Header->Data = 0;
    Header->Next = NULL;
    Queue S = malloc(sizeof(struct QNode));
    S->Front = Header;
    S->Rear = Header;
    return S;
}

int DestroyQueue(Queue S){
    Position Cursor = S->Front;
    while (Cursor != NULL) {
        Cursor = Cursor->Next;
        free(Cursor);
        Cursor = NULL;
    }

    return 0;
}

int Push(Queue S, int Data){
    struct SNode *NewSNode = malloc(sizeof(struct SNode));
    NewSNode->Data = Data;
    NewSNode->Next = S->Rear->Next;
    S->Rear->Next = NewSNode;
    S->Rear = NewSNode;
    return 0;
}

int Pop(Queue S) {
    if (IsEmpty(S)) {
        return -1;
    } else {
        struct SNode *Top = S->Front->Next;
        S->Front->Next = Top->Next;
        int Data = Top->Data;
        if (S->Rear == Top)
            S->Rear = S->Front;
        free(Top);
        return Data;
    }
}

int IsEmpty(Queue S) {
    return S->Rear == S->Front;
}