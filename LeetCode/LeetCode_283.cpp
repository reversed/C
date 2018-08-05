class Solution {
public:
    bool swapNextNonZero(vector<int>& nums, int ia)
    {
        int sz = nums.size();
        
        for (int i = ia + 1; i < sz; ++i)
        {
            if (nums[i] != 0)
            {
                swap(nums[ia], nums[i]);
                return true;
            }
        }
        return false;
    }
    
    void moveZeroes(vector<int>& nums) {
        int sz = nums.size();
        
        for (int i = 0; i < sz; ++i)
        {
            if (nums[i] == 0)
            {
                if (!swapNextNonZero(nums, i)) break;
            }
        }
    }
};
