class Solution {
public:
    int firstUniqChar(string s) {
        int arr[26] = {0};
        
        for (char c : s)
        {
            int idx = c - 'a';
            ++arr[idx];
        }
        
        for (int i = 0; i < s.size(); ++i)
        {
            int idx = s[i] - 'a';
            if (arr[idx] == 1) return i;
        }
        return -1;
    }
};

