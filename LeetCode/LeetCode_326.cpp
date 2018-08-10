class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n <= 0) return false;
        int maxn = INT_MAX;
        int max3x = pow(3, (int)(log(maxn) / log(3)));
        return max3x % n == 0;
    }
};

