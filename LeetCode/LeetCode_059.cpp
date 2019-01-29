class Solution {
public:
    void foo(vector<vector<int>> &v, int row1, int row2, int col1, int col2, int val)
    {
        if (row1 == row2 || col1 == col2)
        {
            v[row1][col1] = val;
            return;
        }
        if (row1 > row2 || col1 > col2) return;
        
        for (int i = col1; i <= col2; ++i) v[row1][i] = val++;
        for (int i = row1 + 1; i <= row2 - 1; ++i) v[i][col2] = val++;     
        for (int i = col2; i >= col1; --i) v[row2][i] = val++;     
        for (int i = row2 - 1; i >= row1 + 1; --i) v[i][col1] = val++;
        
        return foo(v, row1+1, row2-1, col1+1, col2-1, val);
    }
    
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res;
        
        for (int i = 0; i < n; ++i)
        {
            vector<int> tmp(n, 0);
            res.push_back(tmp);
        }
        
        foo(res, 0, n-1, 0, n-1, 1);     
        
        return res;
    }
};

