class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res;
        if (nums.empty()) return res;
        
        int sz = nums.size();
        vector<int> prod1(sz, 1);
        vector<int> prod2(sz, 1);

        prod1[0] = nums[0];
        for (int i = 1; i < sz; ++i) {
            prod1[i] = prod1[i-1] * nums[i];
        }
        
        prod2[sz-1] = nums[sz-1];
        for (int i = sz - 2; i >= 0; --i) {
            prod2[i] = prod2[i+1] * nums[i];
        }
        
        for (int i = 0; i < sz; ++i) {
            int l = (i >= 1) ? prod1[i-1] : 1;
            int r = (i <= sz - 2) ? prod2[i+1] : 1;
            res.push_back(l * r);
        }
        return res;
    }
};

