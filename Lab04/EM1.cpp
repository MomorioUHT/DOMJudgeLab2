#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int findMinCost(vector<vector<int>>& grid, int rows, int cols) {
    // Direction vectors for moving up, down, left, and right
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    // Min-cost matrix to store the minimum cost to reach each cell
    vector<vector<int>> minCost(rows, vector<int>(cols, INT_MAX));
    minCost[0][0] = grid[0][0];

    // Visited array to keep track of processed cells
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    while (true) {
        // Find the cell with the minimum cost that has not been visited
        int minVal = INT_MAX;
        int cx = -1, cy = -1;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!visited[i][j] && minCost[i][j] < minVal) {
                    minVal = minCost[i][j];
                    cx = i;
                    cy = j;
                }
            }
        }

        // If no such cell is found, break (all cells are visited)
        if (cx == -1 && cy == -1) {
            break;
        }

        // Mark the cell as visited
        visited[cx][cy] = true;

        // Update the cost of neighboring cells
        for (int d = 0; d < 4; ++d) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                if (!visited[nx][ny] && minCost[cx][cy] + grid[nx][ny] < minCost[nx][ny]) {
                    minCost[nx][ny] = minCost[cx][cy] + grid[nx][ny];
                }
            }
        }
    }

    return minCost[rows - 1][cols - 1];
}

int main() {
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

        cout << findMinCost(grid, rows, cols) << endl;
    }

    return 0;
}