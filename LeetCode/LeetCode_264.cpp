class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> res(1691, 0);
        res[0] = 0;
        res[1] = 1;
        int v2 = 1, v3 = 1, v5 = 1;
        for (int i = 2; i <= n; ++i)
        {
            int val = min(res[v2] * 2, min(res[v3] * 3, res[v5] * 5));
            res[i] = val;
            if (res[v2] * 2 == res[i]) ++v2;
            if (res[v3] * 3 == res[i]) ++v3;
            if (res[v5] * 5 == res[i]) ++v5;
        }
        return res[n];
    }
};

