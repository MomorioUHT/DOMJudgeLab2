#include <stdio.h>
#include <stdlib.h>

// Structure to store each elf's data
typedef struct {
    int time;
    int costPerMinute;
    double costEffectiveness;
} Elf;

// Merge function for merge sort
void merge(Elf arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Elf L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].costEffectiveness >= R[j].costEffectiveness)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Merge sort function
void mergeSort(Elf arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Elf elves[n];

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &elves[i].time, &elves[i].costPerMinute);
        elves[i].costEffectiveness = (double)elves[i].costPerMinute / elves[i].time;
    }

    // Sort elves by cost-effectiveness
    mergeSort(elves, 0, n - 1);

    // Greedy assignment
    int totalTime = 0;
    long long totalCost = 0;

    for (int i = 0; i < n; i++) {
        totalCost += (long long)totalTime * elves[i].costPerMinute;
        totalTime += elves[i].time;
    }

    // Output the result
    printf("%lld\n", totalCost);

    return 0;
}
