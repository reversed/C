class Solution {
public:
    int getSum(int a, int b) {
        int res = a ^ b;
        int cur = a & b;
        
        while (cur != 0)
        {
            int tmp = res;
            res = res ^ (cur << 1);
            cur = tmp & (cur << 1);
        }
        
        return res;
    }
};

