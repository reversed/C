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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) return res;
        
        queue<TreeNode*> q;
        int cnt1 = 0, cnt2 = 0;
        
        q.push(root);
        ++cnt1;
        while (!q.empty()) {
            TreeNode* tmp = q.front();
            if (cnt1 == 1) res.push_back(tmp->val);
            
            if (tmp->left) {
                q.push(tmp->left);
                ++cnt2;
            }
            if (tmp->right) {
                q.push(tmp->right);
                ++cnt2;
            }
            
            q.pop(); --cnt1;
            if (cnt1 == 0) {
                cnt1 = cnt2;
                cnt2 = 0;
            }
        }
        return res;
    }
};

