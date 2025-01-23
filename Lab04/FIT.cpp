#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight > other.weight; // For min-heap based on weight
    }
};

int findParent(vector<int>& parent, int node) {
    if (parent[node] == node)
        return node;
    return parent[node] = findParent(parent, parent[node]);
}

void unionSets(vector<int>& parent, vector<int>& rank, int u, int v) {
    int rootU = findParent(parent, u);
    int rootV = findParent(parent, v);
    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

int main() {
    while (true) {
        int v, e;
        cin >> v >> e;
        if (v == 0 && e == 0)
            break;

        priority_queue<Edge> pq;
        int totalWeight = 0;

        for (int i = 0; i < e; i++) {
            int u, v, weight;
            cin >> u >> v >> weight;
            pq.push({u, v, weight});
            totalWeight += weight; // Sum of all edge weights
        }

        vector<int> parent(v);
        vector<int> rank(v, 0);
        for (int i = 0; i < v; i++) {
            parent[i] = i;
        }

        int mstWeight = 0;
        int edgeCount = 0;

        // Process edges in ascending order of weights
        while (!pq.empty() && edgeCount < v - 1) {
            Edge edge = pq.top();
            pq.pop();

            if (findParent(parent, edge.u) != findParent(parent, edge.v)) {
                unionSets(parent, rank, edge.u, edge.v);
                mstWeight += edge.weight;
                edgeCount++;
            }
        }

        cout << totalWeight - mstWeight << endl;
    }

    return 0;
}
