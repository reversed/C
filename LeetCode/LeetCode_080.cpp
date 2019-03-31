class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;

        int pre = nums[0];
        int cnt = 1;
        int cur = 1;
        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[i] == pre && cnt < 2)
            {
                nums[cur] = nums[i];
                ++cur;
                ++cnt;
            }
            else if (nums[i] == pre && cnt >= 2)
            {
                ++cnt;
            }
            else if (nums[i] != pre)
            {
                pre = nums[i];
                nums[cur] = nums[i];
                ++cur;
                cnt = 1;
            }
        }
        return cur;
    }
};

