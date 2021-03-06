class Solution {
public:
    vector<vector<int>> subsets_n(vector<int>& nums, int st, int n)
    {
        vector<vector<int>> res;
        int ed = nums.size() -1 ;
        
        if (n == 0) return { {} };
        if (n < 0) return res;
        
        for (int i = st; i < nums.size(); ++i)
        {
            vector<vector<int>> tmp = subsets_n(nums, i+1, n-1);
            for (auto v : tmp)
            {
                v.push_back(nums[i]);
                res.push_back(v);
            }
        }
        return res;
    }
    
    vector<vector<int>> subsets_n(vector<int>& nums, int n)
    {
        vector<vector<int>> res;
        
        if (n == 0) return { {} };

        for (int i = 0; i < nums.size(); ++i)
        {
            vector<vector<int>> tmp = subsets_n(nums, i+1, n-1);
            for (auto v : tmp)
            {
                v.push_back(nums[i]);
                res.push_back(v);
            }
        }
        return res;
    }
    
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        for (int i = 0; i <= nums.size(); ++i)
        {
            vector<vector<int>> tmp = subsets_n(nums, i);
            res.insert(res.begin(), tmp.begin(), tmp.end());
        }
        return res;
    }
};

/* back tracing algo
class Solution {
public:
    void foo(vector<int>& nums, int pos, vector<int>& ans)
    {
        if (pos == nums.size()) {
            res.push_back(ans);
            return;
        }
        
        ans.push_back(nums[pos]);
        foo(nums, pos+1, ans);
        ans.pop_back();
        foo(nums, pos+1, ans);
    }
    
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> ans {};
        foo(nums, 0, ans);
        return res;
    }
    
    vector<vector<int>> res;
};
*/
