class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        string res;
        int64_t ntor = numerator;
        int64_t dtor = denominator;
        
        if (ntor == 0) return "0";
        else if (ntor < 0 && dtor > 0) { ntor *= -1; res.push_back('-'); }
        else if (ntor > 0 && dtor < 0) { dtor *= -1; res.push_back('-'); }
        else if (ntor < 0 && dtor < 0) { ntor *= -1; dtor *= -1; }
        
        // integer
        int64_t d = ntor / dtor;
        res += to_string(d);
        
        // fraction
        set<int> si;
        int64_t f = ntor % dtor;
        if (f != 0) {
            res.push_back('.');
            si.insert(f);
            while (f != 0) {
                int64_t tmp = f * 10;
                res.push_back((tmp / dtor) + '0');
                f = tmp % dtor;

                if (si.count(f) != 0) break;
                si.insert(f);
            }
        }
        
        // loop detect
        if (f != 0) {
            int64_t target = f;
            string ts; 
            do {
                f = f * 10;
                ts.push_back((f / dtor) + '0');
                f = f % dtor;
            } while (f != target);
            
            int sz = ts.size(); 
            res.insert(res.end() - sz, '(');
            res.insert(res.end(), ')');
        }        
        
        return res;
    }
};

