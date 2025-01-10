#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double start;
    double end;
} Sprinkler;

void merge(Sprinkler arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Sprinkler *L = (Sprinkler *)malloc(n1 * sizeof(Sprinkler));
    Sprinkler *R = (Sprinkler *)malloc(n2 * sizeof(Sprinkler));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].start <= R[j].start) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(Sprinkler arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int findMinSprinklers(double l, double w, int n, double positions[][2]) {
    Sprinkler *sp = (Sprinkler *)malloc(n * sizeof(Sprinkler));
    int spCount = 0;
    double half = w / 2.0;

    for (int i = 0; i < n; ++i) {
        double x = positions[i][0];
        double r = positions[i][1];

        if (r <= half)
            continue;

        double dx = sqrt(r * r - half * half);
        double start = fmax(0.0, x - dx);
        double end = fmin(l, x + dx);

        sp[spCount].start = start;
        sp[spCount].end = end;
        spCount++;
    }

    mergeSort(sp, 0, spCount - 1);

    double covered = 0.0;
    int usedSp = 0;
    int i = 0;

    while (covered < l) {
        double furthest = covered;

        while (i < spCount && sp[i].start <= covered) {
            furthest = fmax(furthest, sp[i].end);
            i++;
        }

        if (furthest == covered) {
            free(sp);
            return -1;
        }

        covered = furthest;
        usedSp++;
    }

    free(sp);
    return usedSp;
}

int main() {
    double l, w;

    while (scanf("%lf %lf", &l, &w) == 2) {
        int n;
        scanf("%d", &n);

        double positions[n][2];
        for (int i = 0; i < n; ++i) {
            scanf("%lf %lf", &positions[i][0], &positions[i][1]);
        }

        int result = findMinSprinklers(l, w, n, positions);
        printf("%d\n", result);
    }

    return 0;
}