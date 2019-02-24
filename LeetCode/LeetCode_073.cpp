class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int row = matrix.size();
        if (row == 0) return;
        int col = matrix[0].size();
        if (col == 0) return;
        
        // col0 and row0
        bool col0 = false;
        for (int i = 0; i < row; ++i)
        {
            if (matrix[i][0] == 0)
            {
                col0 = true;
                break;
            }
        }
        bool row0 = false;
        for (int i = 0; i < col; ++i)
        {
            if (matrix[0][i] == 0)
            {
                row0 = true;
                break;
            }
        }
        
        // not include row 0 / col 0
        for (int i = 1; i < row; ++i)
        {
            for (int j = 1; j < col; ++j)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }
        
        // not include col 0
        for (int i = 1; i < row; ++i)
        {
            if (matrix[i][0] == 0)
            {
                for (int j = 1; j < col; ++j)
                {
                    matrix[i][j] = 0;
                }
            }
        }
        
        // not include row 0
        for (int j = 1; j < col; ++j)
        {
            if (matrix[0][j] == 0)
            {
                for (int i = 1; i < row; ++i)
                {
                    matrix[i][j] = 0;
                }
            }
        }

        // col0 and row0
        if (row0 == true)
        {
            for (int i = 0; i < col; ++i) matrix[0][i] = 0;
        }
        
        if (col0 == true)
        {
            for (int i = 0; i < row; ++i) matrix[i][0] = 0;
        }
        
        return;
    }
};
