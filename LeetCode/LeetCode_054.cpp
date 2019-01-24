class Solution {
public:
	vector<int> spiral(vector<vector<int>>& v, int row1, int row2, int col1, int col2)
	{
		vector<int> res;
		
		if (row1 > row2 || col1 > col2) return res;

		if (row1 == row2)
		{
			for (int i = col1; i <= col2; ++i) res.push_back(v[row1][i]);
			return res;
		}
		if (col1 == col2)
		{
			for (int i = row1; i <= row2; ++i) res.push_back(v[i][col1]);
			return res;
		}
		
		for (int i = col1; i <= col2; ++i) res.push_back(v[row1][i]);
		for (int i = row1 + 1; i <= row2 - 1; ++i) res.push_back(v[i][col2]);
		for (int i = col2; i >= col1; --i) res.push_back(v[row2][i]);
		for (int i = row2 - 1; i >= row1 + 1; --i) res.push_back(v[i][col1]);
		
		vector<int> tmp = spiral(v, row1 + 1, row2 - 1, col1 + 1, col2 - 1);
		res.insert(res.end(), tmp.begin(), tmp.end());
		return res;
	}

    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
		int row = matrix.size();
		if (row == 0) return res;
		int col = matrix[0].size();
		if (col == 0) return res;
		
		res = spiral(matrix, 0, row - 1, 0, col - 1);
		return res;
    }
};
