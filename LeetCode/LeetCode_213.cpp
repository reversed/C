class Solution {
public:
    int rob2(vector<int>& nums, int st, int ed)
    {
        if (st > ed) return 0;
        if (ed < 0) return 0;
        
        int len = ed - st + 1;
        if (len == 1) return nums[st];
        
        vector<int> dp(len);
        dp[0] = nums[st];
        dp[1] = max(nums[st], nums[st+1]);
        for (int i = 2; i < len; ++i)
        {
            dp[i] = max(dp[i-1], dp[i-2] + nums[st+i]);
        }
        return dp[len-1];
    }
    
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        int val1 = rob2(nums, 1, nums.size() - 1);
        int val2 = rob2(nums, 2, nums.size() - 2) + nums[0];
        return max(val1, val2);
    }
};

