class Solution {
public:
    int str2num(string s)
    {
        if (s.empty()) return -1;
        if (s.size() == 2 && s[0] == '0') return -1;
        if (s.size() == 3 && s[0] == '0') return -1;
        if (s.size() > 3) return -1;

        int res = 0;
        for (int i = 0; i < s.size(); ++i) {
            res = res * 10 + (s[i] - '0');
        }
        
        return res;
    }
    
    vector<string> restoreIp(string s, int n)
    {
        vector<string> res;
        if (n == 0) return res;
        if (n == 1) {
            int val = str2num(s);
            if (val <= 255 && val >= 0) res.push_back(s);
            return res;
        }
        
        vector<string> tmp;
        string s1;
        int val = 0;

        if (s.empty()) return res;
        s1.insert(s1.begin(), s.back());
        s.pop_back();
        val = str2num(s1);
        if (str2num(s1) >= 0 && str2num(s1) <= 255) {
            tmp = restoreIp(s, n-1);
            for (string& ss : tmp) {
                ss = ss + '.' + s1;
                res.push_back(ss);
            }
        }

        if (s.empty()) return res;      
        s1.insert(s1.begin(), s.back());
        s.pop_back();
        val = str2num(s1);
        if (str2num(s1) >= 0 && str2num(s1) <= 255) {
            tmp = restoreIp(s, n-1);
            for (string& ss : tmp) {
                ss = ss + '.' + s1;
                res.push_back(ss);
            }
        }

        if (s.empty()) return res;
        s1.insert(s1.begin(), s.back());
        s.pop_back();
        val = str2num(s1);
        if (str2num(s1) >= 0 && str2num(s1) <= 255) {
            tmp = restoreIp(s, n-1);
            for (string& ss : tmp) {
                ss = ss + '.' + s1;
                res.push_back(ss);
            }
        }
        return res;
    }
    
    vector<string> restoreIpAddresses(string s) {
        return restoreIp(s, 4);
    }
};

