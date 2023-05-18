class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();

        vector <vector <int>> cell(r, vector <int>(c, -1));
        queue <pair<int, int>> bfs;

        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                if (grid[i][j] == 1) {
                    cell[i][j] = 0;
                    bfs.push({ i, j });
                }

        int distance = 1;
        while (not bfs.empty()) {
            int len = bfs.size();
            for (int k = 0; k < len; k++) {
                pair <int, int> curr = bfs.front(); bfs.pop();
                int i = curr.first, j = curr.second;
                if (i > 0 and cell[i - 1][j] == -1) {
                    cell[i - 1][j] = distance;
                    bfs.push({ i - 1, j });
                }
                if (j > 0 and cell[i][j - 1] == -1) {
                    cell[i][j - 1] = distance;
                    bfs.push({ i, j - 1 });
                }
                if (i < r - 1 and cell[i + 1][j] == -1) {
                    cell[i + 1][j] = distance;
                    bfs.push({ i + 1, j });
                }
                if (j < c - 1 and cell[i][j + 1] == -1) {
                    cell[i][j + 1] = distance;
                    bfs.push({ i, j + 1 });
                }
            }
            distance++;
        }

        int m = INT_MIN;
        for (auto v : cell)
            for (int i : v)
                if (i > m)
                    m = i;

        if (not m)
            return -1;
        return m;
    }
};
