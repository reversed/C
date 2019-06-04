class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<int> res(n+1, 1);
        
        int sz = primes.size();
        vector<int> p(sz, 1);
        
        for (int i = 2; i <= n; ++i) {
            int min = INT_MAX;
            int min_idx = INT_MAX;
            for (int j = 0; j < sz; ++j) {
                int tmp = primes[j] * res[p[j]];
                while (tmp == res[i-1]) {
                    p[j] += 1;
                    tmp = primes[j] * res[p[j]];
                }
                if (tmp < min) {
                    min = tmp;
                    min_idx = j;
                }
            }
            p[min_idx] += 1;
            res[i] = min;
            //cout << res[i] << endl;
        }
        return res[n];
    }
};


