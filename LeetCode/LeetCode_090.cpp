class Solution {
public:
    vector<vector<int>> res;

    void subsetWithDup(vector<int>& nums, int pos, vector<int>& ans)
    {
        if (pos == nums.size())
        {
            if (find(res.begin(), res.end(), ans) != res.end()) return;
            res.push_back(ans);
            return;
        }
        
        ans.push_back(nums[pos]);
        subsetWithDup(nums, pos+1, ans);
        ans.pop_back();
        subsetWithDup(nums, pos+1, ans);
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> ans {};
        subsetWithDup(nums, 0, ans);
        return res;
    }
};

