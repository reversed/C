// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int st = 1;
        int ed = n;
        
        while (st <= ed)
        {
            int mid = (ed - st) / 2 + st;
            int val = guess(mid);
            if (val == 0)
            {
                return mid;
            }
            else if (val == 1)
            {
                st = mid + 1;
            }
            else
            {
                ed = mid - 1;
            }
        }
        return st;
    }
};

