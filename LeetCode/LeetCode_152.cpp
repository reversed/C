class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int len = nums.size();
        if (len == 0) return 0;
        
        vector<int> dp(len, 0);
        dp[0] = nums[0];
        for (int i = 1; i < len; ++i)
        {
            int max = dp[i-1];
            int cur = 1;
            for (int j = i; j >= 0; --j)
            {
                cur = nums[j] * cur;
                if (cur > max) max = cur;
            }
            dp[i] = max;
        }
        
        return dp[len-1];
    }
};
