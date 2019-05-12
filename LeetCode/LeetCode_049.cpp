class Solution {
public:
	bool doCompare(string s1, string s2)
	{
		if (s1.size() != s2.size()) return false;
		
		int arr1[26] = {0};
		int arr2[26] = {0};
		for (int i = 0; i < s1.size(); ++i)
		{
			int idx1 = s1[i] - 'a';
			int idx2 = s2[i] - 'a';
			++arr1[idx1];
			++arr2[idx2];
		}
		for (int i = 0; i < 26; ++i)
		{
			if (arr1[i] != arr2[i]) return false;
		}
		
		return true;
	}

    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
		
		for (string s : strs)
		{
			bool found = false;
			for (vector<string>& vs : res)
			{
				// do compare for anagram
				if (doCompare(vs[0], s))
				{
					found = true;
					vs.push_back(s);
					break;
				}
			}
			if (!found)
			{
				res.push_back( {s} );
			}
		}
		return res;
    }
};


