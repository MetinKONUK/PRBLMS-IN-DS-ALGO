class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int N = nums.size();
        int left_sum = 0, right_sum = 0;
        for (int i = 1; i < N; ++i)
            right_sum += nums[i];

        for (int index = 0; index < N; ++index) {
            if (left_sum == right_sum)
                return index;
            right_sum -= index+1 < N ? nums[index + 1] : 0;
            left_sum += nums[index];
        }
        return -1;
    }
};