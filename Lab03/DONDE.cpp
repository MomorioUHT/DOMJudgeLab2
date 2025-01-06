#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// Merge function for Merge Sort
void merge(vector<int> &arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

// Merge Sort function
void mergeSort(vector<int> &arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Helper
vector<int> parseInputLine() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> result;
    int num;

    while (ss >> num) {
        result.push_back(num);
    }

    return result;
}

int maxSatisfiedChildren(vector<int> &m, vector<int> &n) {
    mergeSort(m, 0, m.size() - 1);
    mergeSort(n, 0, n.size() - 1);

    int i = 0, j = 0, satisfied = 0;

    // Use a greedy approach to distribute cookies
    while (i < m.size() && j < n.size()) {
        if (n[j] >= m[i]) {
            satisfied++;
            i++;
            j++;
        } else {
            j++;
        }
    }

    return satisfied;
}

int main() {
    vector<int> m = parseInputLine();
    vector<int> n = parseInputLine();

    int result = maxSatisfiedChildren(m, n);
    cout << result << endl;

    return 0;
}
