#include<stdio.h>
#include<stdlib.h>

int main() {
    /*int k = 0;
    scanf("%d\n", &k);
    int* a = (int*)malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &a[i]);
    }*/

    int k = 10;
    int a[10] = {-4, -1, -2, -2, -2, -2, -2, -2, -2, -1};

    int sum = 0;
    int max_sum = -1;

    int left_index = 0;
    int right_index = k - 1;

    int temp_left_index = 0;

    for (int i = 0; i < k; i++) {
        sum += a[i];
        if (sum > max_sum) {
            max_sum = sum;
            left_index = temp_left_index;
            right_index = i;
        } else if (sum < 0) {
            sum = 0;
            temp_left_index = i + 1;
        }
    }

    if (max_sum == -1)
        max_sum = 0;

    printf("%d %d %d", max_sum, a[left_index], a[right_index]);

    return 0;
}