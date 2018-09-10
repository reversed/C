class Solution {
public:
    vector<string> genParen(int ln, int rn, int n)
    {
        vector<string> res;
        if (ln < rn) return res;
        if (ln > n || rn > n) return res;
        if (ln == n && rn == n)
        {
            string s;
            res.push_back(s);
            return res;
        }
        
        vector<string> tmpl = genParen(ln + 1, rn, n);
        for (string s : tmpl)
        {
            s.insert(0, "(");
            res.push_back(s);
        }
        vector<string> tmpr = genParen(ln, rn + 1, n);
        for (string s : tmpr)
        {
            s.insert(0, ")");
            res.push_back(s);
        }
        return res;
    }

    vector<string> generateParenthesis(int n) {
        return genParen(0, 0, n);
    }
};

