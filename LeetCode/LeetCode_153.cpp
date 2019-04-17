class Solution {
public:
    int findMin(vector<int>& nums) {
        if (nums.empty()) return 0;
        int st = 0;
        int ed = nums.size() - 1;
        int mid = 0;
        
        while (st < ed) {
            mid = st + (ed - st) / 2;
            //printf("%d %d %d\n", st, mid, ed);
            
            if (mid - 1 >= st && mid + 1 <= ed)
            {
                if (nums[mid-1] > nums[mid] && nums[mid+1] > nums[mid]) return nums[mid];
            }
            
            if (nums[st] >= nums[ed] && nums[mid] >= nums[st]) {
                st = mid + 1;
            }
            else if (nums[st] >= nums[ed] && nums[mid] < nums[st]) {
                ed = mid - 1;
            }
            else if (nums[st] < nums[ed] && nums[mid] >= nums[st]) {
                ed = mid - 1;
            }
            else if (nums[st] < nums[ed] && nums[mid] < nums[st]) {
                st = mid + 1;
            }
        }
        return nums[st];
    }        
};

