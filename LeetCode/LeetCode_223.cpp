class Solution {
public:
    int prod(int64_t x1, int64_t y1, int64_t x2, int64_t y2) {
        int64_t w = x2 - x1;
        int64_t h = y2 - y1;
        if (w < 0 || h < 0) return 0;
        else return w * h;
    }
    
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int64_t s1 = prod(A, B, C, D);
        int64_t s2 = prod(E, F, G, H);
        
        int64_t x1 = max(A, E);
        int64_t y1 = max(B, F);
        int64_t x2 = min(C, G);
        int64_t y2 = min(D, H);
        int64_t s3 = prod(x1, y1, x2, y2);
        
        int64_t res = s1 + s2 - s3;
        
        return res;
    }
};

