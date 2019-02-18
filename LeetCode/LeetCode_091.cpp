class Solution {
public:
    int numDecodings(string s) {
        int len = s.size();
        if (len == 0) return 0;
        if (s[0] - '0' == 0) return 0;
        
        vector<int> dp(len+1, 0);
        dp[0] = 1; dp[1] = 1;
        for (int i = 1; i < len; ++i)
        {
            int cur = s[i] - '0';
            int pre = s[i-1] - '0';
            
            if ((pre == 0 || pre > 2) && cur == 0)
            {
                return 0;
            }
            else if (cur == 0)
            {
                dp[i+1] = dp[i-1];
            }
            else if (pre == 1)
            {
                dp[i+1] = dp[i] + dp[i-1];
            }
            else if (pre == 2 && cur <= 6)
            {
                dp[i+1] = dp[i] + dp[i-1];
            }
            else
            {
                dp[i+1] = dp[i];
            }
        }
        return dp[len];
    }
};

