#include<stdio.h>
#include<stdlib.h>

int find_max_sum (int* a, int n) {
    if (n == 0)
        return 0;

    int n_right = (n - 1) / 2 + 1;

    int left_max = 0;
    int right_max = 0;

    if (n == 1) {
        return a[0];
    } else if (n == 2) {
        left_max = a[0];
        right_max = a[1];
    } else {
        left_max = find_max_sum(&a[0], n_right);
        right_max = find_max_sum(&a[n_right], n - n_right);
    }

    int left_sum = 0;
    int left_sum_max = 0;

    for (int i = n_right - 1; i >= 0; i--) {
        left_sum += a[i];
        if (left_sum > left_sum_max)
            left_sum_max = left_sum;
    }

    int right_sum = 0;    
    int right_sum_max = 0;

    for (int i = n_right; i < n; i++) {
        right_sum += a[i];
        if(right_sum > right_sum_max)
            right_sum_max = right_sum;
    }

    int cross_max = left_sum_max + right_sum_max;

    int side_max = left_max > right_max ? left_max : right_max;

    return cross_max > side_max ? cross_max : side_max;
}

int main() {
    /*int k = 0;
    scanf("%d\n", &k);
    int* a = (int*)malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &a[i]);
    }*/

    int k = 10;
    int array[10] = {-10, 1, 2, 3, 4, -5, -23, 3, 7, -21};

    int sum = 0;
    int max_sum = -1;

    int left_index = 0;
    int right_index = k - 1;

    max_sum = find_max_sum(array, k);

    if (max_sum < 0)
        max_sum = 0;

    //printf("%d %d %d", max_sum, a[left_index], a[right_index]);
    printf("Max_sum = %d\n", max_sum);

    return 0;
}