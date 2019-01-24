class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();
        
        int m = INT_MIN;
        int s = 0;
        for (int i = 0; i < len; ++i)
        {
            s += nums[i];
            if (s > m)
            {
                m = s;
            }
            if (s < 0)
            {
                s = 0;
            }
        }
        return m;
    }
};
