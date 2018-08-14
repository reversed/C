class Solution {
public:
    bool isPerfectSquare(int num) {
        for (int i = 0; i <= 0x10000; ++i)
        {
            int tmp = i * i;
            if (tmp == num) return true;
            else if (tmp > num) return false;
        }
        return false;
    }
};

