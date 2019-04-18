class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int max = INT_MAX;
        
        for (int i = nums.size() - 1; i >= 0; --i) {  
            int cnt = 0;
            int sum = 0;
            for (int j = i; j < nums.size(); ++j) {
                sum += nums[j];
                ++cnt;
                if (cnt >= max) break;
                if (sum >= s) { max = cnt; break;}
            }
        }
        return max == INT_MAX ? 0 : max;           
    }
};

