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
    void foo(vector<vector<int>>& res, TreeNode* root, int level, bool is_left) {
        if (root == nullptr) return;
        
        if (res.size() <= level) {
            res.push_back(vector<int>());
        }
        
        if (is_left) {
            res[level].push_back(root->val);
        }
        else {
            res[level].insert(res[level].begin(), root->val);
        }
        foo(res, root->left, level+1, !is_left);
        foo(res, root->right, level+1, !is_left);
    }
    
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        foo(res, root, 0, true);
        return res;
    }
};
