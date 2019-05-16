/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random) {
        val = _val;
        next = _next;
        random = _random;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;
        map<Node*, Node*> m;
        
        Node* n1 = head;
        Node* n2 = new Node(n1->val, nullptr, nullptr);
        m.insert( pair(n1, n2) );
        Node* res = n2;
        
        while (n1->next != nullptr) {
            n2->next = new Node(n1->next->val, nullptr, nullptr);
            m.insert( pair(n1->next, n2->next) );
            
            n1 = n1->next;
            n2 = n2->next;
        }
        
        n1 = head;
        n2 = res;
        while (n1 != nullptr) {
            Node* r1 = n1->random;
            Node* r2 = m[r1];
            n2->random = r2;
            
            n1 = n1->next;
            n2 = n2->next;
        }
        
        return res;
    }
};

