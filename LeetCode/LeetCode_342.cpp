class Solution {
public:
    bool isPowerOfFour(int num) {
        if (num <= 0) return false;
        int tmp = num & (num - 1);
        if (tmp == 0 && (num & 0x55555555) != 0) return true;
        return false;
    }
};


