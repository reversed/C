class Solution {
public:
    vector<vector<int>> foo(vector<int>& c, int target, int start)
    {
        int sz = c.size();
        vector<vector<int>> res;
        
        if (start > sz - 1) return res;
        if (c[start] > target) return res;
        if (c[start] == target)
        {
            res.push_back({target});
            return res;
        }
        
        vector<vector<int>> tmp = foo(c, target - c[start], start + 1);
        for (auto v : tmp)
        {
            v.insert(v.begin(), c[start]);
            res.push_back(v);
        }
        tmp = foo(c, target, start + 1);
        for (auto v : tmp)
        {
            if (find(res.begin(), res.end(), v) == res.end())
                res.push_back(v);
        }
        
        return res;
    }
    
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        return foo(candidates, target, 0);
    }
};
