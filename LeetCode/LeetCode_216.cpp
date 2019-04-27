class Solution {
public:
    bool isValid(vector<int>& f, int cur) {
        for (int i = 0; i <= cur; ++i) {
            if (f[i] == 1) return false;
        }
        return true;
    }
    
    vector<vector<int>> combinationSum3(int k, int n, vector<int>& f) {
        if (n < 0) return {};
        if (k == 0 && n == 0) return {{}};

        vector<vector<int>> res;       
        for (int i = 1; i <= 9; ++i) {
            if (!isValid(f, i)) continue;

            f[i] = 1;
            vector<vector<int>> tmp = combinationSum3(k-1, n-i, f);
            for (auto &vi : tmp) {
                vi.push_back(i);
                res.push_back(vi);
            }
            f[i] = 0;
        }
        return res;
    }
    
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> flags(10, 0);
        return combinationSum3(k, n, flags);
    }
};

