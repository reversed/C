class Solution {
public:
    int lengthOfLastWord(string s) {
        int pos_end = s.find_last_not_of(" ");
        if (pos_end == string::npos) return 0;
        
        int pos = s.find_last_of(" ", pos_end);
        if (pos == string::npos) return pos_end + 1;
        
        return pos_end - pos;
    }
};

