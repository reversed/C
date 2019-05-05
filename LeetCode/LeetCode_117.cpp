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
        while (n != nullptr) {
            if (n->left != nullptr || n->right != nullptr) break;
            n = n->next;
        }
        if (n == nullptr) return;
        
        Node* cur_node = n;
        Node* head = new Node(0);

        Node* link_left = head;
        Node* link_right;
        while (cur_node != nullptr) {
            if (cur_node->left != nullptr) {
                link_right = cur_node->left;
                link_left->next = link_right;
                link_left = link_right;
            }
            if (cur_node->right != nullptr) {
                link_right = cur_node->right;
                link_left->next = link_right;
                link_left = link_right;
            }
            cur_node = cur_node->next;
        }
        link_left->next = nullptr;
        
        delete head;
        return;
    }
    
    Node* find_next_first_node(Node *n) {
        while (n != nullptr) {
            if (n->left != nullptr) return n->left;
            if (n->right != nullptr) return n->right;
            n = n->next;
        }
        return nullptr;
    }
    
    Node* connect(Node* root) {
        Node* cur = root;
        while (cur != nullptr) {
            connect_next_line(cur);
            cur = find_next_first_node(cur);
        }
        return root;
    }
};

