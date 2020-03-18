#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

//List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
//Position BinarySearch( List L, ElementType X );
Position BinarySearch( List L, ElementType X ) {
    int m = (L->Last - 1) / 2 + 1;
    int r = L->Last;
    int l = 1;
    
    while (!((L->Data[l] < X) && (L->Data[r] > X) && (r - l == 1))) {
        if (X > L->Data[m]) {
            l = m;
            m = (r - m - 1) / 2 + 1 + m;
        } else if (X < L->Data[m]) {
            r = m;
            m = (m - l - 1) / 2 + l;
        } else {
            return m;
        }
    }
    return NotFound;
}

int main()
{
    List L;
    ElementType X;
    Position P;

    L = (List)malloc(sizeof(struct LNode));
    L->Last = 5;
    L->Data[1] = 12;
    L->Data[2] = 31;
    L->Data[3] = 55;
    L->Data[4] = 89; 
    L->Data[5] = 101;

    //scanf("%d", &X);
    X = 31;
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}
