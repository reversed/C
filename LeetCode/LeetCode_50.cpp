class Solution {
public:
    double myPow(double x, int n) {
        double res = 1;
        
        if (n >= 0)
        {
            while (n != 0)
            {
                if (n % 2 == 0)
                {
                    x = x * x;
                    n = n / 2;
                }
                else
                {
                    res *= x;
                    n = n - 1;
                }
            }
        }
        
        if (n < 0)
        {
            while (n != 0)
            {
                if (n % 2 == 0)
                {
                    x = x * x;
                    n = n / 2;
                }
                else
                {
                    res /= x;
                    n = n + 1;
                }
            }
        }
        return res;
    }
};

