class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;
        if (grid[0].empty()) return 0;
        
        int row = grid.size();
        int col = grid[0].size();
        vector<int> dp(col, 0);
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (i == 0 && j == 0)
                {
                    dp[j] = grid[i][j];
                }
                else if (i == 0)
                {
                    dp[j] = grid[i][j] + dp[j-1];
                }
                else if (j == 0)
                {
                    dp[j] = grid[i][j] + dp[j];
                }
                else
                {
                    dp[j] = grid[i][j] + min(dp[j], dp[j-1]);
                }
            }
        }
        return dp[col-1];
    }
};

