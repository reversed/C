class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res = permute(nums);
        sort(res.begin(), res.end());
        auto it = unique(res.begin(), res.end());
        res.resize(distance(res.begin(), it));
        return res;
    }

    vector<vector<int>> foo(vector<int>& nums, int st)
    {
        vector<vector<int>> res;
        int len = nums.size();
        if (st > len - 1) return res;
        if (st == len - 1)
        {
            res.push_back( {nums[st]} );
            return res;
        }
        
        for (int i = st; i < len; ++i)
        {
            swap(nums[st], nums[i]);
            auto tmp = foo(nums, st + 1);
            for (auto v : tmp) 
            {
                v.push_back(nums[st]);
                res.push_back(v);
            }
            swap(nums[st], nums[i]);
        }
        return res;
    }
    
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        return foo(nums, 0);
    }
};

