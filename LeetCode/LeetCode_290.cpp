class Solution {
public:
    void getString(vector<string>& vs, string str)
    {
        string tmp;
        for (char c : str)
        {
            if (c != ' ')
            {
                tmp.push_back(c);
            }
            else
            {
                vs.push_back(tmp);
                tmp.clear();
            }
        }
        vs.push_back(tmp);
    }
    
    bool wordPattern(string pattern, string str) {
        vector<string> vs;
        getString(vs, str);
        
        int lv = vs.size();
        int pv = pattern.size();
        if (lv != pv) return false;
        
        string::iterator pi = pattern.begin();
        vector<string>::iterator vi = vs.begin();
        map<char, string> m;
        
        while (pi != pattern.end())
        {
            char pc = *pi;
            string ss = *vi;
            map<char, string>::iterator mi = m.find(pc);
            if (mi != m.end())
            {
                if (m[pc] != ss) return false;
            }
            else
            {
                for (auto p : m)
                {
                    if (p.second == ss) return false;
                }
                m[pc] = ss;
            }
            
            ++pi;
            ++vi;
        }
        
        return true;
    }
};
