class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int st = 0;
        int ed = nums.size() - 1;
        
        while (st <= ed)
        {
            if (nums[st] == nums[ed] && st != ed)
            {
                ++st;
                continue;
            }

            int mid = st + (ed - st) / 2;
            
            if (nums[mid] > target && nums[st] <= target)
            {
                ed = mid - 1;
            }
            else if (nums[mid] > target && nums[st] >= target)
            {
                if (nums[st] > nums[mid]) ed = mid - 1; // turn around happened
                else st = mid + 1;
            }
            else if (nums[mid] < target && nums[ed] >= target)
            {
                st = mid + 1;
            }
            else if (nums[mid] < target && nums[ed] <= target)
            {
                if (nums[ed] < nums[mid]) st = mid + 1; // turn around happened
                else ed = mid - 1;
            }
            else if (nums[mid] == target)
            {
                return true;
            }
        }
        return false;
    }
};

