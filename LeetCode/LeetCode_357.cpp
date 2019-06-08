class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) return 1;

        vector<int> res(11, 0);
        res[0] = 0;
        res[1] = 10;
        for (int i = 2; i <= 10; ++i) {
            int v = 9;
            for (int j = 1; j < i; ++j) {
                v = v * (10 - j);
            }
            res[i] = v;
        }
        
        int number = 0;
        for (int i = 0; i <= n && i <= 10; ++i) {
            number += res[i];
        }
        
        return number;
    }
};
