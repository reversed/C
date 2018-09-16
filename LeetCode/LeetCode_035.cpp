class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int len = nums.size();
        
        int i = 0;
        while (i < len)
        {
            if (nums[i] >= target)
                return i;
            ++i;
        }
        return i;
    }
};

