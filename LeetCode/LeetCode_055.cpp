class Solution {
public:
    bool canJump(vector<int>& nums) {
        int sz = nums.size();
        vector<bool> vb(sz, false);
        if (sz == 0) return true;
        
        vb[sz - 1] = true;
        for (int i = sz - 2; i >= 0; --i)
        {   
            bool finish = false;
            for (int j = 1; j <= nums[i]; ++j)
            {
                if (vb[j+i] == true)
                {
                    vb[i] = true;
                    finish = true;
                    continue;
                }
            }
            
            if (finish) continue;
            vb[i] = false;
        }
        
        return vb[0];
    }
};

