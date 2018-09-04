class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        int sz = digits.size();
        if (sz == 0) return res;
        
        char c = digits[sz - 1];
        digits.pop_back();
        vector<string> tmp = letterCombinations(digits);
        string a;
        if (c == '2') a = "abc";
        if (c == '3') a = "def";
        if (c == '4') a = "ghi";
        if (c == '5') a = "jkl";
        if (c == '6') a = "mno";
        if (c == '7') a = "pqrs";
        if (c == '8') a = "tuv";
        if (c == '9') a = "wxyz";
        
        if (tmp.size() == 0) tmp.push_back("");
        for (char alpha : a)
        {
            for (string s : tmp)
            {
                s.push_back(alpha);
                res.push_back(s);
            }
        }
        return res;
    }
};

