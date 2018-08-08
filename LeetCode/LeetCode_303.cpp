class NumArray {
public:
    NumArray(vector<int> nums) {
        int sz = nums.size();
        
        int sum = 0;
        for (int i = 0; i < sz; ++i)
        {
            sum += nums[i];
            sums.push_back(sum);
        }
    }
    
    int sumRange(int i, int j) {
        if (i == 0) return sums[j];
        else return (sums[j] - sums[i - 1]);
    }
private:
    vector<int> sums;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */
 