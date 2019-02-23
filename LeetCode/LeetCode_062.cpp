class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 0 || n == 0) return 0;
        vector<vector<uint64_t>> c(m+1, vector<uint64_t>(n+1, 0));
        c[1][1] = 1;
        
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (c[i][j] == 0) c[i][j] = c[i-1][j] + c[i][j-1];
            }
        }
        return c[m][n];
    }
};

