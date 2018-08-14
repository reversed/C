class Solution {
public:
    bool isVowel(char c)
    {
        switch (c)
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
                return true;
            default:
                return false;
        }
    }
    
    string reverseVowels(string s) {
        int sz = s.size();
        int i = 0, j = sz - 1;
        
        while (i < j)
        {
            while (i < j && !isVowel(s[i])) ++i;
            while (i < j && !isVowel(s[j])) --j;
            if (i < j) swap(s[i], s[j]);
            ++i; --j;
        }
        return s;
    }
};

