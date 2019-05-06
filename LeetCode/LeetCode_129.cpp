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
    int res = 0;
    
    void count(TreeNode* root, int cnt) {
        if (root == nullptr) return;
        if (root->left == nullptr && root->right == nullptr) {
            res += cnt * 10 + root->val;
            return;
        }
        
        count(root->left, cnt * 10 + root->val);
        count(root->right, cnt * 10 + root->val);
    }
    
    int sumNumbers(TreeNode* root) {
        count(root, 0);
        return res;
    }
};

