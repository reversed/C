class Solution {
public:
    int findMin(vector<int>& nums) {
        if (nums.empty()) return 0;
        int st = 0;
        int ed = nums.size() - 1;
        int mid = 0;
        
        while (st < ed) {
            if (nums[st] == nums[ed]) {
                --ed;
                continue;
            }

            mid = st + (ed - st) / 2;
            //printf("%d %d %d\n", st, mid, ed);
            
            if (mid != st && nums[mid] == nums[st]) {
                st = mid;
                continue;
            }
            if (mid != ed && nums[mid] == nums[ed]) {
                ed = mid;
                continue;
            }
            
            if (nums[st] >= nums[ed] && nums[mid] >= nums[st]) {
                st = mid + 1;
            }
            else if (nums[st] >= nums[ed] && nums[mid] < nums[st]) {
                ed = mid;
            }
            else if (nums[st] < nums[ed] && nums[mid] >= nums[st]) {
                ed = mid - 1;
            }
            else if (nums[st] < nums[ed] && nums[mid] < nums[st]) {
                st = mid;
            }
        }
        return nums[st];     
    }
};
