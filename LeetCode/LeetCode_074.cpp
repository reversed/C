class Solution {
public:
    int searchRow(vector<vector<int>>& matrix, int target)
    {
        int st = 0;
        int ed = matrix.size() - 1;
        
        while (st < ed)
        {
            int mid = st + (ed - st) / 2;
            if (matrix[mid][0] == target) return mid;
            else if (matrix[mid][0] < target) st = mid + 1;
            else ed = mid - 1;
        }
        return (matrix[st][0] > target) ? (st - 1) : st;
    }
    
    bool searchCol(vector<vector<int>>& matrix, int row, int target)
    {
        if (row < 0 || row > matrix.size()) return false;
        int st = 0;
        int ed = matrix[row].size() - 1;
        
        while (st < ed)
        {
            int mid = st + (ed - st) / 2;
            if (matrix[row][mid] == target) return true;
            else if (matrix[row][mid] < target) st = mid + 1;
            else ed = mid - 1;
        }
        return (matrix[row][st] == target) ? true : false;
    }
    
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0) return false;
        if (matrix[0].size() == 0) return false;
        
        int row = searchRow(matrix, target);
        return searchCol(matrix, row, target);
    }
};
