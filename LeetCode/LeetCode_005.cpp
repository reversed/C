class Solution {
public:
    string longestPalindrome(string s) {
        int sz = s.size();
        bool res[1000][1000];
    
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
                res[i][j] = false;

        int start = 0;
        int maxlen = 1;
        for (int i = 0; i < sz; ++i)
        {
            res[i][i] = true;
            if (i + 1 < sz && s[i] == s[i + 1])
            {
                start = i;
                maxlen = 2;
                res[i][i + 1] = true;
            }
        }
        

        for (int k = 0; k < sz; ++k)
        {
            for (int i = 0; i < sz - k - 1; ++i)
            {
                if (res[i][i + k] == false) continue;
                if (i - 1 < 0 || i + k + 1 > sz) continue;
                if (s[i - 1] != s[i + k + 1]) continue;
                res[i - 1][i + k + 1] = true;
                start = i - 1;
                maxlen = k + 3;
            }
        }

        return s.substr(start, maxlen); 
    }
};
