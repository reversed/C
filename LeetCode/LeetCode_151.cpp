class Solution {
public:
    string trim(string s) {
        string res = "";
        
        int st = 0;
        while (st < s.size() && s[st] == ' ') ++st;
        
        while (st < s.size()) {
            while (st < s.size() && s[st] != ' ') {
                res.push_back(s[st]);
                ++st;
            }
            res.push_back(' ');
            while (st < s.size() && s[st] == ' ') {
                ++st;
            }
        }
        if (res.back() == ' ') res.pop_back();
        return res;
    }
    
    void reverseStr(string& s, int start, int end) {
        int st = start;
        int ed = end;
        while (st < ed) {
            swap(s[st], s[ed]);
            ++st;
            --ed;
        }
    }
    
    string reverseWords(string s) {
        string res = trim(s);
        reverseStr(res, 0, res.size() - 1);
        
        res.push_back(' ');
        int st = 0;
        int ed = res.find_first_of(' ', st);
        while (ed != string::npos) {
            reverseStr(res, st, ed - 1);
            st = ed + 1;
            ed = res.find_first_of(' ', st);
        }
        res.pop_back();
        
        return res;
    }
};

