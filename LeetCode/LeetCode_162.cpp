class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int st = 0;
        int ed = nums.size() - 1;
        
        while (st < ed)
        {
            if (nums[st+1] < nums[st]) return st;
            else if (nums[ed-1] < nums[ed]) return ed;
            
            int mid = st + (ed - st) / 2;
            if (nums[mid-1] > nums[mid]) {
                // left
                ed = mid - 1;
            }
            else if (nums[mid+1] > nums[mid]) {
                // right
                st = mid + 1;
            }
            else {
                return mid;
            }
        }

        return st;
    }
};

