class Solution {
public:
    vector<vector<int>> foo(vector<int>& c, int target, int st)
    {
        int sz = c.size();
        vector<vector<int>> res;
        
        if (st > sz - 1) return res;
        if (c[st] > target) return res;
        if (c[st] == target)
        {
            vector<int> tmp {target};
            res.push_back(tmp);
            return res;
        }
        
        int val = 0;
        while (val < target)
        {
            vector<vector<int>> tmp = foo(c, target - val, st + 1);
            for (auto v : tmp)
            {
                int cval = val;
                while (cval != 0)
                {
                    v.insert(v.begin(), c[st]);
                    cval -= c[st];
                }
                res.push_back(v);
            }
            val += c[st];
        }
        if (val == target)
        {
            vector<int> tmp;
            while (val != 0)
            {
                tmp.push_back(c[st]);
                val -= c[st];
            }
            res.push_back(tmp);
        }
        return res;
    }
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        return foo(candidates, target, 0);
    }
};

