class Solution {
public:
    string getPermutation(int n, int k) {
        string res;
        string s("123456789");
        
        vector<int> v(n, 1);
        for (int i = 1; i < n; ++i) v[i] = i * v[i - 1];
             
        for (int i = n - 1; i > 0; --i)
        {
            int cnt = 0;
            while (k > v[i])
            {
                k -= v[i];
                ++cnt;
            }
            res.push_back(s[cnt]);
            s.erase(s.begin() + cnt);   
        }
        res.push_back(s[0]);
        
        return res;
    }
};

