class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int pre = 0;
        int len = nums.size();
        
        for (int i = 1; i < len; ++i)
        {
            if (nums[i] == nums[pre])
            {
                continue;
            }
            else
            {
                ++pre;
                nums[pre] = nums[i];
            }
        }
        return pre + 1;
    }
};

