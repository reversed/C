class Solution {
public:
    int search(vector<int>& nums, int target) {
        int sz = nums.size();
        int st = 0;
        int ed = sz - 1;
        
        while (st <= ed)
        {
            int mid = st + (ed - st) / 2;
            if (nums[mid] == target)
            {
                return mid;
            }
            
            if (nums[st] <= nums[mid])
            {
                if (target < nums[mid] && target >= nums[st])
                {
                    ed = mid - 1;
                }
                else
                {
                    st = mid + 1;
                }
            }
            else if (nums[mid] <= nums[ed])
            {
                if (target > nums[mid] && target <= nums[ed])
                {
                    st = mid + 1;
                }
                else
                {
                    ed = mid - 1;
                }
            }
        }
        return -1;
    }
};

