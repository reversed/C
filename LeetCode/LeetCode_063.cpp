class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int row = obstacleGrid.size();
        if (row == 0) return 0;
        int col = obstacleGrid[0].size();
        if (col == 0) return 0;
    
        vector<uint64_t> dp(col, 0);
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (obstacleGrid[i][j] == 1) 
                {
                    dp[j] = 0;
                }
                else if (i == 0)
                {
                    if (j == 0) dp[j] = 1;
                    else dp[j] = dp[j - 1];
                }
                else if (j != 0)
                {
                    dp[j] = dp[j] + dp[j - 1];               
                }
            }
        }
        return dp[col - 1];
    }
};

