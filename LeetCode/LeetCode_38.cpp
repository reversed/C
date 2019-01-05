class Solution {
public:
    string countAndSay(int n) {
        if (n == 1) return "1";

        string s = countAndSay(n-1);
        
        string res;
        char c = s[0];
        int cnt = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            if (c == s[i])
            {
                cnt += 1;
            }
            else
            {
                res.push_back(cnt + '0');
                res.push_back(c);
                cnt = 1;
            }
            c = s[i];
        }
        res.push_back(cnt + '0');
        res.push_back(c);
        return res;
    }
};

