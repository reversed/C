class Solution {
public:
    int divide_pos(int dividend, int divisor)
    {
        if (divisor == 0) return -1;

        int res = 0;
        while (dividend - divisor >= 0)
        {
            int d = divisor;
            int cnt = 0;
            while (dividend - d >= 0)
            {
                d <<= 1;
                ++cnt;
                if (cnt == 32) break;
            }
            dividend -= (divisor << (cnt-1));
            res += (1 << (cnt-1));
        }
        return res;
    }
    
    int divide(int dividend, int divisor) {
        int min = INT_MIN;
        int max = INT_MAX;
        int q = 0;
        
        // handle extreme cases
        if (dividend == min)
        {
            if (divisor == min) return 1;
            if (divisor == 1) return min;
            if (divisor == -1) return max;
            q += 1;
            dividend += abs(divisor); 
        }
        else if (divisor == min)
        {
            return 0;
        }
        
        int sign1 = dividend < 0 ? (-1) : 1;
        int sign2 = divisor < 0 ? (-1) : 1;
                
        q += divide_pos(dividend * sign1, divisor * sign2);
        return sign1 * sign2 * q;
    }
};

