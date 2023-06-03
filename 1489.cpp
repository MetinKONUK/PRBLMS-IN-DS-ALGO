class DisjointSet {
private:
    vector<int> parent;
    vector<int> size;
    int components;

public:
    DisjointSet(int n) : parent(n + 1), size(n + 1), components(n) {
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unionSets(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py)
            return false;

        if (size[px] > size[py]) {
            parent[py] = px;
            size[px] += size[py];
        }
        else {
            parent[px] = py;
            size[py] += size[px];
        }
        components--;
        return true;
    }

    bool isConnected() {
        return components == 1;
    }
};

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int edgeCount = edges.size();
        int edgeLen = edges[0].size();

        vector<vector<int>> indexedEdges(edgeCount, vector<int>(edgeLen + 1));

        for (int i = 0; i < edgeCount; i++) {
            copy(edges[i].begin(), edges[i].end(), indexedEdges[i].begin());
            indexedEdges[i][3] = i;
        }

        sort(indexedEdges.begin(), indexedEdges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });

        DisjointSet ds(n);
        int minCost = calculateMSTCost(indexedEdges, ds, -1);

        vector<vector<int>> ans(2);

        for (int i = 0; i < 2; i++)
            ans[i] = {};

        for (const vector<int>& edge : indexedEdges) {
            int from = edge[0], to = edge[1], weight = edge[2], index = edge[3];

            DisjointSet dsCopy(n);
            int excludedMSTCost = calculateMSTCost(indexedEdges, dsCopy, index);

            if (!dsCopy.isConnected() || excludedMSTCost > minCost) {
                ans[0].push_back(index);
                continue;
            }

            dsCopy = DisjointSet(n);
            dsCopy.unionSets(from, to);
            int includedMSTCost = weight;
            includedMSTCost += calculateMSTCost(indexedEdges, dsCopy, index);

            if (includedMSTCost == minCost) {
                ans[1].push_back(index);
            }
        }
        return ans;
    }

    int calculateMSTCost(vector<vector<int>>& edges, DisjointSet& ds, int exEdgeIndex) {
        int mstCost = 0;
        for (const vector<int>& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2], i = edge[3];
            if (exEdgeIndex != i && ds.unionSets(u, v)) {
                mstCost += w;
            }
        }
        return mstCost;
    }
};
