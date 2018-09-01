class Solution {
public: 
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        
        int sz = nums.size();
        for (int i = 0; i < sz - 2; ++i)
        {
            if (i > 0 && nums[i] == nums[i-1]) continue; // duplicate
            
            int a = nums[i];
            int st = i + 1;
            int ed = sz - 1;
            int target = a * (-1);
            
            while (st < ed)
            {
                int b = nums[st];
                int c = nums[ed];
                if (b + c == target)
                {
                    vector<int> v;
                    v.push_back(a);
                    v.push_back(b);
                    v.push_back(c);
                    res.push_back(v);
                    ++st;
                    while (st < ed && nums[st] == nums[st-1]) ++st; // duplicate
                    --ed;
                    while (st < ed && nums[ed] == nums[ed+1]) --ed; // duplicate
                }
                else if (b + c < target)
                {
                    ++st;
                }
                else
                {
                    --ed;
                }
            }
        }
        return res;
    }
};

/*
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) { 
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        if (nums.size() < 3) return res;
            
        for (int i = 0; i < nums.size() - 2; ++i)
        {
            for (int j = i + 1; j < nums.size() - 1; ++j)
            {
                for (int k = j + 1; k < nums.size(); ++k)
                {
                    if (nums[i] + nums[j] + nums[k] == 0)
                    {
                        vector<int> v;
                        v.push_back(nums[i]);
                        v.push_back(nums[j]);
                        v.push_back(nums[k]);
                        res.push_back(v);
                    }
                }
            }
        }
        
        sort(res.begin(), res.end());
        auto last = unique(res.begin(), res.end());
        res.erase(last, res.end());
        return res;
    }
};
*/
