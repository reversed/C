class Solution {
public:
    bool iszero(vector<int>& b) {
        for (int i = 0; i < b.size(); ++i) {
            if (b[i] > 0) return false;
        }
        return true;
    }
    
    void div2(vector<int>& b) {
        int tmp = 0;
        for (int i = 0; i < b.size(); ++i) {
            b[i] += tmp * 10;
            tmp = b[i] % 2;
            b[i] = b[i] / 2;
        }
    }
    
    int superPow(int a, vector<int>& b) {
        if (iszero(b)) return 1;

        // (a^b)%c = ((a%c)^b)%c
        // Reduce a to 0 - 1336
        a = a % 1337;
        
        // (a*b)%c=((a%c)*(b%c))%c
        // IF b IS even number
        // THEN a = a^(b/2) * a^(b/2)
        // IF b IS odd number
        // THEN a = a^(b/2) * a^(b/2) * a
        bool even = false;
        int sz = b.size();
        if (b[sz-1] % 2 != 0) even = true;
        
        div2(b);
        int ans = superPow(a, b); // Recursive
        ans *= ans;
        if (even) ans *= a;
        
        ans = ans % 1337;
        
        return ans;
    }
};
