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
    TreeNode* buildTree(vector<int>& preorder, int pre_st, vector<int>& inorder) {
        if (inorder.empty()) {
            return nullptr;
        }
        
        int target = preorder[pre_st];
        TreeNode* root = new TreeNode(target);
        
        auto it = std::find(inorder.begin(), inorder.end(), target);
        vector<int> inorder_left = vector<int>(inorder.begin(), it);
        vector<int> inorder_right = vector<int>(it + 1, inorder.end());
        int preorder_left_st = pre_st + 1;
        int preorder_right_st = pre_st + 1 + inorder_left.size();
        
        root->left = buildTree(preorder, preorder_left_st, inorder_left);
        root->right = buildTree(preorder, preorder_right_st, inorder_right);
        return root;
    }
    
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) { 
        return buildTree(preorder, 0, inorder);
    }
};

