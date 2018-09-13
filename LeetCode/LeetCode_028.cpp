class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle == "") return 0;
        
        int len1 = haystack.size();
        int len2 = needle.size();
        
        for (int i = 0; i < len1; ++i)
        {
            if (len1 - i < len2) break;
            
            bool found = true;
            for (int j = 0, cur = i; j < len2; ++j, ++cur)
            {
                if (haystack[cur] != needle[j])
                {
                    found = false;
                    break;
                }
            }
            if (found) return i;
        }
        return -1;
    }
};

