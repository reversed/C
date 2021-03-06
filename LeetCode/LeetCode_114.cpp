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
    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        
        flatten(root->left);
        flatten(root->right);
        
        TreeNode* tmp = root->right;
        root->right = root->left;
        root->left = nullptr;
        
        TreeNode* pre = root;
        while (pre->right != nullptr) {
            pre = pre->right;
        }
        pre->right = tmp;
    }
};

