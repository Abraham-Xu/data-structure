#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000

typedef int ElementType;
typedef int SetName;
typedef ElementType SetType[MAX_SIZE];

void Init(SetType S);
void Connect(SetType S, ElementType X1, ElementType X2);
void Check(SetType S, ElementType X1, ElementType X2);
void Stat(SetType S, int N);

SetName Find(SetType S, ElementType X);
void Union(SetType S, SetName Root1, SetName Root2);

int main()
{
    FILE *fp;
    fp = fopen("input2.txt", "r");
    int N;
    fscanf(fp, "%d\n", &N);
    SetType Set;
    Init(Set);

    char Op;
    int Nodes[2];

    do {  
        fscanf(fp, "%c ", &Op);
        int X1, X2;
    
        switch (Op) {
            case 'I':
                        fscanf(fp, "%d %d\n", &X1, &X2);
                        Connect(Set, X1, X2);
                        break;
            case 'C':   
                        fscanf(fp, "%d %d\n", &X1, &X2);
                        Check(Set, X1, X2);
                        break;
            case 'S':
                        Stat(Set, N);
                        break;
            default:    break;
        } 

    } while (Op != 'S');

    fclose(fp);

    return 0;
}

void Init(SetType S) {
    for (int i = 0; i < MAX_SIZE; i++) {
        S[i] = -1;
    }
    return;
}

void Connect(SetType S, ElementType X1, ElementType X2) {
    SetName Root1, Root2;
    Root1 = Find(S, X1 - 1);
    Root2 = Find(S, X2 - 1);
    if (Root1 != Root2)
        Union(S, Root1, Root2);
    return;
}

SetName Find(SetType S, ElementType X) {
    //for (; S[X] > -1; X = S[X]);
    if (S[X] < 0)
        return X;
    else
        return S[X] = Find(S, S[X]);
    //return X;
}

void Union(SetType S, SetName Root1, SetName Root2) {
    if (S[Root1] < S[Root2]) {
        S[Root2] = Root1;
        S[Root1] -= S[Root2];
    } else {
        S[Root1] = Root2;
        S[Root2] -= S[Root1];
    }
    //S[Root2] = Root1;
    return;
}

void Check(SetType S, ElementType X1, ElementType X2) {
    SetName Root1, Root2;
    Root1 = Find(S, X1 - 1);
    Root2 = Find(S, X2 - 1);
    if (Root1 == Root2)
        printf("yes\n");
    else
        printf("no\n");
    return;
}

void Stat(SetType S, int N) {
    int GroupCnt = 0;
    for (int i = 0; i < N; i++) {
        if (S[i] < 0)
            GroupCnt++;
    }

    if (GroupCnt == 1)
        printf("The network is connected.");
    else
        printf("There are %d components.", GroupCnt);
    return;    
}