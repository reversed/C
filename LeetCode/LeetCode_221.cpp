class Solution {
public:
    bool squareAt(vector<vector<char>>& matrix, int x, int y, int rank)
    {
        if (x - rank + 1 < 0) return false;
        if (y - rank + 1 < 0) return false;
        
        for (int i = x; i > x - rank; --i)
        {
            for (int j = y; j > y - rank; --j)
            {
                if (matrix[i][j] != '1') return false;
            }
        }
        return true;
    }
    
    int maximalSquare(vector<vector<char>>& matrix) {
        int row = matrix.size();
        if (row == 0) return 0;
        int col = matrix[0].size();
        if (col == 0) return 0;
        
        vector<vector<int>> dp(row, vector<int>(col, 0));
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (i == 0 && j == 0) { dp[i][j] = matrix[i][j] - '0'; continue; }
                if (i == 0) { dp[i][j] = max(dp[i][j-1], matrix[i][j] - '0'); continue; }
                if (j == 0) { dp[i][j] = max(dp[i-1][j], matrix[i][j] - '0'); continue; }
                
                int val = max(dp[i-1][j], dp[i][j-1]);
                if (matrix[i][j] == '0')
                {
                   dp[i][j] = val; 
                }
                else
                {
                    if (squareAt(matrix, i, j, val + 1))
                    {
                        dp[i][j] = val + 1;
                    }
                    else
                    {
                        dp[i][j] = val;
                    }
                }
            }
        }
        
        return dp[row-1][col-1] * dp[row-1][col-1];
    }
};

