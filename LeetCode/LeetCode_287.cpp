class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // st, ed is based on 1 ~ n Numbers, not vector nums index
        int st = 1;
        int ed = nums.size() - 1;
        
        while (st < ed) {
            int mid = st + (ed - st) / 2;
            int cnt = 0;
            
            //printf("%d %d %d\n", st, ed, mid);
            
            for (int i = 0; i < nums.size(); ++i) {
                if (nums[i] <= mid) ++cnt;
            }
            if (cnt > mid) ed = mid;
            else st = mid + 1;
        }
        return st;
    }
};

