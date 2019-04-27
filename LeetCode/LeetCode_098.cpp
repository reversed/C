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
    void iterateBST(TreeNode* root, vector<int> &v) {
        if (root == nullptr) return;

        iterateBST(root->left, v);
        v.push_back(root->val);
        iterateBST(root->right, v);
    } 
    
    bool is_sorted(vector<int>& v) {
        for (int i = 1; i < v.size(); ++i) {
            if (v[i] <= v[i-1]) return false;
        }
        return true;
    }
    
    bool isValidBST(TreeNode* root) {
        vector<int> res;
        iterateBST(root, res);
        return is_sorted(res);
    }
};

