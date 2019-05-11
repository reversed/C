class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        if (nums.empty()) return res;
        
        int st = 0;
        int ed = 0;
        string s1, s2, s;
        
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i-1] + 1) {
                ed = i;
            }
            else if (nums[i] > nums[i-1] + 1) {
                s1 = std::to_string(nums[st]);
                s2 = std::to_string(nums[ed]);
                if (s1 != s2) s = s1 + "->" + s2;
                else s = s1;
                res.push_back(s);
                st = ed = i;
            }
        }
        s1 = std::to_string(nums[st]);
        s2 = std::to_string(nums[ed]);
        if (s1 != s2) s = s1 + "->" + s2;
        else s = s1;
        res.push_back(s);
        return res;
    }
};

