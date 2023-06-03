class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> parent(n + 1, -1);

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            if (find(u, parent) == find(v, parent))
                return edge;

            Union(u, v, parent);
        }

        return {};
    }

    int find(int x, vector<int>& parent) {
        if (parent[x] == -1)
            return x;
        return parent[x] = find(parent[x], parent);
    }

    void Union(int x, int y, vector<int>& parent) {
        int s1 = find(x, parent);
        int s2 = find(y, parent);

        if (s1 != s2)
            parent[s1] = s2;
    }
};
