#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int temp[], int left, int mid, int right, long long int *inversionCount) {
    int i = left, j = mid + 1, k = left;
    
    while (i <= mid && j <= right) {
        if (arr[i] >= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            (*inversionCount) += (mid - i + 1);
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

void mergeSort(int arr[], int temp[], int left, int right, long long int *inversionCount) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, temp, left, mid, inversionCount);
        mergeSort(arr, temp, mid + 1, right, inversionCount);

        merge(arr, temp, left, mid, right, inversionCount);
    }
}

int main() {
    int n;

    // Read input until EOF
    while (scanf("%d", &n) != EOF) {
        int *arr = (int *)malloc(n * sizeof(int));
        int *temp = (int *)malloc(n * sizeof(int));
        long long int inversionCount = 0;

        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        mergeSort(arr, temp, 0, n - 1, &inversionCount);

        printf("%lld\n", inversionCount);

        free(arr);
        free(temp);
    }

    return 0;
}
