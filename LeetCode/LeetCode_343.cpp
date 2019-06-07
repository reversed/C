class Solution {
public:
    int integerBreak(int n) {
        vector<int> res(n+1, 1);
        
        for (int i = 2; i <= n; ++i) {
            int max = INT_MIN;
            for (int j = 1; j <= i / 2; ++j) {
                int k = i - j;
                int val = res[j] * res[k];
                if (val > max) max = val;
                val = j * k;
                if (val > max) max = val;
                val = res[j] * k;
                if (val > max) max = val;
                val = j * res[k];
                if (val > max) max = val;
            }
            res[i] = max;
        }
        return res[n];
    }
};
