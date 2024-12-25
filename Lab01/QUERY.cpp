#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

struct Item {
    string name;
    double price;
};

string toLowerCase(string str) {
    string result;
    for (char x: str) {
        result += towlower(x);
    }
    return result;
}

void merge(vector<Item>& results, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Item> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; ++i)
        leftArr[i] = results[left + i];
    for (int j = 0; j < n2; ++j)
        rightArr[j] = results[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].price <= rightArr[j].price) {
            results[k] = leftArr[i];
            ++i;
        } else {
            results[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        results[k] = leftArr[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        results[k] = rightArr[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<Item>& results, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(results, left, mid);
        mergeSort(results, mid + 1, right);

        merge(results, left, mid, right);
    }
}

int main() {
    int n;
    cin >> n;

    vector<Item> items(n);

    for (int i = 0; i < n; ++i) {
        cin >> items[i].name >> items[i].price;
    }

    string query;
    cin >> query; 
    query = toLowerCase(query);

    bool found = false;
    vector<Item> results;

    for (Item item : items) {
        if (toLowerCase(item.name).find(query) != string::npos) { 
            results.push_back(item);
            found = true;
        }
    }

    if (found) {
        //Use mergesort
        mergeSort(results, 0, results.size() - 1);

        for (Item item : results) {
            printf("%s %.2f\n", item.name.c_str(), item.price);
        }
    } else {
        cout << "-- NONE --" << endl;
    }

    return 0;
}