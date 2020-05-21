#include <stdio.h>
#include <stdlib.h>

#define MIN -2147483648

typedef int ElementType;
typedef struct HeapStruct *MaxHeap;
struct HeapStruct{
    ElementType *Elements;
    int Size;
    int Capacity;
};

MaxHeap Create(int MaxSize);
int IsFull(MaxHeap MH);
int Insert(MaxHeap MH, ElementType X);
int Route(MaxHeap MH, int Pos);

int main()
{
    FILE *fp;
    fp = fopen("input1.txt", "r");
    int N, M;
    fscanf(fp, "%d %d\n", &N, &M);
    int *Elements = malloc(sizeof(ElementType) * N);
    int *Targets = malloc(sizeof(ElementType) * M);

    for (int i = 0; i < N; i++) {
        fscanf(fp, "%d ", &Elements[i]);
    }

    fscanf(fp, "\n");

    for (int i = 0; i < M; i++) {
        fscanf(fp, "%d ", &Targets[i]);
    }

    fclose(fp);

    MaxHeap MH = Create(N);
    for (int i = 0; i < N; i++) {
        Insert(MH, Elements[i]);
    }

    for (int i = 0; i < M; i++) {
        if (i != 0)
            printf("\n");
        Route(MH, Targets[i]);
    }

    return 0;
}

MaxHeap Create(int MaxSize) {
    MaxHeap MH = malloc(sizeof(struct HeapStruct));
    MH->Elements = malloc(sizeof(ElementType) * (MaxSize + 1));
    MH->Size = 0;
    MH->Capacity = MaxSize;
    MH->Elements[0] = MIN;

    return MH;
}

int IsFull(MaxHeap MH) {
    if (MH->Size == MH->Capacity)
        return 1;
    else
        return 0;
}

int Insert(MaxHeap MH, ElementType X) {
    if (IsFull(MH))
        return -1;
    
    int i = ++MH->Size;
    for (; MH->Elements[i / 2] > X; i /= 2) {
        MH->Elements[i] = MH->Elements[i / 2];
    }
    MH->Elements[i] = X;

    return 0;
}

int Route(MaxHeap MH, int Pos) {
    for (int i = Pos; i > 0; i /= 2) {
        if (i != Pos)
            printf(" ");
        printf("%d", MH->Elements[i]);
    }

    return 0;
}