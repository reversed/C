class Solution {
public:
    int reverse(int x) {
        if (x < 0 && x < x - 1) return 0; // overflow

        int s = x < 0 ? -1 : 1;
        x = x * s;
        
        int res = 0;
        while (x != 0)
        {
            if (res > 214748364) return 0;
            if (res == 214748364 && x % 10 > 8) return 0;
            res = res * 10 + x % 10;
            x /= 10;
        }
        return s * res;
    }
};

