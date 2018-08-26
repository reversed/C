class Solution {
public:
    int maxArea(vector<int>& height) {
        int st = 0;
        int ed = height.size() - 1;
        int mx = 0;
        
        while (st < ed)
        {
            int tmp;
            if (height[st] > height[ed])
            {
                tmp = height[ed] * (ed - st);
                --ed;
            }
            else
            {
                tmp = height[st] * (ed - st);
                ++st;
            }
            mx = max(mx, tmp);
        }
        return mx;
    }
};

