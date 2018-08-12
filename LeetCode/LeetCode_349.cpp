class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        set<int> s;
        for (int i : nums1)
        {
            s.insert(i);
        }
        set<int> s2;
        for (int i : nums2)
        {
            if (s.count(i) != 0)
            {
                s2.insert(i);
            }
        }
        
        vector<int> res;
        res.assign(s2.begin(), s2.end());
        
        return res;
    }
};

