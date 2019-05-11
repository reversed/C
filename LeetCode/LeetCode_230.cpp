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
    int kthSmallest(TreeNode* root, int k) {
        if (k == 0 || root == nullptr) return 0;
        
        stack<TreeNode*> s;
        TreeNode *cur = root;
        
        while (cur != nullptr) {
            s.push(cur);
            cur = cur->left;
        }
        
        while (!s.empty()) {
            TreeNode *tmp = s.top();
            s.pop();
            --k;
            if (k == 0) return tmp->val;
            
            tmp = tmp->right;
            while (tmp != nullptr) {
                s.push(tmp);
                tmp = tmp->left;
            }
        }
        return 0;
    }
};

