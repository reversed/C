class Solution {
public:
    int maxRotateFunction(vector<int>& A) {
        int n = A.size();
        if (n == 0) return 0;
        
        int64_t sum = 0;
        int64_t maxv = 0;
        for (int i = 0; i < n; ++i) {
            sum += A[i];
            maxv += A[i] * i;
        }
        
        int64_t res = maxv;
        int64_t maxt = 0;
        for (int i = 0; i < n - 1; ++i) {
            maxt = maxv + sum;
            maxt -= (int64_t)(A[n - 1 - i]) * n;
            res = max(res, maxt);
            maxv = maxt;
        }
        return res;
    }
};

/* Time Exceeded Limit
class Solution {
public:
    int maxRotateFunction(vector<int>& A) {
        int n = A.size();
        if (n == 0) return 0;

        int64_t maxv = INT_MIN;
        for (int i = 0; i < n; ++i) {
            int64_t sum = 0;
            int idx = 0;
            for (int j = 0; j < n; ++j) {
                int cnt = (i + j) % n;
                sum += A[idx] * cnt;
                ++idx;
            }
            if (sum > maxv) maxv = sum;
        }
        return maxv;
    }
};
*/

