class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string res = "";
        if (strs.size() == 0) return res;
        
        string s = strs.at(0);
        int len = s.size();
        
        for (int i = 0; i < len; ++i)
        {
            char tc = s[i];
            for (vector<string>::iterator itv = strs.begin(); itv != strs.end(); ++itv)
            {
                string si = *itv;
                int pend = si.size() - 1;
                if (i > pend || si[i] != tc)
                {
                    return res;
                }
            }
            res.push_back(tc);
        }
        return res;
    }
};

