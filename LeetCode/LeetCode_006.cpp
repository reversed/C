class Solution {
public:
    string convert(string s, int numRows) {
        vector<string> vs;
        
        if (numRows == 1) return s;
        
        for (int i = 0; i < numRows; ++i)
        {
            vs.push_back("");
        }
        
        int st = 0;
        int inc = 1;
        for (char c : s)
        {
            if (st == numRows - 1) inc = -1;
            if (st == 0) inc = 1;
            vs[st].push_back(c);
            
            st += inc;
        }
        
        string res;
        for (int i = 0; i < numRows; ++i)
        {
            res += vs[i];
        }
        return res;
    }
};

