class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int targetId, int level) {
        unordered_map<string, int> videoFreq;
        vector<bool> visited(friends.size(), false);
        queue<int> friendQueue;
        friendQueue.push(targetId);
        visited[targetId] = true;

        while (!friendQueue.empty() && level-- > 0) {
            int queueSize = friendQueue.size();
            for (int i = 0; i < queueSize; i++) {
                int currentFriend = friendQueue.front();
                friendQueue.pop();
                for (int friendId : friends[currentFriend]) {
                    if (!visited[friendId]) {
                        friendQueue.push(friendId);
                        visited[friendId] = true;
                    }
                }
            }
        }

        while (!friendQueue.empty()) {
            int currentFriend = friendQueue.front();
            friendQueue.pop();
            for (string& video : watchedVideos[currentFriend]) {
                videoFreq[video]++;
            }
        }

        vector<pair<int, string>> freqPairs;
        for (auto& pair : videoFreq) {
            freqPairs.push_back({ pair.second, pair.first });
        }

        sort(freqPairs.begin(), freqPairs.end());

        vector<string> result;
        for (auto& pair : freqPairs) {
            result.push_back(pair.second);
        }

        return result;
    }
};
