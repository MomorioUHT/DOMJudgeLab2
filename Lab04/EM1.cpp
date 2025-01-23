#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Cell {
    int x, y, cost;
    bool operator>(const Cell& other) const {
        return cost > other.cost;
    }
};

int findMinCost(vector<vector<int>>& grid, int rows, int cols) {
    // Direction vectors for moving up, down, left, and right
    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {1, 0, -1, 0};

    // Min-cost matrix to store the minimum cost to reach each cell
    vector<vector<int>> minCost(rows, vector<int>(cols, INT_MAX));
    minCost[0][0] = grid[0][0];

    // Min-heap priority queue for efficiently finding the next cell to process
    priority_queue<Cell, vector<Cell>, greater<Cell>> pq;
    pq.push({0, 0, grid[0][0]});

    while (!pq.empty()) {
        Cell current = pq.top();
        pq.pop();

        int cx = current.x, cy = current.y;

        // Skip if this cell has already been processed with a smaller cost
        if (current.cost > minCost[cx][cy]) {
            continue;
        }

        // Update the cost of neighboring cells
        for (int d = 0; d < 4; ++d) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                int newCost = minCost[cx][cy] + grid[nx][ny];
                if (newCost < minCost[nx][ny]) {
                    minCost[nx][ny] = newCost;
                    pq.push({nx, ny, newCost});
                }
            }
        }
    }

    return minCost[rows - 1][cols - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numRooms;
    cin >> numRooms;

    while (numRooms--) {
        int rows, cols;
        cin >> rows >> cols;

        vector<vector<int>> grid(rows, vector<int>(cols));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cin >> grid[i][j];
            }
        }

        cout << findMinCost(grid, rows, cols) << "\n";
    }

    return 0;
}