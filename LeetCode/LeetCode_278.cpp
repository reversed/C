// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int st = 1;
        int ed = n;
        
        while (st <= ed)
        {
            int mid = st + (ed - st) / 2;
            bool is_bad = isBadVersion(mid);
            if (is_bad)
            {
                ed = mid - 1;
            }
            else
            {
                st = mid + 1;
            }
        }
        return st;
    }
};

