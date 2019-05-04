/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() {}

    Node(int _val, Node* _left, Node* _right, Node* _next) {
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
};
*/
class Solution {
public:
    void connect_next_line(Node* n) {
        if (n->left == nullptr) return;
        
        Node* cur_node = n;
        while (cur_node->next != nullptr) {
            Node* next_node = cur_node->next;
            cur_node->left->next = cur_node->right;
            cur_node->right->next = next_node->left;
            cur_node = next_node;
        }
        cur_node->left->next = cur_node->right;
        return;
    }
    
    Node* connect(Node* root) {
        Node* cur = root;
        while (cur != nullptr) {
            connect_next_line(cur);
            cur = cur->left;
        }
        return root;
    }
};

