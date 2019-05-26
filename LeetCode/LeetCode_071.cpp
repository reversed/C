class Solution {
public:
    string findDir(string path, int& st) {
        string res = "";
        if (st >= path.size()) return res;
        if (path[st] != '/') res += '/';
        else res += path[st++];

        while (st < path.size() && path[st] == '/') st++;
        while (st < path.size() && path[st] != '/') { res += path[st++]; }
        
        return res;
    }
    
    string simplifyPath(string path) {
        stack<string> s;
        string res = "";
        path.insert(0, "/");

        int sz = 0;   
        string str = findDir(path, sz);
        while (str != "") {
            if (str == "/." || str == "/") {
                str = findDir(path, sz);
                continue;
            }
            if (str == "/..") {
                if (!s.empty()) s.pop();
                str = findDir(path, sz);
                continue;
            }
            s.push(str);
            str = findDir(path, sz);
        }
        
        while (!s.empty()) {
            res.insert(0, s.top());
            s.pop();
        }
        
        if (res.empty()) return "/";
        return res;
    }
};
