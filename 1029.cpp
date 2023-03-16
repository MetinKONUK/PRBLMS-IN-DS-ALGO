class Solution {
public:
int twoCitySchedCost(vector<vector<int>>& costs) {
	vector<int> cost_all_b;
	for (vector<int> cost : costs) {
		cost_all_b.push_back(cost[1] - cost[0]);
	}
	vector<int> I(cost_all_b.size());
	for (int i = 0; i < cost_all_b.size(); ++i) {
		I[i] = i;
	}
	sort(I.begin(), I.end(), [&](int one, int two) {
		return cost_all_b[one] < cost_all_b[two];
		});
	int result = 0;
	int i = cost_all_b.size() / 2;
	for (int j = 0; j < i; ++j) {
		result += costs[I[j]][1];
	}
	for (i; i < cost_all_b.size(); ++i) {
		result += costs[I[i]][0];
	}
	return result;
}
};