#include <vector>
#include <queue>
#include <algorithm>

class Solution {
public:
    int minimumTime(int n, std::vector<std::vector<int>>& relations, std::vector<int>& time) {
        if (relations.empty()) {
            return *max_element(time.begin(), time.end());
        }

        std::vector<std::vector<int>> adjList(n + 1, std::vector<int>());
        std::vector<int> indegree(n + 1, 0);
        std::vector<int> maxCompletionTime(n + 1, 0);

        for (const auto& relation : relations) {
            int src = relation[0];
            int dst = relation[1];
            adjList[src].push_back(dst);
            ++indegree[dst];
        }

        std::queue<int> courseQueue;
        for (int i = 1; i <= n; ++i) {
            if (indegree[i] == 0) {
                courseQueue.emplace(i);
                maxCompletionTime[i] = time[i - 1];
            }
        }

        while (!courseQueue.empty()) {
            int src = courseQueue.front();
            courseQueue.pop();

            for (int dst : adjList[src]) {
                --indegree[dst];
                int curCompletionTime = maxCompletionTime[src] + time[dst - 1];
                maxCompletionTime[dst] = std::max(maxCompletionTime[dst], curCompletionTime);

                if (indegree[dst] == 0) {
                    courseQueue.emplace(dst);
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            if (indegree[i] > 0) {
                return -1;
            }
        }

        return *max_element(maxCompletionTime.begin(), maxCompletionTime.end());
    }
};
