/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> s;
        TreeNode* current;
        if (root == nullptr) return res;
        
        s.push(root);
        while (!s.empty()) {
            current = s.top();
            s.pop();
            
            while (current->left != nullptr) {
                s.push(current);
                current = current->left;
            }

            res.push_back(current->val); 
   
            if (current->right != nullptr) {
                s.push(current->right);
            } else {
                while (!s.empty()) {
                    current = s.top();
                    res.push_back(current->val);
                    s.pop();
                    if (current->right != nullptr) {
                        s.push(current->right);
                        break;
                    }
                }
            }
            
        }
        return res;
    }
};

