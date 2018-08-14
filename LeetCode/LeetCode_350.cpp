class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        multiset<int> s;
        for (int i : nums1)
        {
            s.insert(i);
        }
        multiset<int> s2;
        for (int i : nums2)
        {
            multiset<int>::iterator it = s.find(i);
            if (it != s.end())
            {
                s2.insert(i);
                s.erase(it);
            }
        }
        
        vector<int> res;
        res.assign(s2.begin(), s2.end());
        
        return res;
    }
};

