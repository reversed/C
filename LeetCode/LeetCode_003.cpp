class Solution {
public:
    int sfind(string s, char c, int st, int ed)
    {
        for (int i = st; i < ed; ++i)
        {
            if (s[i] == c) return i;
        }
        return -1;
    }

    int lengthOfLongestSubstring(string s) {
        int mx = 0;
        int p = 0;
        
        for (int i = 0; i < s.size(); ++i)
        {
            int pos = sfind(s, s[i], p, i);
            
            if (pos != -1)
            {
                p = pos + 1;
            }
            else
            {
                mx = max(mx, i - p + 1);
            }
        }
        return mx;
    }
};

