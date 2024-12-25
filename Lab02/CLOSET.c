#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DISTANCE 1e9

typedef struct {
    double x;
    double y;
} Point;

// Calculate the distance between two points
double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double min(double a, double b) {
    return (a < b) ? a : b;
}

// Merge two halves of points array based on x
void mergeX(Point points[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Point L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = points[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = points[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].x <= R[j].x)
            points[k++] = L[i++];
        else
            points[k++] = R[j++];
    }

    while (i < n1)
        points[k++] = L[i++];
    while (j < n2)
        points[k++] = R[j++];
}

// Merge sort for points array based on x
void mergeSortX(Point points[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortX(points, left, mid);
        mergeSortX(points, mid + 1, right);
        mergeX(points, left, mid, right);
    }
}

// Merge two halves of points array based on y
void mergeY(Point points[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Point L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = points[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = points[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].y <= R[j].y)
            points[k++] = L[i++];
        else
            points[k++] = R[j++];
    }

    while (i < n1)
        points[k++] = L[i++];
    while (j < n2)
        points[k++] = R[j++];
}

// Merge sort for points array based on y
void mergeSortY(Point points[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortY(points, left, mid);
        mergeSortY(points, mid + 1, right);
        mergeY(points, left, mid, right);
    }
}

// Function to find the closest distance in a strip of points
double stripClosest(Point strip[], int size, double d) {
    double minDist = MAX_DISTANCE;
    mergeSortY(strip, 0, size - 1); // Sort strip according to y-coordinates

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minDist; ++j) {
            minDist = min(minDist, dist(strip[i], strip[j]));
        }
    }
    return minDist;
}

// Recursive function to find the closest distance
double closestRecursive(Point points[], int n) {
    if (n <= 3) {
        double minDist = 999999;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                minDist = min(minDist, dist(points[i], points[j]));
            }
        }
        return minDist;
    }

    int mid = n / 2;
    Point midPoint = points[mid];

    double dl = closestRecursive(points, mid);
    double dr = closestRecursive(points + mid, n - mid);

    double d = min(dl, dr);

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(points[i].x - midPoint.x) < d) {
            strip[j++] = points[i];
        }
    }

    return min(d, stripClosest(strip, j, d));
}

// Main Function of Closet
double closest(Point points[], int n) {
    mergeSortX(points, 0, n - 1);
    return closestRecursive(points, n);
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);

        if (n < 2) {
            printf("0.000000\n"); // Fewer than 2 points
            continue;
        }

        Point points[n];
        for (int i = 0; i < n; i++) {
            scanf(" (%lf, %lf)", &points[i].x, &points[i].y);
        }

        double result = closest(points, n);
        printf("%.6lf\n", result);
    }

    return 0;
}
