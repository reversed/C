class Solution {
public:
    bool dfs(vector<vector<char>>& board, vector<vector<bool>>& map, int x, int y, string& word)
    {
        if (word.empty()) return true;

        if (x >= board.size() || x < 0) return false;
        if (y >= board[0].size() || y < 0) return false;
        if (map[x][y] == true) return false;
        
        char c = word.back();
        if (board[x][y] != c) return false;
  
        map[x][y] = true;
        word.pop_back();
        vector<pair<int, int>> step { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        for (auto p : step)
        {
            int tx = p.first + x;
            int ty = p.second + y;
            if (dfs(board, map, tx, ty, word)) return true;
        }
        map[x][y] = false;
        word.push_back(c);
        
        return false;
    }
    
    bool exist(vector<vector<char>>& board, string word) {
        if (word.empty()) return true;
        int row = board.size();
        if (row == 0) return false;
        int col = board[0].size();
        
        reverse(word.begin(), word.end());
        
        vector<vector<bool>> access_map(row, vector(col, false));
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (dfs(board, access_map, i, j, word)) return true;
            }
        }
        return false;
    }
};

