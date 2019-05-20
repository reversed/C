class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int row = board.size();
        if (row == 0) return;
        int col = board[0].size();
        
        vector<pair<int, int>> step = { {-1, -1}, {-1, 0}, {-1, 1},
                                        {0 , -1},          {0 , 1},
                                        {1 , -1}, {1 , 0}, {1 , 1},
                                      };
        
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                int cnt = 0;
                
                for (auto p : step) {
                    int x = i + p.first;
                    int y = j + p.second;
                    
                    if (x < 0 || y < 0 || x >= row || y >=col) continue;
                    cnt += board[x][y] & 0x1;
                }
                
                if (board[i][j] == 1 && (cnt == 2 || cnt == 3)) board[i][j] |= 0x2;
                if (board[i][j] == 0 && cnt == 3) board[i][j] |= 0x2;
            }
        }
        
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                board[i][j] >>= 1;
            }
        }
    }
};

