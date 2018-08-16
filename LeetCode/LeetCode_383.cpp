class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        for (char c : ransomNote)
        {
            auto idx = magazine.find(c);
            if (idx == string::npos) return false;
            else magazine.erase(idx, 1);
        }
        return true;
    }
};

