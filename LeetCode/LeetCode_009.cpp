class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        
        int tmp = x;
        std::vector<int> v1;
        while (tmp != 0)
        {
            v1.push_back(tmp % 10);
            tmp /= 10;
        }
     
        tmp = x;
        while (tmp != 0)
        {
            int i1 = v1.back();
            v1.pop_back();
            int i2 = tmp % 10;
            if (i1 != i2) return false;
            
            tmp /= 10;
        }
        return true;
    }
};

