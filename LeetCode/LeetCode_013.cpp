class Solution {
public:
    int romanToInt(string s) {
        std::map<char, int> mp;
   
        mp['I'] = 1;
        mp['V'] = 5;
        mp['X'] = 10;
        mp['L'] = 50;
        mp['C'] = 100;
        mp['D'] = 500;
        mp['M'] = 1000;
        
        int last = 0;
        int res = 0;
        for (string::reverse_iterator rit = s.rbegin(); rit != s.rend(); ++rit)
        {
            char c = *rit;
            int cur = mp[*rit];
            if (cur < last) res -= cur;
            else res += cur;
            
            last = cur;
        }
        return res;
    }
};

