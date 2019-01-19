class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int row = matrix.size();
        if (row == 0) return;
        int col = matrix[0].size();
        
        for (int i = 0; i < row / 2; ++i)
        {
            matrix[i].swap(matrix[row - i - 1]);
        }
        for (int i = 0; i < row; ++i)
        {
            for (int j = i + 1; j < col; ++j)
            {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
};

