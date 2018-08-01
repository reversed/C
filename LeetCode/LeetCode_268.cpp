class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sz = nums.size() + 1;
        int sum = sz * (sz - 1) / 2;
        int sum2 = accumulate(nums.cbegin(), nums.cend(), 0);
        return sum - sum2;
    }
};
