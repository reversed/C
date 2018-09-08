class Solution {
public:
    vector<vector<int>> threeSum(vector<int>&nums, int st, int target)
    {
        vector<vector<int>> res;
        int sz = nums.size();
        
        for (int i = st; i < sz - 2; ++i)
        {
            if (i > st && nums[i] == nums[i-1]) continue;
            
            int t = target - nums[i];
            int bg = i + 1;
            int ed = sz - 1;
            while (bg < ed)
            {
                int val = nums[bg] + nums[ed];
                vector<int> tmp;
                if (val == t)
                {
                    tmp.push_back(nums[i]);
                    tmp.push_back(nums[bg]);
                    tmp.push_back(nums[ed]);
                    res.push_back(tmp);
                    --ed;
                    while (bg < ed && nums[ed] == nums[ed + 1]) --ed;
                    ++bg;
                    while (bg < ed && nums[bg] == nums[bg - 1]) ++bg;
                }
                else if (val < t)
                {
                    ++bg;
                }
                else if (val > t)
                {
                    --ed;
                }
            }
        }
        return res;
    }
    
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int sz = nums.size();
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < sz - 3; ++i)
        {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            
            vector<vector<int>> tmp = threeSum(nums, i + 1, target - nums[i]); 
            
            for (auto vi : tmp)
            {
                vi.push_back(nums[i]);
                res.push_back(vi);
            }
        }
        return res;
    }
};

