class Solution {
public:
    int searchLeft(vector<int>& nums, int pos, int target)
    {
        int st = 0;
        int ed = pos;
        
        while (st < ed)
        {
            int mid = st + (ed - st) / 2;
            if (nums[mid] == target)
            { 
                ed = mid;
                if (nums[st] == target) return st;
                else ++st;
            }
            else st = mid + 1;
        }
        return ed;
    }
    
    int searchRight(vector<int>& nums, int pos, int target)
    {
        int sz = nums.size();
        int st = pos;
        int ed = sz - 1;
        
        while (st < ed)
        {
            
            int mid = st + (ed - st) / 2;
            if (nums[mid] == target)
            { 
                st = mid; 
                if (nums[ed] == target) return ed;
                else --ed;
            }
            else ed = mid - 1;
        }
        return st;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res;
        int sz = nums.size();
        int st = 0;
        int ed = sz - 1;
        
        while (st <= ed)
        {
            int mid = st + (ed - st) / 2;
            
            if (nums[mid] == target)
            {                
                int l = searchLeft(nums, mid, target);
                int r = searchRight(nums, mid, target);
                res.push_back(l);
                res.push_back(r);
                return res;
            }
            else if (target < nums[mid])
            {
                ed = mid - 1;
            }
            else if (target > nums[mid])
            {
                st = mid + 1;
            }
        }
        
        // no match
        res.push_back(-1);
        res.push_back(-1);
        return res;
    }
};

