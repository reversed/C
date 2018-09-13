class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int sz = nums.size();
        
        int i;
        for (i = sz - 2; i >= 0; --i)
        {
            if (nums[i] < nums[i + 1])
            {
                for (int j = sz - 1; j > i; --j)
                {
                    if (nums[j] > nums[i]) 
                    {
                        swap(nums[i], nums[j]);
                        break;
                    }
                }
                break;
            }
        }
        
        sort(nums.begin() + i + 1, nums.end());
    }
};


