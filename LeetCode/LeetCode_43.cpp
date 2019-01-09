class Solution {
public:
    string smul(string s, char c)
    {
        int carry = 0;
        int len = s.size();
        string res;
        
        int mul = c - '0';
        for (int i = len - 1; i >= 0; --i)
        {
            int dig = s[i] - '0';
            int product = dig * mul + carry;
            res.insert(res.begin(), (product % 10 +'0'));
            carry = product / 10;
        }
        if (carry != 0) res.insert(res.begin(), carry + '0');
        return res;
    }
    
    string sadd(string s1, string s2)
    {
        string res;
        int len1 = s1.size();
        int len2 = s2.size();
        
        int pos1 = len1 - 1;
        int pos2 = len2 - 1;
        int carry = 0;
        while (pos1 >= 0 || pos2 >= 0)
        {
            int i1 = 0, i2 = 0;
            if (pos1 >= 0) i1 = s1[pos1] - '0';
            if (pos2 >= 0) i2 = s2[pos2] - '0';
            
            int add_res = i1 + i2 + carry;
            res.insert(res.begin(), add_res % 10 + '0');
            carry = add_res / 10;
            --pos1; --pos2;
        }
        if (carry != 0) res.insert(res.begin(), carry + '0');
        return res;
    }
    
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
       
        string res;
        for (char c : num2)
        {
            res.push_back('0');
            string tmp = smul(num1, c);
            res = sadd(tmp, res);
        }
        return res;
    }
};

