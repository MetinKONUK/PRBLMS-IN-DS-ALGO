class Solution {
public:
    struct hasher {
        template <typename T1, typename T2>
        auto operator()(const pair<T1, T2> &pair) const -> size_t {
            return hash<T1>{}(pair.first) ^ hash<T2>{}(pair.second);
        }
    };
    bool isPathCrossing(string path) {
        int x = 0, y = 0;
        unordered_set<pair<int, int>, hasher> crossed;
        for (char ch : path) {
            crossed.insert({x, y});
            if (ch == 'E')
                x++;
            else if (ch == 'W')
                x--;
            else if (ch == 'N')
                y++;
            else
                y--;
            if (crossed.find({ x, y }) != crossed.end())
                return true;
        }
        return false;
    }
};