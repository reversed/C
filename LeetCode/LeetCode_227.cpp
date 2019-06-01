class Solution {
public:
    int calculate(string s) {
        stack<int> ns;
        stack<char> os;
        
        s.push_back('e'); // end indicator
        int num = 0;
        for (char c : s) {  
            if (c == ' ') {
                // do nothing
            }
            else if (c >= '0' && c <= '9') {
                num = num * 10 + (c - '0');
            }
            else {
                // operator
                if (os.empty()) {
                    os.push(c);
                    ns.push(num);
                    num = 0;
                }
                else {                   
                    char op = os.top();
                    if (op == '*' || op == '/') {
                        os.pop();
                        int n1 = ns.top();
                        ns.pop();

                        if (op == '*') ns.push(n1 * num);
                        else ns.push(n1 / num);
                    }
                    else {
                        ns.push(num);
                    }
                    os.push(c);
                    num = 0;
                }
            }
        }
        os.pop(); // end indicator
        
        stack<int> rns;
        stack<char> ros;
        while (!os.empty()) {
            ros.push(os.top());
            os.pop();
        }
        while (!ns.empty()) {
            rns.push(ns.top());
            ns.pop();
        }
        
        while (!ros.empty()) {
            int n1 = rns.top();
            rns.pop();
            int n2 = rns.top();
            rns.pop();
            
            char c = ros.top();
            ros.pop();
            
            if (c == '+') rns.push(n1 + n2);
            else if (c == '-') rns.push(n1 - n2);
        }
        
        return rns.top();
    }
};

