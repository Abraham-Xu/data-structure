#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void ListComponentsDFS(int **G, int N, int *Visited);
void ListComponentsBFS(int **G, int N, int *Visited);
void DFS(int **G, int N, int S, int *V);
void BFS(int **G, int N, int S, int *V);

int main()
{
    FILE *fp;
    fp = fopen("input1.txt", "r");
    int N, E;
    fscanf(fp, "%d %d\n", &N, &E);
    int **Graph = malloc(sizeof(int*) * N);

    for (int i = 0; i < N; i++) {
        Graph[i] = calloc(N, sizeof(int));
    }

    int Node1, Node2;
    for (int i = 0; i < E; i++) {
        fscanf(fp, "%d %d\n", &Node1, &Node2);
        Graph[Node1][Node2] = 1;
        Graph[Node2][Node1] = 1;
    }

    fclose(fp);

    int *Visited = calloc(N, sizeof(int));
    ListComponentsDFS(Graph, N, Visited);
    Visited = memset(Visited, 0, sizeof(int) * N);
    ListComponentsBFS(Graph, N, Visited);

    /*Queue Q = CreateQueue();
    Push(Q, 1);
    Push(Q, 2);
    Push(Q, 3);
    Pop(Q);*/

    return 0;
}

void ListComponentsDFS(int **G, int N, int *Visited) {
    for (int i = 0; i < N; i++) {
        if (!Visited[i]) {
            printf("{ ");
            DFS(G, N, i, Visited);
            printf("}\n");
        }
    }
}

void ListComponentsBFS(int **G, int N, int *Visited) {
    for (int i = 0; i < N; i++) {
        if (!Visited[i]) {
            printf("{ ");
            BFS(G, N, i, Visited);
            printf("}\n");
        }
    }
}

void DFS(int **G, int N, int S, int *V) {
    printf("%d ", S);
    V[S] = 1;
    for (int i = 0; i < N; i++) {
        if (G[S][i] && !V[i]) {
            DFS(G, N, i, V);
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