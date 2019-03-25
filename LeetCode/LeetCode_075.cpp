class Solution {
public:
    void sortColors(vector<int>& nums) {
        if (nums.empty()) return;
        int st = 0;
        int ed = nums.size() - 1;
        int cur = st;
        
        while (cur <= ed)
        {
            if (nums[cur] == 0)
            {
                swap(nums[cur], nums[st]);
                ++st;
                ++cur;
            }
            else if (nums[cur] == 2)
            {
                swap(nums[cur], nums[ed]);
                --ed;
            }
            else
            {
                ++cur;
            }
        }
    }
};


