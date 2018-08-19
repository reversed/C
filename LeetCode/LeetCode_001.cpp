class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        int sz = nums.size();
        for (int i = 0; i < sz - 1; ++i)
        {
            for (int j = i + 1; j < sz; ++j)
            {
                if (nums[i] + nums[j] == target)
                {
                    res.push_back(i);
                    res.push_back(j);
                    return res;
                }
            }
        }
        return res;
    }
};

