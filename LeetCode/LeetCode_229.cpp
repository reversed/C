class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> res;
        int v1 = 0, cnt1 = 0;
        int v2 = 0, cnt2 = 0;
        int len = nums.size();
        
        for (auto i : nums) {
            if (v1 == i) {
                ++cnt1;
            }
            else if (v2 == i) {
                ++cnt2;
            }
            else if (cnt1 == 0) {
                v1 = i;
                ++cnt1;
            }
            else if (cnt2 == 0) {
                v2 = i;
                ++cnt2;
            }
            else {
                --cnt1; --cnt2;
            }
        }
        
        cnt1 = 0; cnt2 = 0;
        for (auto i : nums) {
            if (i == v1) ++cnt1;
            else if (i == v2) ++cnt2;
        }
         
        if (cnt1 > nums.size() / 3) res.push_back(v1);
        if (cnt2 > nums.size() / 3) res.push_back(v2);
        return res;
    }
};

