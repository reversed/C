class Solution {
public:
    int myAtoi(string str) {
        string ts;
        int sign = 1;

        bool f = false;
        bool sindex = true;
        for (int i = 0; i < str.size(); ++i)
        {
            char c = str[i];
            if (f == false && isblank(c)) continue;
            if (f == true && !isdigit(c)) break;
            if (sindex && !isdigit(c) && c != '-' && c != '+') return 0;
            if (!sindex && !isdigit(c)) return 0;
            
            f = true;
            sindex = false;
            if (c == '-') { sign = -1; continue; }
            if (c == '+') { sign = 1; continue; }          
            ts.push_back(c);
        }

        uint64_t res = 0;
        uint32_t mx = INT_MAX;
        for (int i = 0; i < ts.size(); ++i)
        {
            int tmp = ts[i] - '0';
            res = res * 10 + tmp;
            if (sign == 1 && res > mx) return INT_MAX;
            if (sign == -1 && res > mx + 1) return INT_MIN;
        }
        return res * sign;
    }
};

