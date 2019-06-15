class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        int sz = nums.size();
        vector<vector<int>> res;
        if (sz == 0) return {};
        
        for (int i = 0; i < sz; ++i) {
            res.push_back({nums[i]});
        }
        
        int maxgv = INT_MIN;
        int maxgi = 0;
        for (int i = 1; i < sz; ++i) {
            int maxv = INT_MIN;
            int maxi = -1;
            for (int j = 0; j < i; ++j) {
                int tj = nums[j];
                int ti = nums[i];
                if (ti % tj == 0) {
                    int v = res[j].size() + 1;
                    if (v > maxv) {
                        maxv = v;
                        maxi = j;
                    }
                }
            }
            if (maxv > maxgv) {
                maxgv = maxv;
                maxgi = i;
            }
            if (maxi != -1) {
                vector<int> tmp(res[maxi].begin(), res[maxi].end());
                res[i].insert(res[i].begin(), tmp.begin(), tmp.end());
            }
        }
        return res[maxgi];
    }
};
