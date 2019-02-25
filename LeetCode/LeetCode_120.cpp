class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int row = triangle.size();
        if (row == 0) return 0;
        
        vector<int> dp(row, 0);
        for (int i = 0; i < row; ++i)
        {
            int pre = dp[0];
            for (int j = 0; j < i+1; ++j)
            {
                if (j == 0) 
                {
                    dp[j] = dp[j] + triangle[i][j];
                }
                else if (j == i)
                {
                    dp[j] = pre + triangle[i][j];
                }
                else
                {
                    int tmp = dp[j];
                    dp[j] = min(dp[j] + triangle[i][j], pre + triangle[i][j]);
                    pre = tmp;
                }
            }
        }
   
        int res = INT_MAX;
        for (int i = 0; i < row; ++i)
        {
            if (dp[i] < res) res = dp[i];
        }
        return res;
    }
};
