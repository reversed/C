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
    vector<vector<int>> res;
    
    void foo(TreeNode* root, int sum, vector<int>& ans) {
        if (root == nullptr) return;
        
        int cur = root->val;
        if (root->left == nullptr && root->right == nullptr) {
            sum = sum - cur;
            if (sum == 0) {
                ans.push_back(cur);
                res.push_back(ans);
                ans.pop_back();
                return;
            }
        }
        ans.push_back(cur);
        foo(root->left, sum - cur, ans);
        foo(root->right, sum - cur, ans);
        ans.pop_back();
    }
    
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<int> ans;
        foo(root, sum, ans);
        return res;
    }
};

