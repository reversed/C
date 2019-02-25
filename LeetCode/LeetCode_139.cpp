class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int len = s.size();
        vector<bool> dp(len, false);
        
        for (int i = 0; i < len; ++i)
        {
            int cur = i;
            while (cur >= 0)
            {
                --cur;
                if (cur >= 0 && dp[cur] == false) continue;
                
                string sc = s.substr(cur + 1, i - (cur + 1) + 1);
                if (wordDict.end() != find(wordDict.begin(), wordDict.end(), sc))
                {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[len-1];
    }
};

