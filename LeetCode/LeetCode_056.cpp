/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> res;       
        if (intervals.empty()) return res;
        sort(intervals.begin(), intervals.end(), [](Interval &a, Interval &b) { return a.start < b.start; });
        res.push_back(intervals[0]);
        
        for (int i = 1; i < intervals.size(); ++i)
        {
            Interval tmp = res.back();
            Interval cur = intervals[i];
            
            if (tmp.end >= cur.start && tmp.end < cur.end)
            {
                res.pop_back();
                res.push_back(Interval(tmp.start, cur.end));
            }
            else if (tmp.end < cur.start)
            {
                res.push_back(Interval(cur.start, cur.end));
            }
        }
            
        return res;
    }
};

