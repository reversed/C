class Solution {
public:
    bool is3x3valid(vector<vector<char>>& board, int row, int col)
    {
        int arr[10] = {0};
        for (int i = row; i < row + 3; ++i)
        {
            for (int j = col; j < col + 3; ++j)
            {
                if (board[i][j] == '.') continue;
                
                int val = board[i][j] - '0';
                if (arr[val] != 0)
                {
                    return false;   
                }
                else
                {
                    arr[val] += 1;
                }
            }
        }
        return true;
    }
    
    bool isValidSudoku(vector<vector<char>>& board) {
        // Is line valid?
        for (int i = 0; i < 9; ++i)
        {
            int arr[10] = {0};
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] == '.') continue;
                
                int val = board[i][j] - '0';
                if (arr[val] != 0)
                {
                    return false;   
                }
                else
                {
                    arr[val] += 1;
                }
            }
        }
        // Is column valid?
        for (int j = 0; j < 9; ++j)
        {
            int arr[10] = {0};
            for (int i = 0; i < 9; ++i)
            {
                if (board[i][j] == '.') continue;
                
                int val = board[i][j] - '0';
                if (arr[val] != 0)
                {
                    return false;   
                }
                else
                {
                    arr[val] += 1;
                }
            }
        }
        // Is 3x3 valid?
        for (int i = 0; i < 9; i += 3)
        {
            for (int j = 0; j < 9; j += 3)
            {
                if (!is3x3valid(board, i, j)) return false;
            }
        }
        
        return true;
    }
};


