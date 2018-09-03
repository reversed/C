class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int sz = nums.size();
        if (sz < 3) return 0;
        sort(nums.begin(), nums.end());
        
        int res = 0;
        int min = INT_MAX;
        for (int i = 0; i < sz - 2; ++i)
        {
            int t = target - nums[i];
            int st = i + 1;
            int ed = sz - 1;
            while (st < ed)
            {
                int s2 = nums[st] + nums[ed];
                int diff = abs(s2 - t);
                if (diff < min)
                {
                    min = diff;
                    res = nums[i] + s2;
                }

                if (s2 < t) ++st;
                else --ed;
            }
            
        }
        return res;
    }
};

