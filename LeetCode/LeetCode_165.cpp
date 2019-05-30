class Solution {
public:
    int compareVersion(string version1, string version2) {
        version1.push_back('.');
        version2.push_back('.');
        int st1 = 0;
        int st2 = 0;
        int ed1 = version1.find_first_of('.', st1);
        int ed2 = version2.find_first_of('.', st2);
        
        while (ed1 != string::npos || ed2 != string::npos) {
            int v1 = 0, v2 = 0;
            if (ed1 == string::npos) {
                v2 = stoi(version2.substr(st2, ed2 - st2), nullptr);
                if (v2 == 0) {
                    st2 = ed2 + 1;
                    ed2 = version2.find_first_of('.', st2);
                    continue;
                }
                return -1;
            }
            if (ed2 == string::npos) {
                v1 = stoi(version1.substr(st1, ed1 - st1), nullptr);
                if (v1 == 0) {
                    st1 = ed1 + 1;
                    ed1 = version1.find_first_of('.', st1);
                    continue;
                }
                return 1;
            }
            
            v1 = stoi(version1.substr(st1, ed1 - st1), nullptr);
            v2 = stoi(version2.substr(st2, ed2 - st2), nullptr);
            if (v1 > v2) return 1;
            if (v1 < v2) return -1;
            
            st1 = ed1 + 1;
            st2 = ed2 + 1;
            ed1 = version1.find_first_of('.', st1);
            ed2 = version2.find_first_of('.', st2);
        }
        
        return 0;
    }
};

