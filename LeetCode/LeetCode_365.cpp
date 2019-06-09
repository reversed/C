class Solution {
public:
    int gcd(int x, int y) {
        if (x % y == 0) return y;
        else return gcd(y, x % y);
    }
    
    bool canMeasureWater(int x, int y, int z) {
        if (x + y < z) return false;
        if (z == 0) return true;
        if (x == 0 && y == 0) return false;
        if (x < y) swap(x, y);
        
        if (y == 0) return x == z;
        else return (z % gcd(x, y) == 0);
    }
};

