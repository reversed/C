class Solution {
public:
    bool isValid(string s) {
        stack<char> ps;
        
        for (string::iterator it = s.begin(); it != s.end(); ++it)
        {
            char p = *it;
            if (p == '(' || p == '[' || p == '{')
            {
                ps.push(p);
                continue;
            }
            
            if (ps.empty()) return false;

            char q = ps.top();
            ps.pop();
            
            if (p == ')')
            {
                if (q != '(') return false;
            }
            if (p == ']')
            {
                if (q != '[') return false;
            }
            if (p == '}')
            {
                if (q != '{') return false;
            }
        }
        if (!ps.empty()) return false;
        
        return true;
    }
};

