class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> res;
        
        if (n == 0) 
        {
            res.push_back(0);
            return res;
        }
        
        vector<int> tmp = grayCode(n-1);
        for (int i = 0; i < tmp.size(); ++i)
        {
            res.push_back(tmp[i]);
        }
        for (int i = tmp.size() - 1; i >= 0; --i)
        {
            res.push_back(tmp[i] | (1 << (n-1)));
        }
        return res;
    }
};
